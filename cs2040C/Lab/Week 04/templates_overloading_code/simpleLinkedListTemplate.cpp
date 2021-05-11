// #pragma once

#ifndef SIMPLELINKEDLISTTEMPLATEHPP
#define SIMPLELINKEDLISTTEMPLATEHPP

#include <iostream>
#include "simpleLinkedListTemplate.h"
using namespace std;


template <class T>
ListNode<T>::ListNode(T n){
	_item = n;
	_next = NULL;
}

template <class T>
void List<T>::insertHead(T n)
{
	ListNode<T> *aNewNode = new ListNode<T>(n);
	aNewNode->_next = _head;
	_head = aNewNode;
	_size++;
};

template <class T>
void List<T>::removeHead()
{
	if (_size > 0) {
		ListNode<T> *temp = _head;
		_head = _head->_next;
		delete temp;
		_size--;
	}
}

template <class T>
void List<T>::print(bool withNL) {

	ListNode<T> *temp = _head;
	while (temp) {
		cout << temp->_item;
		if (withNL)
			cout << endl;
		else
			cout << " ";
		temp = temp->_next;
	}
	cout << endl;
	  
}

template <class T>
bool List<T>::exist(T n) {

	// modify this
	return false; 
}

template <class T>
T List<T>::headItem()
{
	if (_size)
		return *_head;
}

template <class T>
T List<T>::extractMax()
{

	// if there are duplicates maximas in the list, return the leftmost one (the one closest to the _head)
	return T();
}

template <class T>
void List<T>::reverseOp() {

}



template <class T>
List<T>::~List()
{
	while (_head)
		removeHead();
};


#endif