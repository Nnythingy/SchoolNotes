/**
 * CS2106 AY21/22 Semester 1 - Lab 2
 *
 * This file contains function definitions. Your implementation should go in
 * this file.
 * Lab 2
 * Name: Ng Jong Ray, Edward
 * Student No: A0216695U
 * Lab Group: B05
 **/

#include "myshell.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

int shmid;
key_t shmkey = 123456;

void my_init(void) {
    // Initialize what you need here
    int **shm;

    shmid = shmget(shmkey, (200*sizeof(int)), IPC_CREAT| 0600);
    if (shmid == -1) {
        printf("Cannot create shared memory\n");
        exit(1);
    }

    shm = (int **)shmat(shmid, NULL, 0);
    if (shm == (int **)-1) {
        printf("Cannot attach\n");
        exit(1);
    }

    // 2d array
    // shm[0][0] stores counter
    // 0 index stores pid
    // 1 index stores status
    for (int i = 0; i < 100; i++){
        shm[i] = (int *)calloc(2, sizeof(int));
    }
}

void run_program(char **tokens) {
    int **shm;
    shm = (int **)shmat(shmid, NULL, 0);
    if (shm == (int **)-1) {
        printf("Cannot attach\n");
        exit(1);
    }

    if (access(tokens[0], F_OK) == 0) {
        execv(tokens[0], tokens);
        exit(0);
    } else {
        printf("%s not found\n", tokens[0]);
        shm[0][0] -= 1;
    }
    shmdt((char *)shm);
}

//help to remove unwanted tokens
void string_split(char **tokens, char **newcommand, int start, int end) {
    int j = 0;
    for (int i = start; i < end; i++) {
        newcommand[j] = calloc(strlen(tokens[i]), sizeof(char));
        strcpy(newcommand[j], tokens[i]);
        if (j == end-1) {
            newcommand[j+1] = '\0';
        }
        j += 1;
    }
}

void my_process_command(size_t num_tokens, char **tokens) {
    // Your code here, refer to the lab document for a description of the arguments
    int flag = 0;
    int **shm;

    shm = (int **)shmat(shmid, NULL, 0);
    if (shm == (int **)-1) {
        printf("Cannot attach\n");
        exit(1);
    }

    if (strcmp(tokens[0],"info") == 0) {
        for (int i = 1; i <= shm[0][0]; i++) {
            if (kill(shm[i][0], 0) == -1){
                //if process is no longer running
                int errsv = errno;
                if (errsv == ESRCH) {
                    printf("[%d] Exited %d\n", shm[i][0], shm[i][1]);
                }
            }
            else {
                //process is still running
                int errsv = errno;
                printf("errsv: %d\n", errsv);
                if (shm[i][1] == 9999) {
                    printf("[%d] Terminating\n", shm[i][0]);
                    int status;
                    waitpid(shm[i][0], &status, WNOHANG);
                    shm[i][1] = WEXITSTATUS(status);
                    continue;
                }
                printf("[%d] Running\n", shm[i][0]);
            }
        }
        return;
    } 

    //handling wait
    if (strcmp(tokens[0],"wait") == 0) {
        int status;
        char *stopstring;
        pid_t cpid = strtol(tokens[1], &stopstring, 10);
        waitpid(cpid, &status, 0);
        for (int i = 1; i <= shm[0][0]; i++) {
            if (shm[i][0] == cpid) {
                shm[i][1] = WEXITSTATUS(status);
            }
        }
        return;
    } 

    //handling terminate
    if (strcmp(tokens[0],"terminate") == 0) {
        char *stopstring;
        pid_t killValue;
        pid_t cpid = strtol(tokens[1], &stopstring, 10);
        killValue = kill(cpid, SIGTERM);
        if (killValue) {
            //unsuccessful kill
        }
        else {
            //successful kill
            for (int i = 1; i <= shm[0][0]; i++) {
                if (shm[i][0] == cpid) {
                    shm[i][1] = 9999;
                }
            }
        }
        return;
    }

    if (strcmp(tokens[num_tokens-2],"&") == 0) {
        //handling background processes
        shm[0][0] += 1;
        int counter = shm[0][0];
        int status = 0;
        //allocated space -1 because removing '&'
        char **newcommand = calloc(num_tokens-1, sizeof(char *));
        //creating the same command without &
        string_split(tokens, newcommand, 0, num_tokens-2);
        fflush(stdin);
        signal(SIGCHLD, SIG_IGN);
        pid_t cpid = fork();
        if (cpid == -1) {
            printf("Fork Error\n");
            exit(-1);
        }
        else if (cpid == 0) {
            setpgid(0, 0);
            run_program(newcommand);
        }
        else {
            waitpid(cpid, &status, WNOHANG);
            shm[counter][0] = cpid;
            shm[counter][1] = WEXITSTATUS(status);
            printf("Child[%d] in background\n", cpid);
        }
        free(newcommand);
        return;
    }

    //handle chaining commands
    int j = 0; //to track the starting token
    for (size_t i = 0; i < num_tokens-2; i++) {
        if (strcmp("&&", tokens[i]) ==  0) {
            shm[0][0] += 1;
            int counter = shm[0][0];
            int status = 0;
            char **newcommand = calloc(i-j+1, sizeof(char *));
            string_split(tokens, newcommand, j, i);
            fflush(stdin);
            pid_t cpid = fork();
            if (cpid == -1) {
                printf("Fork Error\n");
                exit(-1);
            }
            else if (cpid == 0) {
                run_program(newcommand);
            }
            else {
                waitpid(cpid, &status, 0);
                shm[counter][0] = cpid;
                shm[counter][1] = WEXITSTATUS(status);
                //checking if program exists
                //checking if program failed
                if (shm[counter][1] != 0) {
                    printf("%s failed\n", newcommand[0]);
                    return;
                }
            }
            if (counter != shm[0][0]) {
                return;
            }
            j = i+1; //prepare tracker for next command
            flag = 1;
            free(newcommand);
        }
    }

    if (flag == 1) {
        shm[0][0] += 1;
        int counter = shm[0][0];
        int status = 0;
        char **newcommand = calloc(num_tokens-j, sizeof(char *));
        //num_tokens-j since num_tokens-1-j+1
        string_split(tokens, newcommand, j, num_tokens-1);
        fflush(stdin);
        pid_t cpid = fork();
        if (cpid == -1) {
            printf("Fork Error\n");
            exit(-1);
        }
        else if (cpid == 0) {
            run_program(newcommand);
        }
        else {
            waitpid(cpid, &status, 0);
            shm[counter][0] = cpid;
            shm[counter][1] = WEXITSTATUS(status);
            free(newcommand);
        }
    }
    else {
        shm[0][0] += 1;
        int counter = shm[0][0];
        int status = 0;
        fflush(stdin);
        pid_t cpid = fork();
        if (cpid == -1) {
            printf("Fork Error\n");
            exit(-1);
        } else if (cpid == 0) {
            run_program(tokens);
        } else {
            waitpid(cpid, &status, 0);
            shm[counter][0] = cpid;
            shm[counter][1] = WEXITSTATUS(status);
        }
    }
    shmdt((char *)shm);
}

void my_quit(void) {
    // Clean up function, called after "quit" is entered as a user command
    int **shm;

    shm = (int **)shmat(shmid, NULL, 0);
    if (shm == (int **)-1) {
        printf("Cannot attach\n");
        exit(1);
    }
    for (int i = 0; i < 51; i++){
        free(shm[i]);
    }

    shmctl( shmid, IPC_RMID, 0);
    printf("Goodbye!\n");
    execl("exit","",NULL);
}
