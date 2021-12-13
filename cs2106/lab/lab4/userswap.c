#include "userswap.h"
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<fcntl.h>
#include <string.h>
#include <signal.h>
#define PAGE_SIZE 4096

typedef struct NODE {
    void *mem;
    int  permission; //none = 0; read = 1; write = 2; r+w = 3
    int  is_dirty;
    size_t size;
    int is_file;
    struct NODE *next;
} node;

typedef struct {
    node *head;
    size_t count;
} list;

size_t curr_LORM = 0;
list *allMem; //holds information of all created memory
list *pageTable;
list *pidData; //permission stores pid, is_dirty stores fd, size stores count

void insert_node_at(list *lst, int is_pageTable, void *page, int permission, int is_dirty, size_t size, int is_file);
void delete_head(list *lst, int is_pageTable, int is_dirty, pid_t pid);
void delete_node_at(list *lst, node *index, int is_pageTable);
void page_fault_handler(void *addr, pid_t pid, int is_file, size_t offset);
void sigaction_init();

//might need to take in pid
void page_fault_handler(void *addr, pid_t pid, int is_file, size_t offset) {
    //go through the pageTable list
    if (is_file != 0) {
        //need make the allMem show that is it dirty too
        node *tmp = pageTable->head;
        while (tmp != NULL) {
            //resident page caused a pagefault
            //due to lack of write permissions
            if (tmp->mem == addr) {
                mprotect(addr, PAGE_SIZE, PROT_READ | PROT_WRITE);
                tmp->permission = 3;
                tmp->is_dirty = 1;
                for (node *i = allMem->head; i != NULL; i = i->next) {
                    //setting the memory as dirty
                    //to allow writing back to backup file later
                    if (((intptr_t)tmp->mem >= (intptr_t)i->mem) &&
                            ((intptr_t)tmp->mem < ((intptr_t)i->mem + (intptr_t)i->size))) {
                        i->is_dirty = 1;
                    }
                }
                return;
            }
                tmp = tmp->next;
        }
        //page is not resident and need add node to page table

        //checking if LORM has been reached
        if (pageTable->count <= 0) {
            //giving old page PROT_NONE
            pageTable->head->permission = 0;
            mprotect(pageTable->head->mem, PAGE_SIZE, PROT_NONE);
            delete_head(pageTable, 1, pageTable->head->is_dirty, pid);
        }
        //adding the new page into pageTable
        mprotect(addr, PAGE_SIZE, PROT_READ);
        insert_node_at(pageTable, 1, addr, 1, 0, offset, is_file);

        //chekcing pidData list for old data
        node *search = pageTable->head;
        while (search != NULL) {
            if (search->mem == addr) {
                //page data in swp file
                //loading back memory, should cause another sigsegv to give write permission
                if(pread(is_file, addr, PAGE_SIZE, offset) == -1) {
                    exit(1);
                }
                break;
            }
            search = search->next;
        }
    }
    else {
        node *tmp = pageTable->head;
        while (tmp != NULL) {
            //resident page caused a pagefault
            //due to lack of write permissions
            if (tmp->mem == addr) {
                mprotect(addr, PAGE_SIZE, PROT_READ | PROT_WRITE);
                tmp->permission = 3;
                tmp->is_dirty = 1;
                return;
            }
            tmp = tmp->next;
        }
        //page is not resident and need add node to page table

        //checking if LORM has been reached
        if (pageTable->count <= 0) {
            //giving old page PROT_NONE
            pageTable->head->permission = 0;
            mprotect(pageTable->head->mem, PAGE_SIZE, PROT_NONE);
            delete_head(pageTable, 1, pageTable->head->is_dirty, pid);
        }
        //adding the new page into pageTable
        mprotect(addr, PAGE_SIZE, PROT_READ);
        insert_node_at(pageTable, 1, addr, 1, 0, PAGE_SIZE, 0);

        //chekcing pidData list for old data
        node *search = pidData->head;
        while (search != NULL) {
            if (search->mem == addr) {
                //page data in swp file
                //loading back memory, should cause another sigsegv to give write permission
                if (read(search->is_dirty, addr, PAGE_SIZE * search->size) == -1) {
                    exit(1);
                }
                delete_node_at(pidData, search, 0);
            }
            search = search->next;
        }
    }
}

static void sigsegv_handler(int sig, siginfo_t *info, void *ucontext) {
    //find the correct memory in the allMem list
    node *tmp = allMem->head;
    while (tmp != NULL) {
        //checking if within controlled region
        if (((intptr_t)info->si_addr >= (intptr_t)tmp->mem) &&
                ((intptr_t)info->si_addr < ((intptr_t)tmp->mem + (intptr_t)tmp->size))) {
            page_fault_handler(info->si_addr, info->si_pid, tmp->is_file, (intptr_t)info->si_addr-(intptr_t)tmp->mem);
            return;
        }
        tmp = tmp->next;
    }
    signal(SIGSEGV, SIG_DFL);
}

