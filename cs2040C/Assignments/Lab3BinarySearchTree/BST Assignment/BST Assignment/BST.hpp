#pragma once
#ifndef BSTHPP
#define BSTHPP
#include "BST.h"

template <class T>
int BinarySearchTree<T>::_balanceFactor(TreeNode<T>* node) {
	if (!node->_right && !node->_left) {
		return 0;
	}
	else if (!node->_left)
	{
		return (-1 - node->_right->_height);
	}
	else if(!node->_right)
	{
		return (node->_left->_height - (-1));
	}
	
	return (node->_left->_height - node->_right->_height);
}

template <class T>
int BinarySearchTree<T>::_maxHeight(TreeNode<T>* current) {
	int leftHeight = -1;
	int rightHeight = -1;

	if (current->_left) {
		leftHeight = current->_left->_height;
	}
	if (current->_right) {
		rightHeight = current->_right->_height;
	}

	if (leftHeight > rightHeight) {
		return (leftHeight + 1);
	}
	return (rightHeight + 1);
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_insert(TreeNode<T>* current, T x) {
	if (current->_item > x)
	{
		if (current->_left)
		{
			current->_left = _insert(current->_left, x);
		}
		else
		{
			current->_left = new TreeNode<T>(x);
			_size++;
		}
	}
	else if (x > current->_item) {
		if (current->_right)
		{
			current->_right = _insert(current->_right, x);
		}
		else
		{
			current->_right = new TreeNode<T>(x);
			_size++;
		}
	}
	else
		return current;

	current->_height = _maxHeight(current);
	if (_balanceFactor(current) > 1) {
		if (_balanceFactor(current->_left) < -1)
		{
			current->_left = _leftRotation(current->_left);
		}
		current = _rightRotation(current);
	}
	else if (_balanceFactor(current) < -1)
	{
		if (_balanceFactor(current->_right) > 1)
		{
			current->_right = _rightRotation(current->_right);
		}
		current = _leftRotation(current);
	}

	return current;
}

template <class T>
void BinarySearchTree<T>::insert(T x) {
	if (_root == NULL){
		_root = new TreeNode<T>(x);
		_size++;
	}
	else {
		_root = _insert(_root, x);
	}
}

template <class T>
bool BinarySearchTree<T>::_exist(TreeNode<T>* node, T x) {
	if (node->_item == x) {
		return true;
	}
	else if (x < node->_item && node->_left) {
		_exist(node->_left, x);
	}
	else if (x > node->_item && node->_right) {
		_exist(node->_right, x);
	}
	else
	{
		return false;
	}
}

template <class T>
bool BinarySearchTree<T>::exist(T x) {
	if (_root) {
		return _exist(_root, x);
	}
	return false;
}

template <class T>
T BinarySearchTree<T>::searchMax() {
	TreeNode<T>* current = _root;
	while (current->_right) {
		current = current->_right;
	}
	return (current->_item);
}

template <class T>
T BinarySearchTree<T>::searchMin() {
	TreeNode<T>* current = _root;
	while (current->_left) {
		current = current->_left;
	}
	return (current->_item);
}

template <class T>
T BinarySearchTree<T>::_successor(TreeNode<T>* node,T x, T max) {
	if (node->_item > x) {
		if (node->_left) {
			_successor(node->_left, x, node->_item);
		}
		else
		{
			return (node->_item);
		}
	} else {
		if (node->_right) {
			_successor(node->_right, x, max);
		}
		else if (!node->_left && !node->_right && !(node->_item > x))
		{
			return max;
		}
	}
}

template <class T>
T BinarySearchTree<T>::successor(T x)
{
	return _successor(_root, x, 0);
	/*
	* TreeNode<T>* current = _root;
	* TreeNode<T>* temp = NULL; // Will contain node with _item last known to be > x
	* while (current) {  // Find node containing _item closest to x
	*	if (current->_item > x) {
	*		if (!current->_left) {
	*			break;
	*		}
	*		temp = current;
	*		current = current->_left;
	*	}
	*	else {
	*		if (!current->_right) {
	*			break;
	*		}
	*		current = current->_right;
	*	}
	* }
	*
	* if (current->_item > x) {  // If node with _item closest to x is > x then return it
	*	return current->_item;
	* }
	* else if (current->_right) {  // If node with _item closest to x but < x then return min value in right subtree of node
	*	while (current->_left) {
	*		current = current->_left;
	*	}
	*	return current->_item;
	* }
	* else if (temp) {  // If node with _item closest to x but < x and no right subtree then return last known _item > x
	*	return temp->_item;
	* }
	* return NULL; // Returns NULL if no successor is found
	*/
}


template <class T>
TreeNode<T>* BinarySearchTree<T>::_leftRotation(TreeNode<T>* node)
{
	TreeNode<T>* current = node->_right;
	node->_right = current->_left;
	current->_left = node;

	//update height
	node->_height = _maxHeight(node);
	current->_height = _maxHeight(current);

	return current;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_rightRotation(TreeNode<T>* node)
{
	TreeNode<T>* current = node->_left;
	node->_left = current->_right;
	current->_right = node;

	//update height
	node->_height = _maxHeight(node);
	current->_height = _maxHeight(current);

	return current;
}

template <class T>
void BinarySearchTree<T>::printTree(bool withHeight) {
	_printTree(0, _root, withHeight);
}

template <class T>
void BinarySearchTree<T>::preOrderPrint() {
	_preOrderPrint(_root);
	cout << endl;
}

template <class T>
void BinarySearchTree<T>::inOrderPrint() {
	_inOrderPrint(_root);
	cout << endl;
}

template <class T>
void BinarySearchTree<T>::postOrderPrint() {
	_postOrderPrint(_root);
	cout << endl;
}

template <class T>
void BinarySearchTree<T>::_preOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	cout << node->_item << " ";
	_preOrderPrint(node->_left);
	_preOrderPrint(node->_right);
}

template <class T>
void BinarySearchTree<T>::_inOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	_inOrderPrint(node->_left);
	cout << node->_item << " ";
	_inOrderPrint(node->_right);

}

template <class T>
void BinarySearchTree<T>::_postOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	_postOrderPrint(node->_left);
	_postOrderPrint(node->_right);
	cout << node->_item << " ";
}

template <class T>
void BinarySearchTree<T>::_printTree(int indent, TreeNode<T>* node, bool withHeight) {

	if (!node)
		return;

	if (node->_right)
		_printTree(indent + 2, node->_right, withHeight);
	for (int i = 0; i < indent; i++)
		cout << "  ";
	cout << node->_item;
	if (withHeight)
		cout << "(h=" << node->_height << ")";
	cout << endl;
	if (node->_left)
		_printTree(indent + 2, node->_left, withHeight);


};

template <class T>
void BinarySearchTree<T> ::_destroySubTree(TreeNode<T>* node)
{
	if (node->_left)
		_destroySubTree(node->_left);
	if (node->_right)
		_destroySubTree(node->_right);
	delete node;
}

template <class T>
BinarySearchTree<T> :: ~BinarySearchTree()
{
	if (_root)
		_destroySubTree(_root);
}


#endif
