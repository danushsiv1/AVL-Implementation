// AVLNode.h

#include <algorithm>
#include <string>
using namespace std;

#ifndef AVLNODE_H
#define AVLNODE_H

class AVLNode
{
public:
	string data;
	AVLNode *leftChild;
	AVLNode *rightChild;
	int height;
	int size;
	AVLNode *parent;

	AVLNode(string d){
		data = d;
		leftChild = NULL;
		rightChild = NULL;
		height = 1;
		size = 1;
		parent = NULL;
	}

	AVLNode(string d, AVLNode* left, AVLNode* right){
		data = d;
		leftChild = left;
		rightChild = right;
		height = 1;
		size = 1;
		parent = NULL;
		if(left){
			height = max(height, left->height + 1);
			size += left->size;
		}
		if(right){
			height = max(height, right->height + 1);
			size += right->size;
		}
	}

	AVLNode* set_left(AVLNode* new_left){
		leftChild = new_left;
		height = 1;
		size = 1;
		if (leftChild){
			height = max(height, leftChild->height + 1);
			size += leftChild->size;
		}
		if(rightChild){
			height = max(height, rightChild->height + 1);
			size += rightChild->size;
		}
		return this;
	}

	AVLNode* set_right(AVLNode* new_right){
		rightChild = new_right;
		height = 1;
		size = 1;
		if(leftChild){
			height = max(height, leftChild->height + 1);
			size += leftChild->size;
		}

		if(rightChild){
			height = max(height, rightChild->height + 1);
			size += rightChild->size;
		}
		return this;
	}

	int balance(){
		int bf = 0;
		if(rightChild) {
			bf += rightChild->height;
		}
		if(leftChild){
			bf -= leftChild->height;
		}
		return bf;
	}

	int get_height(){
		if(this == NULL)
			return 0;
		return height;
	}

};

#endif