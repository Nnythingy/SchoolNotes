#pragma once
#include <iostream>
using namespace std;

template <class T>
class BinarySearchTree;

template <class T>
class TreeNode {
private:
	T _item;
	TreeNode<T>* _left;
	TreeNode<T>* _right;
	int _height;
public:
	TreeNode(T x) { _left = _right = NULL; _item = x; _height = 0; };

	friend BinarySearchTree<T>;
};

template <class T>
class BinarySearchTree {
private:
	int _size;
	TreeNode<T>* _root;
	void _printTree(int indent, TreeNode<T>*, bool withHeight);
	void _inOrderPrint(TreeNode<T>* node);
	void _postOrderPrint(TreeNode<T>* node);
	void _preOrderPrint(TreeNode<T>*);
	
	TreeNode<T>* _insert(TreeNode<T>* current, T x);
	bool _exist(TreeNode<T>* current, T x);
	T _successor(TreeNode<T>*, T, T);
	TreeNode<T>* _rightRotation(TreeNode<T>*);
	TreeNode<T>* _leftRotation(TreeNode<T>*);
    void _destroySubTree(TreeNode<T>*);
	int _balanceFactor(TreeNode<T>*);
	int _maxHeight(TreeNode<T>*);
    
public:
	BinarySearchTree() { _root = NULL; _size = 0; }
	~BinarySearchTree();
	int size() { return _size; };
	void insert(T);
	void printTree(bool withHeight = 1);
	void preOrderPrint();
	void inOrderPrint();
	void postOrderPrint();
	T searchMax() ;
	T searchMin();
	bool exist(T x);
	T successor(T);
};

#include "BST.hpp"
