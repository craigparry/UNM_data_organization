#ifndef READTREE_H
#define READTREE_H

#include "hashtree.h"

/*Reads in the contents of a file. Each line contains a leaf node.*/
struct TreeNode* putFileIntoHashTree(char* filename);

/*Reads in the contents of a file. Each line contains a filename of an element
  in the hashtree list. This will use putFileIntoHashTree as a helper function.*/
struct TreeListNode* readInFiles(char* filename);

#endif
