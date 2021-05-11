#pragma once

#ifndef STACKHPP
#define STACKHPP

#include <iostream>
#include "stack.h"
using namespace std;

// Task 3: Implement push, peek and pop operations of a stack using a single linked list.

template <class T>
void Stack<T>::push(T _item) {
	_stack->insertHead(_item);
}

template <class T>
T Stack<T>::peek() {
	return _stack->getHead();
}

template <class T>
T Stack<T>::pop() {
	T ans = _stack->getHead();
	_stack->deleteHead();
	return ans;
}

template <class T>
void Stack<T>::print() {
	_stack->print();
}

#endif