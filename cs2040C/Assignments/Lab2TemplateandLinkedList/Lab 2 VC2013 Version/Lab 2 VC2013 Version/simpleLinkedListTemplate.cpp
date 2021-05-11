#pragma once

#ifndef SIMPLELINKEDLISTTEMPLATEHPP
#define SIMPLELINKEDLISTTEMPLATEHPP

#include <iostream>
#include "simpleLinkedListTemplate.h"
using namespace std;

template <class T>
ListNode<T>::ListNode(T n)
{
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
	if (_head == NULL) {
		return false;
	}
	ListNode<T>* temp = _head;
	while (temp != NULL) {
		if (temp->_item == n) {
			return true;
		}
		temp = temp->_next;
	}
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
	ListNode<T>* temp = _head;
	ListNode<T>* previous = _head;
	ListNode<T>* largest = _head;
	T max = _head->_item;

	while (temp->_next != NULL) {
		if (temp->_next->_item > max) {
			largest = temp->_next;
			max = largest->_item;
			previous = temp;
		}
		temp = temp->_next;
	}

	if (largest->_next == NULL) {
		previous->_next = NULL;
	}
	else if (largest == _head) {
		if (_size == 1) {
			_head = NULL;
		}
		else {
			_head = _head->_next;
		}
	}
	else
	{
		previous->_next = largest->_next;
	}
	_size--;
	delete largest;

	return T(max);
}

template <class T>
void List<T>::reverseOp() {

	if (_head == NULL) {
		return;
	}
	ListNode<T>* previous = NULL;
	ListNode<T>* current = _head->_next;

	while (current != NULL) {
		_head->_next = previous;
		previous = _head;
		_head = current;
		current = _head->_next;
	}
	_head->_next = previous;
}

/*
template <class T>
void List<T>::reverseOp() {
	if (_head == NULL || _size == 0) {
		return;
	}

	ListNode<T>* previous = NULL;
	ListNode<T>* current = _head;
	ListNode<T>* after = NULL;

	while (current->_next) {
		after = current->_next;
		current->_next = previous;
		previous = current;
		current = after;
		_head = current;
	}
}
*/

template <class T>
List<T>::~List()
{
	while (_head)
		removeHead();
};


#endif