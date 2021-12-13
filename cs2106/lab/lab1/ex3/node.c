/*************************************
* Lab 1 Exercise 3
* Name: Ng Jong Ray, Edward
* Student No: A0216695U
* Lab Group: B05
*************************************/

#include "node.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Copy in your implementation of the functions from ex2.
// There is one extra function called map which you have to fill up too.
// Feel free to add any new functions as you deem fit.

// Inserts a new node with data value at index (counting from head
// starting at 0).
// Note: index is guaranteed to be valid.
void insert_node_at(list *lst, int index, int data) {
    //initialise tmp node to follow lst
    node *tmp = lst->head;
node *newNode = (node *)malloc(sizeof(node));
		newNode->data = data;
    newNode->next = NULL;

    //empty lst
    if (tmp == NULL){
        lst->head = newNode;
        newNode->next = lst->head;
        return;
    }
        
    //inserting at head
    if (index == 0) {
        do {
            tmp = tmp->next; 
        } while (tmp->next != lst->head);
        newNode->next = lst->head;
        lst->head = newNode;
        tmp->next = lst->head;
    } else {
        while (index > 1) {
            tmp = tmp->next; 
            index -= 1;
        }
        newNode->next = tmp->next;
        tmp->next = newNode;
    }
}

// Deletes node at index (counting from head starting from 0).
// Note: index is guarenteed to be valid.
void delete_node_at(list *lst, int index) {
    //initialise tmp node to follow lst
    node *tmp = lst->head;

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
    if (index == 0) {
		//tmp goes to tail
        do {
            tmp = tmp->next; 
        } while (tmp->next != lst->head);
        lst->head = lst->head->next; //connect lst head to next node
        free(tmp->next); //free head
        tmp->next = lst->head; //connect tail to new lst head
    } else {
        while (index > 1) {
            tmp = tmp->next; 
            index -= 1;
        }
        node *delNode = tmp->next;
        tmp->next = delNode->next;
        free(delNode);
    }
}

// Rotates list by the given offset.
// Note: offset is guarenteed to be non-negative.
void rotate_list(list *lst, int offset) {
	//if list is empty
	if (lst->head == NULL) {
		return;
	}

    for (int i = 0; i < offset; i++) {
        lst->head = lst->head->next;
    }
}

// Reverses the list, with the original "tail" node
// becoming the new head node.
void reverse_list(list *lst) {
	//if list is empty
	if (lst->head == NULL) {
		return;
	}

    node *tmp = lst->head;
    node *first = lst->head;
    node *middle = NULL;

    do {
        tmp = tmp->next; 
    } while (tmp->next != lst->head);
	lst->head = tmp; //set head to tail
    middle = first->next;
    first->next = lst->head;
    while (middle != lst->head) {
        node *holder = middle->next;
        middle->next = first;
        first = middle;
        middle = holder;
    }
    middle->next = first;
}

// Resets list to an empty state (no nodes) and frees
// any allocated memory in the process
void reset_list(list *lst) {
	//if list is empty
	if (lst->head == NULL) {
		return;
	}

    node *tmp = lst->head;
    int counter = 1; //counting total number of nodes
    while (tmp->next != lst->head) {
		counter += 1;
		tmp = tmp->next;
    }
	//deleting of nodes
	for (int i = 0; i < counter; i++) {
		delete_node_at(lst, 0);
	}
}

// Traverses list and applies func on data values of
// all elements in the list.
void map(list *lst, int (*func)(int)) {
	node *tmp = lst->head;

	//if list is empty
	if (lst->head == NULL) {
		return;
	}
	
	do {
	    tmp->data = func(tmp->data);
		tmp = tmp->next;
	} while (tmp != lst->head);
}

// Traverses list and returns the sum of the data values
// of every node in the list.
long sum_list(list *lst) {
	node *tmp = lst->head;
	long counter = 0;

	//if list is empty
	if (lst->head == NULL) {
		return 0;
	}
	
	do {
	    counter += tmp->data;
		tmp = tmp->next;
	} while (tmp != lst->head);
	return counter;
}
