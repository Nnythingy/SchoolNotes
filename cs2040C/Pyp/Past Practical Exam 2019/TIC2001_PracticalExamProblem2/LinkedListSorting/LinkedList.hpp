#pragma once

#ifndef LINKEDLIST_HPP_
#define LINKEDlIST_HPP_

#include <iostream>
#include "LinkedList.h"
using namespace std;

/*
 * LISTNODE CONSTRUCTUORS AND FUNCTIONS
 */
ListNode::ListNode( int item ) {
    _item = item;
    _next = NULL;
}

void ListNode::printItem() {
    cout << _item;
}


/*
 * LIST CONSTRUCTORS AND FUNCTIONS
 */
List::List() {
    _head = NULL;
}

List::~List() {
    while ( _head ) {
        removeHead();
    }
}

void List::insertHead( int item ) {
    ListNode* newNode = new ListNode( item );
    newNode->_next = _head;
    _head = newNode;
}

int List::getHeadItem() {
    return _head->_item;
}

int List::removeHead() {
    int item = SHRT_MIN;  // -32768
    ListNode* temp;

    if ( _head ) {
        temp = _head;
        item = getHeadItem();
        _head = _head->_next;
        delete temp;
    }

    return item;
}

void List::reverse() {
    ListNode* curr = _head;
    ListNode* prev = NULL;
    ListNode* next = NULL;

    while ( curr ) {
        next = curr->_next;
        curr->_next = prev;
        prev = curr;
        curr = next;
    }

    _head = prev;
}

void List::bubbleSort( bool printAtEveryIteration ) {

    // TODO: Implement bubble sort on this implementation of single linked list.
    //       Print the linked list after every pass in the outer iteration
    //       using print(false) function in List class if parameter is true.
    //       The list should be sorted in ascending order.

    // ENTER YOUR ANSWER BELOW.
    ListNode* temp = NULL;
    ListNode* last = NULL;
    while (last != _head->_next)
    {
        temp = _head;
		while (temp->_next && temp->_next != last) {
			if (temp->_item > temp->_next->_item)
			{
				int x = temp->_item;
				temp->_item = temp->_next->_item;
		        temp->_next->_item = x;
            }
			temp = temp->_next;
		}
		last = temp;
        if (last == _head->_next) continue;
        printAtEveryIteration ? print(false) : true;
    }
    print(false);

    // ENTER YOUR ANSWER ABOVE.
}

void List::mergeSort() {
    recursiveMergeSort( this );
}

void List::recursiveMergeSort( List* list ) {
    // TODO: Implement merge sort on this implementation of single linked list.
    // ENTER YOUR ANSWER BELOW.
    if (!list->_head || !list->_head->_next) return;
    List* otherlist = new List;
    list->split(otherlist);
    recursiveMergeSort(list);
    recursiveMergeSort(otherlist);
    list->merge(otherlist);
    // ENTER YOUR ANSWER ABOVE.
}

void List::split( List* otherList ) {
    // TODO: Implement splitting of the current list.
    //       The first half of the list will be pointed by itself.
    //       The second half of the list will be pointed by otherList.
    //       It is guaranteed that the original list will have more than one node.
    //
    // ENTER YOUR ANSWER BELOW.
    ListNode* tmp = _head;
    int size = 1;
    int i = 0;
    while (tmp->_next)
    {
        tmp = tmp->_next;
        size++;
    }
    reverse();
    for (int i = 0; i < size/2; i++)
    {
        otherList->insertHead(removeHead());
    }
    reverse();

    // ENTER YOUR ANSWER ABOVE.
}

void List::merge( List* otherList ) {
    // TODO: Implement merging of current list and otherList.
    //       The otherList should be empty after merging.
    //       It is guaranteed that both lists are non-empty.
    //
    // ENTER YOUR ANSWER BELOW.
    reverse();
    otherList->reverse();

    List* newlist = new List;

    while (_head && otherList->_head) {
		if (getHeadItem() > otherList->getHeadItem())
		{
			newlist->insertHead(removeHead());
		}
        else
        {
            newlist->insertHead(otherList->removeHead());
        }
    }
    
    if (_head)
    {
        while (_head)
        {
            newlist->insertHead(removeHead());
        }
    }
    else
    {
        while (otherList->_head)
        {
            newlist->insertHead(otherList->removeHead());
        }
    }

    _head = newlist->_head;
    // ENTER YOUR ANSWER ABOVE.
}

void List::print( bool printWithNewLine = false ) {

    ListNode* curr = _head;

    while ( curr ) {
        cout << curr->_item;

        if ( printWithNewLine )
            cout << endl;
        else
            cout << " ";

        curr = curr->_next;
    }

    cout << endl;
}

#endif
