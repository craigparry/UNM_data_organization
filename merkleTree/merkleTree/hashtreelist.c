/**********************************************************************
 * Craig Parry 
 * 
 * This file implements the hashtreelist.h file and is used to make 
 * lists contining hashtrees 
 * this file is dependent on hashtreelist.h, hashtree.h, hashtree.c,
 * and lonesha256.c
 * 
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtreelist.h"

int verifyHashInTree(struct TreeNode* hashtree, char* data);

/************************************* 
 * Each parameter’s type and name: struct TreeNode* root
 * input and/or output: none
 * Function’s return value: struct TreeListNode * 
 * creates a new TreeListNode
 * Function’s algorithm: struct
 *************************************/
struct TreeListNode * createNode(struct TreeNode* root)
{
  struct TreeListNode* temp;
  temp = malloc(sizeof(struct TreeListNode));
  temp->root =root;
  temp->height = 0;
  temp->prev = NULL;
  return temp;
}

/************************************************************************* 
 * Each parameter’s type and name: struct TreeListNode* lastNode,
 * struct TreeNode* root
 * input and/or output: none
 * Function’s return value: struct TreeListNode*
 * Adds a node to the end of the TreeList 
 * Function’s algorithm: linkedlist
 ***************************************************************************/
struct TreeListNode * addNode(struct TreeListNode* lastNode, 
                              struct TreeNode* root)
{
  struct TreeListNode* temp;
  /*return when null tree */
  if(root == NULL) return lastNode;
  /*create new node*/
  temp = createNode(root);
  /* if there is no list present return value as new head*/
  if(lastNode == NULL) return temp;
  /* else make temp the new head and connect previous node*/
  temp->height = lastNode->height +1;
  temp->prev = lastNode;

  return temp;
}

/*************************************************************************** 
 * Each parameter’s type and name: struct TreeListNode* lastNode, char* data
 *  input and/or output: none
 * Function’s return value: int 
 * returns the height of the TreeList at which you can find
 * the data. returns -1 if not found 
 * Function’s algorithm: tree traversal and recursive iteration  
 **************************************************************************/
int findData(struct TreeListNode* lastNode, char* data)
{
  int found;
  found = -1;
  if(lastNode == NULL) return -1;
 
  if(verifyDataInTree(lastNode->root,data))
  {
    return lastNode->height;
  } 
  else
  {
    if(lastNode->prev != NULL)
    {
      found =findData(lastNode->prev, data);
    }
  }
  return found; 
}

/*************************************************************************** 
 * Each parameter’s type and name: struct TreeListNode* lastNode, int height
 * input and/or output: none
 * Function’s return value: struct TreeListNode* 
 * finds the node that contains the height passed to the function
 * Function’s algorithm 
 ***************************************************************************/
struct TreeListNode * findHeight(struct TreeListNode* lastNode, int height)
{
  if(lastNode == NULL) return NULL;
  if(lastNode-> height == height)
  {
    return lastNode;
  } 
  if(lastNode->prev ==NULL) return NULL;
  return findHeight(lastNode->prev,height);
}

/*************************************************************************** 
 * Each parameter’s type and name: struct TreeListNode* lastNode,
 * int height, char* hash
 *  input and/or output: none 
 * Function’s return value: int
 * returns 1 if the tree at the given height has the given hash 
 * at the root and 0 otherwise
 * Function’s algorithm: recursive iteration
 **************************************************************************/
int checkHash(struct TreeListNode* lastNode, int height, char* hash)
{
  if(lastNode == NULL) return 0; 
  lastNode = findHeight(lastNode, height);
  if(lastNode ==NULL) return 0;
  if(!strcmp(lastNode->root->data, hash)) return 1; 
  return 0;
}

/************************************************************************ 
 * Each parameter’s type and name: struct TreeListNode* lastNode
 * input and/or output: none
 * Function’s return value: void 
 * Free memory used by the list.
 * Function’s algorithm: free, recursive iteration, tree traversal
 ************************************************************************/
void freeList(struct TreeListNode* lastNode)
{
  if(lastNode == NULL) return;
  if(lastNode->prev != NULL)
  {
    freeList(lastNode->prev);
  }
  if(lastNode->root != NULL)
  {
    freeTree(lastNode->root);
    lastNode->root = NULL;
  }
  free(lastNode);
  lastNode =NULL;
}
