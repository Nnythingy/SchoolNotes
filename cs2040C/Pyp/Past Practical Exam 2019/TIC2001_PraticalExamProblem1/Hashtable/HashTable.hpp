#pragma once
#include "HashTable.h"

HashTable::HashTable(int n) {
	//initially, populate hashtable with 0s
	N = n;
	for (int i = 0; i < n; i++)
	{
		ht[i] = 0;
	}
	return;
}



void HashTable::insertWithoutCollision(int n) {
	int hashvalue = h(n);
	int index = hashvalue % N;
	ht[index] = n;
	return;
}

void HashTable::deleteWithoutCollision(int n) {
	int hashvalue = h(n);
	int index = hashvalue % N;
	if (ht[index] == n) ht[index] = -1;
	return;
}

bool HashTable::existWithoutCollision(int n) {
	int hashvalue = h(n);
	int index = hashvalue % N;
	if (ht[index] == n) return true;
	return false;
}

void HashTable::insertWithCollision(int n) {
	int hashvalue = h(n);
	int index = hashvalue % N;
	while (ht[index] > 0) {
		if (ht[index] == n)	return;
		++index%N;
	}
	ht[index] = n;
	return;
}

//n does not necasarrily exist in the hash table
void HashTable::deleteWithCollision(int n) {

	int hashvalue = h(n);
	int index = hashvalue % N;
	while (ht[index] != 0) {
		if (ht[index] == n) { ht[index] = -1; return; }
		++index%N;
	}
	return;
}

bool HashTable::existWithCollision(int n) {
	
	int hashvalue = h(n);
	int index = hashvalue % N;
	while (ht[index] != 0) {
		if (ht[index] == n) return true;
		++index%N;
	}
	return false;
}

void HashTable::printHashTable() {
	
	cout << "Current hash table: " << endl;
	for (int i = 0; i < N; i++) {
		cout << ht[i] << " ";
	}
	cout << endl;
}

