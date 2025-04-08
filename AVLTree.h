#ifndef AVLTREE_H
#define AVLTREE_H

#include "AVLNode.h"
#include <string>
using namespace std;

class AVLTree{
private:
  AVLNode *root;
  int balance(AVLNode*);
	int height(AVLNode*);
	
	AVLNode* rotateLeft(AVLNode*);
	AVLNode* rotateRight(AVLNode*);
	AVLNode* rotateSq(AVLNode*);
	AVLNode* rotateSq2(AVLNode*);

public:
  AVLTree();
  void insert(string);
  AVLNode* insert(AVLNode*, AVLNode*);
	AVLNode* find(string);
	AVLNode* find(AVLNode*, string);
	int first_count(AVLNode*, string);
	int last_count(AVLNode*, string);
	int rangeSearch(string, string);
	int rangeSearch(AVLNode*, string, string);
	void sortedReturn();
	void sortedReturn(AVLNode*, int);
};

#endif