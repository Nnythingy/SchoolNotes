#pragma once
#include "HashTable.h"

HashTable::HashTable(int n) {

	//initially, populate hashtable with 0s
	N = 0;
	size = n;
	for (int i = 0; i < n; i++) {
		ht[i] = EMPTY;
	}
	for (int i = n; i < 100; i++) {
		delete[] ht[i];
	}
	return;
}

int HashTable::getKey(int n) {
	int key = 0;
	if (h(n) > size) {
		key = n % size;
	}
	else {
		key = h(n);
	}
	return key;
}

void HashTable::insertWithoutCollision(int n) {

	int key = getKey(n);
	ht[key] = n;
	N++;
	return;
}

void HashTable::deleteWithoutCollision(int n) {
	int key = getKey(n);

	if (ht[key] != EMPTY) {
		ht[key] = DEL;
		N--;
	}
	return;
}

bool HashTable::existWithoutCollision(int n) {
	int key = getKey(n);

	if (ht[key] == n) {
		return true;
	}
	return false;
}

void HashTable::insertWithCollision(int n) {
	int key = getKey(n);

	if (ht[key] == EMPTY) {
		ht[key] = n;
		N++;
	}
	else {
		while (key < size) {
			if (ht[key] == EMPTY) {
				ht[key] = n;
				N++;
				return;
			}
			key++;
		}
	}

	return;
}

//n does not necasarrily exist in the hash table
void HashTable::deleteWithCollision(int n) {

	if (!existWithCollision(n)) {
		return;
	}

	int key = getKey(n);
	while (key < size) {
		if (ht[key] == n) {
			ht[key] = DEL;
			N--;
			return;
		}
		key++;
	}

	return;
}

bool HashTable::existWithCollision(int n) {
	int key = getKey(n);

	while (key < size) {
		if (ht[key] == n) {
			return true;
		}
		key++;
	}
	return false;
}

void HashTable::printHashTable() {
	
	cout << "Current hash table: " << endl;
	for (int i = 0; i < size; i++) {
		cout << ht[i] << " ";
	}
	cout << endl;
}

