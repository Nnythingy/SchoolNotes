#pragma once
#include <math.h>

#include <iostream>
using namespace std;

#ifndef HEAPHPP
#define HEAPHPP

template <class T>
int Heap<T>::_parent(int index) {
	return ((index - 1) / 2);
}

template <class T>
int Heap<T>::_rightChild(int index) {
	return ((2*index) + 2);
}

template <class T>
int Heap<T>::_leftChild(int index) {
	return ((2*index) + 1);
}

template <class T>
void Heap<T>::_swap(int a, int b) {
	T tmp = _heap[a];
	_heap[a] = _heap[b];
	_heap[b] = tmp;
}

template <class T>
void Heap<T>::_bubbleUp(int index) {
	if (index < 1) return;
	if (_heap[index] < _heap[_parent(index)]) return;

	_swap(index, _parent(index));
	_bubbleUp(_parent(index));
}

template <class T>
void Heap<T>::_bubbleDown(int index) {
	int left = _leftChild(index);
	int right = _rightChild(index);
	if (left >= _n || right >= _n) return;
	if (_heap[index] > _heap[left] && _heap[index] > _heap[right]) return;

	if (_heap[left] > _heap[right]) {
		_swap(index, left);
		_bubbleDown(left);
	}
	else
	{
		_swap(index, right);
		_bubbleDown(right);
	}
}

template <class T>
void Heap<T>::insert(T item) {
	_heap[_n] = item;
	if (!(_heap[_n] < _heap[_parent(_n)])) {
		_bubbleUp(_n);
	}
	_n++;
}

template <class T>
T Heap<T>::extractMax() {
	T max = _heap[0];
	_swap(0, _n-1);
	_n--;
	_bubbleDown(0);
	return max;
}


template <class T>
void Heap<T>::printHeapArray() {
	for (int i = 0; i < _n; i++)
		cout << _heap[i] << " ";
	cout << endl;
}

template <class T>
int Heap<T>::_lookFor(T x){ // not a very good implementation, but just use this for now.
    int i;
    for(i=0;i<_n;i++)
        if (_heap[i] == x)
            return i;
    
    return -1;
}

template <class T>
void Heap<T>::decreaseKey(T from, T to)
{
	if (_n <= 0) return;
	int index = _lookFor(from);
	_heap[index] = to;

	_bubbleDown(index);
}


template <class T>
void Heap<T>::increaseKey(T from, T to)
{
	if (_n == 0) return;
	int index = _lookFor(from);
	_heap[index] = to;

	_bubbleUp(index);
}

template <class T>
void Heap<T>::deleteItem(T x)
{
	if (_n == 0) return;
	int index = _lookFor(x);
	if (_heap[_n-1] > x) {
		_swap(index, _n-1);
		_bubbleUp(index);
	}
	else
	{
		_swap(index, _n-1);
		_bubbleDown(index);
	}

	_n--;
}

template <class T>
void Heap<T>::printTree() {
    int parity = 0;
	if (_n == 0)
		return;
	int space = pow(2,1 + (int) log2f(_n)),i;
	int nLevel = (int) log2f(_n)+1;
	int index = 0,endIndex;
    int tempIndex;
	
	for (int l = 0; l < nLevel; l++)
	{
		index = 1;
        parity = 0;
		for (i = 0; i < l; i++)
			index *= 2;
		endIndex = index * 2 - 1;
		index--;
        tempIndex = index;
        while (index < _n && index < endIndex) {
            for (i = 0; i < space-1; i++)
                cout << " ";
            if(index==0)
                cout << "|";
            else if (parity)
                cout << "\\";
            else
                cout << "/";
            parity = !parity;
            for (i = 0; i < space; i++)
                cout << " ";
			index++;
		}
        cout << endl;
        index=tempIndex;
		while (index < _n && index < endIndex) {
			for (i = 0; i < (space-1-((int) log10(_heap[index]))); i++)
				cout << " ";
			cout << _heap[index];
			for (i = 0; i < space; i++)
				cout << " ";
			index++;
		}
		
		cout << endl;
		space /= 2;
	}

}






#endif