void userswap_set_size(size_t size) {
    size_t old_LORM = curr_LORM;
    int remainder = size % PAGE_SIZE;
    if (remainder != 0) {
        size = size + PAGE_SIZE - remainder;
    }

    if (curr_LORM == 0) {
        curr_LORM = size;
    }
    long long amount = curr_LORM - old_LORM;
    
    //checking if a linked list already exists
    if (pageTable) {
        pageTable->count += amount;
    } else {
        pageTable = (list *)malloc(sizeof(list));
        pageTable->head = NULL;
        pageTable->count = size;
    }
}

void *userswap_alloc(size_t size) {
    //checking if linked list already exists
    if (!allMem) {
        allMem = (list *)malloc(sizeof(list));
        allMem->head = NULL;
        allMem->count = 0;
    }

    userswap_set_size(PAGE_SIZE);
    
    if (!pidData) {
        pidData = (list *)malloc(sizeof(list));
        pidData->head = NULL;
        pidData->count = size;
    }

    sigaction_init();

    // round up size to PAGE_SIZE
    int remainder = size % PAGE_SIZE;
    if (remainder != 0) {
        size = size + PAGE_SIZE - remainder;
    }

    // init non resident page
    void *newMem = mmap(0, size, PROT_NONE, MAP_ANON|MAP_PRIVATE, -1, 0);
    if (newMem == MAP_FAILED) {
        printf("New page allocation Failed\n");
        return NULL;
    }

    insert_node_at(allMem, 0, newMem, 0, 0, size, 0);
    return newMem;
}

void userswap_free(void *mem) {
    //check for the mem
    node *tmp = allMem->head;
    while (tmp != NULL) {
        if (tmp->mem == mem) {
            //if the released memory is the whole block
            size_t size;
            size = tmp->size;
            delete_node_at(allMem, tmp, 1);
            if (tmp->is_file != 0 && tmp->is_dirty == 1) {
                //writing back data from memory to backing file
                if(pwrite(tmp->is_file, mem, tmp->size, 0) == -1) {
                    exit(1);
                }
            }
            if(munmap(mem, size)) {
                printf("munmap VM page to kernel fail\n");
                exit(1);
            }
            return;
        }
        tmp = tmp->next;
    }
    //mem released is in the middle of the block
    //update old ll node with same addr but new size
    node *tmp2 = allMem->head;
    while (tmp2 != NULL) {
        if (((intptr_t)mem >= (intptr_t)tmp2->mem) &&
                ((intptr_t)mem < ((intptr_t)tmp2->mem + (intptr_t)tmp2->size))) {
            intptr_t offset;
            offset = (intptr_t)mem - (intptr_t)tmp2->mem;
            if (tmp2->is_file != 0 && tmp2->is_dirty == 1) {
                //writing back data from memory to backing file
                if(pwrite(tmp2->is_file, mem, tmp2->size-(size_t)offset, (size_t)offset) == -1) {
                    exit(1);
                }
            }
            if (munmap(mem, tmp2->size-(size_t)offset)) {
                printf("munmap VM page to kernel fail\n");
                exit(1);
            }
            tmp2->size = (size_t)offset;
            break;
        }
        tmp2 = tmp2->next;
    }
}

void *userswap_map(int fd, size_t size) {
    //checking if linked list already exists
    if (!allMem) {
        allMem = (list *)malloc(sizeof(list));
        allMem->head = NULL;
        allMem->count = 0;
    }

    userswap_set_size(size);

    if (!pidData) {
        pidData = (list *)malloc(sizeof(list));
        pidData->head = NULL;
        pidData->count = size;
    }

    sigaction_init();

    // round up size to PAGE_SIZE
    int remainder = size % PAGE_SIZE;
    if (remainder != 0) {
        size = size + PAGE_SIZE - remainder;
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        exit(1);
    }
    if (sb.st_size != (off_t)size) {
        if (ftruncate(fd, size) == -1) {
            exit(1);
        }
    }

    // init non resident page
    void *newMem = mmap(0, size, PROT_NONE, MAP_ANON|MAP_PRIVATE, -1, 0);
    if (newMem == MAP_FAILED) {
        printf("New page allocation Failed\n");
        return NULL;
    }

    insert_node_at(allMem, 0, newMem, 0, 0, size, fd);

    return newMem;
}

