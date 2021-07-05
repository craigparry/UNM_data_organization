#ifndef HASHTREELIST_H
#define HASHTREELIST_H

#include "hashtree.h"

struct TreeListNode
{
  struct TreeNode* root;
  int height;
  struct TreeListNode* prev;
};

/*creates a new TreeListNode */
struct TreeListNode* createNode(struct TreeNode* root);

/*adds new node to the Tree List*/
struct TreeListNode* addNode(struct TreeListNode* lastNode, struct TreeNode* root);

/* returns the height of the TreeList at which you can find
 * the data. returns -1 if not found */
int findData(struct TreeListNode* lastNode, char* data);

/* returns 1 if the tree at the given height has the given hash 
 * at the root and 0 otherwise*/
int checkHash(struct TreeListNode* lastNode, int height, char* hash);


/* Free memory used by the list. */
void freeList(struct TreeListNode* lastNode);


#endif
