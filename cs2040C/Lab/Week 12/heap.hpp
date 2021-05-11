#pragma once
#include <math.h>

#include <iostream>
using namespace std;

#ifndef HEAPHPP
#define HEAPHPP

template <class T>
void Heap<T>::_bubbleUp(int index) {
	int parent;
	T temp;
	while (index) {
		parent = (index - 1) / 2;
		if (  _heap[index] > _heap[parent])
		{
			temp = _heap[parent];
			_heap[parent] = _heap[index];
			_heap[index] = temp;
			index = parent;
		}
		else
			index = 0;
	}
}

template <class T>
void Heap<T>::_bubbleDown(int index) {
	int left = index * 2 + 1;
	int right = left + 1;
	int chosenChild = 0;
	T temp;

	if (left >= _n)
		return;
	if (right >= _n)
	{
		if (  _heap[index] > _heap[left])
			return;
		else
			chosenChild = left;
	}
	else
		chosenChild = _heap[left] > _heap[right] ? left : right;
	
	temp = _heap[index];
	_heap[index] = _heap[chosenChild];
	_heap[chosenChild] = temp;
	_bubbleDown(chosenChild);
}

template <class T>
void Heap<T>::insert(T item) {
	_heap[_n] = item;
	_bubbleUp(_n);
	_n++;
}

template <class T>
T Heap<T>::extractMax() {

	if(_n==0)
		return T();

	T max = _heap[0];
	_heap[0] = _heap[_n - 1];
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
int Heap<T>::_lookFor(T x){
    int i;
    for(i=0;i<_n;i++)
        if (_heap[i] == x)
            return i;
    
    return -1;
}

template <class T>
void Heap<T>::decreaseKey(T from, T to)
{
    int index = _lookFor(from);
    _heap[index] = to;
    _bubbleDown(index);
}


template <class T>
void Heap<T>::increaseKey(T from, T to)
{
    int index = _lookFor(from);
    _heap[index] = to;
    _bubbleUp(index);
}

template <class T>
void Heap<T>::deleteItem(T x)
{
    if(_n==0)
        return;
    int index = _lookFor(x);
    if(index == -1)
        return;
    _heap[index] = _heap[_n-1];
    _n--;
    if(_n==0)
        return;
    if(_heap[index]>_heap[(index - 1) / 2])
        _bubbleUp(index);
    else
        _bubbleDown(index);
}

template <class T>
void Heap<T>::printTree() {
    int parity = 0;
	if (_n == 0)
		return;
	int space = pow(2,1 + (int) log2f( _n)),i;
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
