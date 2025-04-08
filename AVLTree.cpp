// AVLTree.cpp

#include "AVLTree.h"
#include "AVLNode.h"

#include <algorithm>
#include <iostream>
#include <string>

// Constructor initializes AVL
AVLTree::AVLTree(){
	root = NULL;
}

// Returns height of given node.
int AVLTree::height(AVLNode* node){
  if(node == NULL) {
		return 0;
	}
	if(node->leftChild != NULL && node->rightChild != NULL){
		if(node->leftChild->height > node->rightChild->height){
			return node->leftChild->height;
		}
		else {
			return node->rightChild->height;
		}
	} else if (node->leftChild != NULL && node->rightChild == NULL){
		return node->leftChild->height;
	} else {
		return node->rightChild->height;
	}
}

// Returns given node left if unbalanced on right
// Returns new root after rotation.
AVLNode* AVLTree::rotateLeft(AVLNode* node){
	if(node->rightChild == NULL){
		return node;
	} else {
		AVLNode *upper_node = node->parent;
		AVLNode *new_node = node->rightChild;
		AVLNode *temp = node->rightChild->leftChild;
		node->set_right(temp);
		new_node->set_left(node);
		new_node->parent = upper_node;
		return new_node;
	}
}

// Returns given node right if unbalance on left
// Returns new root after rotation
AVLNode* AVLTree::rotateRight(AVLNode* node){
	if(node->leftChild == NULL){
		return node;
	} else {
		AVLNode *upper_node = node->parent;
		AVLNode *new_node = node->leftChild;
		AVLNode *temp = node->leftChild->rightChild;
		node->set_left(temp);
		new_node->set_right(node);
		new_node->parent = upper_node;
		return new_node;
	}
}

// Performs right-left rotation (almost like a square) when node unbalanced
// Rotates right child first, then node to left
AVLNode* AVLTree::rotateSq2(AVLNode* node){
	node->set_right(rotateRight(node->rightChild));
	node = rotateLeft(node);
	return node;
}

// Does same as prior but with a left-right rotation
AVLNode* AVLTree::rotateSq(AVLNode* node){
	node->set_left(rotateLeft(node->leftChild));
	node = rotateRight(node);
	return node;
}

// Inserts a new value into the tree & calls recursive insert method to maintain AVL properties
void AVLTree::insert(string value){
	AVLNode *new_node = new AVLNode(value);
	root = insert(root, new_node);
}

// Recursive insert method that inserts a new node into the tree & ensures balance
AVLNode* AVLTree::insert(AVLNode* current, AVLNode* to_insert){
	if(current == NULL){
		return to_insert;
	}
	if(current->data > to_insert->data){
		current->set_left(insert(current->leftChild, to_insert));
		if(balance(current) < -1){
			if(current->leftChild->data > to_insert->data){
				return rotateSq(current);
			} else {
				return rotateRight(current);
			}
		}
		current->leftChild->parent = current;
		return current;
	} else if (current->data < to_insert->data){
		current->set_right(insert(current->rightChild, to_insert));
		if(balance(current) > 1){
			if(current->rightChild->data > to_insert->data){
				return rotateSq2(current);
			} else {
				return rotateLeft(current);
			}
		}
		return current;
	}
	return current;
}

// Counts the first number of nodes before given end value.
int AVLTree::first_count(AVLNode* current, string end_value){
	if(current == NULL){
		return 0;
	}
	if(current->data > end_value){
		return first_count(current->leftChild, end_value);
	}
	int left_count = (current->leftChild ? current->leftChild->size : 0);
	int right_count = first_count(current->rightChild, end_value);
	return 1 + left_count + right_count;
}

// Counts number of nodes after given end value.
int AVLTree::last_count(AVLNode* current, string start_value){
	if(current == NULL){
		return 0;
	}

	if(current->data < start_value){
		return last_count(current->rightChild, start_value);
	}

	int left_count = (current->rightChild ? current->rightChild->size : 0);
	int right_count = last_count(current->leftChild, start_value);

	return 1 + right_count + left_count;
}

// Parses through range of values between start/end values
int AVLTree::rangeSearch(string start_value, string end_value){
  return rangeSearch(root, start_value, end_value);
}

// Recursive function to find # of nodes that fall between given start/end values
int AVLTree::rangeSearch(AVLNode* current, string start_value, string end_value){
	if(current == NULL){
		return 0;
	}
	int self = (current->data == start_value || current->data == end_value) ? 1 : 0;
	if(current->data <= start_value){
		return self + rangeSearch(current->rightChild, start_value, end_value);
	} else if(current->data >= end_value){
		return self + rangeSearch(current->leftChild, start_value, end_value);
	}
  return 1 + first_count(current->rightChild, end_value) + last_count(current->leftChild, start_value);
}

// Calculates balance factor
int AVLTree::balance(AVLNode* node){
	int bf = 0;
	if (node->rightChild){
		bf += node->rightChild->height;
	}
	if (node->leftChild){
		bf -= node->leftChild->height; // subtracts height of left from right
	}
	return bf;
}

// Finds a node with given data
AVLNode* AVLTree::find(string value){
	return find(root, value);
}

// If data exists, it responds with corresponding node
AVLNode* AVLTree::find(AVLNode* current, string value){
	if (current == NULL || current->data == value){
		return current;
	}
	if(current->data > value){
		return find(current->leftChild, value);
	} else if (current->data < value){
		return find(current->leftChild, value);
	} else {
		return NULL;
	}
}

// Returns sorted output
void AVLTree::sortedReturn(){
  sortedReturn(root, 1);
}

// Recursive function to print tree in order.
void AVLTree::sortedReturn(AVLNode* current, int level){
	if(current == NULL){
		return;
	}
	int nextLevel = level + 1;
	sortedReturn(current->leftChild, nextLevel);
	sortedReturn(current->rightChild, nextLevel);
}