void sigaction_init() {
    struct sigaction pageAction;
    pageAction.sa_sigaction = sigsegv_handler;
    pageAction.sa_flags = SA_SIGINFO;
    //sigemptyset(&pageAction.sa_mask);
    //sigaddset(&pageAction.sa_mask, SIGSEGV);
    if(sigaction(SIGSEGV, &pageAction, NULL) == -1) {
        printf("Failed to setup signal handlers.");
        return;
    }
}

void insert_node_at(list *lst, int is_pageTable, void *page, int permission, int is_dirty, size_t size, int is_file) {
    //initialise tmp node to follow lst
    node *tmp = lst->head;
    if (is_pageTable) {
        lst->count -= size;
    } else {
        lst->count++;
    }

    //insert other data also
    node *newNode = (node *)malloc(sizeof(node));
    newNode->mem = page;
    newNode->permission = permission;
    newNode->is_dirty = is_dirty;
    newNode->size = size;
    newNode->is_file = is_file;
    newNode->next = NULL;

    //empty lst
    if (tmp == NULL){
        lst->head = newNode;
        return;
    }
        
    //inserting at tail
    while (tmp->next != NULL) {
        tmp = tmp->next; 
    }
    tmp->next = newNode;
}

//to check what is the free location in the swp file
int free_index(list *lst, pid_t pid) {
    int check[4] = {0};
    int current = 0;
    node *tmp = lst->head;
    while (tmp->next != NULL) {
        if (tmp->permission == pid) {
            check[tmp->size] = 1;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (check[i] == 0) {
            current = i;
            return current;
        }
    }
    return -1;
}

//used to remove head of pageTable
void delete_head(list *lst, int is_pageTable, int is_dirty, pid_t pid) {
    //initialise tmp node to follow lst
    node *tmp = lst->head;
    if (is_pageTable) {
        lst->count += tmp->size;
    } else {
        lst->count--;
    }

    //consider if is_dirty then write back to swp file
    //save the information to pidData ll
    //add the fd there
    if (is_pageTable && is_dirty) {
        int flag = 0;
        int fd;
        node *pidnode = pidData->head;
        while (pidnode != NULL) {
            if (pidnode->permission == pid) {
                //swp file with pid already exists
                flag = 1;
                fd = pidnode->is_dirty;
                insert_node_at(pidData, 0, tmp->mem, pid, fd, 0, 0);
                int location = free_index(pidData, pid);
                if(write(fd, tmp->mem, PAGE_SIZE * location) == -1) {
                    exit(1); //writing data to swap file
                }
                madvise(tmp->mem, PAGE_SIZE, MADV_DONTNEED);
                break;
            }
            pidnode = pidnode->next;
        }

        //no swp file yet
        //creating new .swp
        if (flag) {
            insert_node_at(pidData, 0, tmp->mem, pid, 0, 0, 0);
            char *filename;
            sprintf(filename, "%d", pid);
            strcat(filename, ".swp");

            fd = open(filename, O_CREAT | O_WRONLY, 0777);
            printf("opened file %d\n", fd);
            node *search = pidData->head;
            while (search->next != NULL) {
                if (search->permission == pid && search->mem == tmp->mem) {
                    search->is_dirty = fd;
                    int result = ftruncate(fd, PAGE_SIZE * 4); //create a swp file to store up to 4 pages
                    int result1 = write(fd, tmp->mem, PAGE_SIZE * search->size); //writing data to swap file
                    madvise(tmp->mem, PAGE_SIZE, MADV_DONTNEED);
                    if (!result || !result1) {
                        exit(1);
                    }
                    break;
                }
                search = search->next;
            }
        }
    }

	//if only 1 node in the list
	if (tmp->next == NULL) {
		lst->head = NULL;
		free(tmp);
		return;
	}

    //deleting head
    lst->head = lst->head->next; //connect lst head to next node
    free(tmp); //free head
}

//this will only be used to free memory
void delete_node_at(list *lst, node *index, int is_pageTable) {
    //initialise tmp node to follow lst
    node *tmp = lst->head;
    if (is_pageTable) {
        lst->count += index->size;
    } else {
        lst->count--;
    }

	//if list is empty
	if (lst->head == NULL) {
		return;
	}

	//if only 1 node in the list
	if (tmp->next == lst->head) {
		lst->head = NULL;
		free(tmp);
		return;
	}
        
    //deleting head
    if (index == tmp) {
        lst->head = tmp->next; //connect tail to new lst head
        free(tmp); //free head
    }
    else {
        while (tmp->next != index) {
            tmp = tmp->next; 
        }
        node *delNode = tmp->next;
        tmp->next = delNode->next;
        free(delNode);
    }
}
