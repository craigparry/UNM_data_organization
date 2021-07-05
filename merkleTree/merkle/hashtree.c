/********************************************************************* 
 * Craig Parry
 * 
 * this file is used to create hash trees and implements the functions
 * defined in hashtree.h and is dependent on lonesha256.h for the 
 * hashing function. This file can be tested with testhashtree.c
 * 
 ********************************************************************/

/* at this point the only major error that I'm aware of is that when hashing two 
hashed strings together the output does not match the online SHA256 calulator:
for instance when I hash Pug or pig, the output matches the calculator, but when
concatonating their hashes together and hashing that string it does not match the 
calculator output. Although it is a consistent output when compared to the same 
hash sequence with my progam. Checked this and it is probably due to the fact 
that when printing the values I was using the online calculator with Hex values
instead of character values.(the hash should be working fine) */

#define LONESHA256_STATIC
#include <stdio.h>
#include <stdlib.h>
#include "lonesha256.h"
#include "hashtree.h"
#include <string.h>

void printTreeHelper(struct TreeNode* root);
struct HashNode * giveProofHelper(struct TreeNode* hashtree,
                                  char* data, struct HashNode* node);
struct HashNode * createHashNode(char* data);
void removeEnd(struct HashNode * list, char* data);

/****************************************************************** 
 * Each parameter’s type and name: char* data
 * input and/or output: none
 * Function’s return value: char* 
 * Hashes the data by using a SHA256 hash in the lonesha C library.
 * Saves this as a character array, saved
 * on the heap. Returns a pointer to this character array.
 * Function’s algorithm: lonesha256 hash
 ******************************************************************/
char* hash(char* data)
{
  /* run the data through the hash function and malloc the memory needed 
   to store the data after it was hashed on the heap
   maybe try storing this and freeing it before implementing other functions
   so we know it is working and not leaking memory*/
  unsigned char* temp;
  if(data == NULL)
  {
    temp =NULL;
    return (char*)temp;
  } 
  temp = calloc(33,sizeof(unsigned char));
  if(!lonesha256(temp,(const unsigned char*)data,strlen(data)))
  {
    return (char*) temp;
  }
  
  return NULL;
}

/********************************************************************* 
 * Each parameter’s type and name: char* data
 * input and/or output: none
 * Function’s return value: struct TreeNode*
 * Alloc a new leaf node with given data and returns a pointer to it.
 * Assume data does not lives on the heap.
 * Function’s algorithm: struct, heap allocation
 ********************************************************************/
struct TreeNode * createLeafNode(char* data)
{ 
  /* leaf is the node containing the data 
  node at the very bottom of the tree
  calloc storage for data on the heap and for the treenode
  assign values */

  struct TreeNode* temp;
  
  temp = malloc(sizeof(struct TreeNode));
  temp->data = calloc(strlen(data)+1,sizeof(char)); 
 
  strcpy(temp->data, data);
  temp->isLeaf = 1;
  temp->left = NULL;
  temp->right = NULL;

  return temp;
}

/************************************************************************** 
 * Each parameter’s type and name: struct TreeNode* child1,
 * struct TreeNode* child2
 * input and/or output: none
 * Function’s return value struct TreeNode*
 * Alloc a new inner node where the data is the hash of the data of child1
 * plus the data of child2 
 * Function’s algorithm: struct, heap allocation
 *************************************************************************/
struct TreeNode * createBranchNode(struct TreeNode* child1,
                                   struct TreeNode* child2)
{
  /* branch is the connection off of the leaf that contains the hash 
  it looks like each hash node will point to the left and right children */

  struct TreeNode* leftNode;
  struct TreeNode* rightNode;
  struct TreeNode* newNode;
  char* tempStr;
  tempStr = "";
  leftNode =NULL;
  rightNode =NULL;
  newNode =NULL;

  if(child1 == NULL && child2 == NULL) return NULL;
  /*allocate memory to hold temp string for concatonation*/
  tempStr = calloc(66,sizeof(char));
  /*allocates memory for new node*/
  newNode = malloc(sizeof(struct TreeNode));
  /*creates new branch to hold hash of the leaf and points that node to leaf*/
  if(child1 !=NULL && child1->isLeaf == 1 )
  {
    leftNode = malloc(sizeof(struct TreeNode));
    leftNode->left = child1;
    leftNode->right = NULL;

    leftNode->isLeaf = 0;
    leftNode->data = hash(child1->data);
    newNode->left = leftNode;
  } 
  /*if the child isnt a leaf then just connect the branches normally*/
  else
  {
    leftNode = child1;
    newNode->left =child1;
  }
  /*creates new branch to hold hash of the leaf and points that node to leaf*/
  if(child2 != NULL && child2->isLeaf == 1)
  {
    rightNode = malloc(sizeof(struct TreeNode));
    rightNode->left = child2;
    rightNode->right = NULL;

    rightNode->isLeaf = 0;
    rightNode->data = hash(child2->data);
    newNode->right = rightNode;
  } 
  /*if the child isnt a leaf then just connect the branches normally*/
  else
  {
    rightNode = child2;
    newNode->right = child2;
  }
  /* makes sure the children assigned to newNode were not NULL*/
  if(newNode->right !=NULL && newNode->left != NULL)
  {
    newNode->isLeaf = 0;
    /*need to concatonate each string to a buffer before sending 
     the concatonated hashes into the hash function or else segfault
    becuase we cannot manipilate the string literals that are malloced*/
    tempStr = strcat(tempStr, leftNode->data);
    tempStr = strcat(tempStr, rightNode->data);
    newNode->data = hash(tempStr); 
    free(tempStr);
    return newNode;
  }

  free(tempStr);
  /*if either left or right of newNode is NULL send the non-NULL
  return the non-NULL node as the root*/
  if(newNode->right != NULL) 
  { 
    free(newNode);
    return rightNode;
  }
  if(newNode->left != NULL)
  { 
    free(newNode);
    return leftNode;
  } 
  return newNode;
}


/************************************************************************ 
 * Each parameter’s type and name: struct TreeNode* hashtree, char* data
 * input and/or output:none
 * Function’s return value: int 
 * Verify if the given data is in a leaf node of the tree.
 * Returns a 0 if not, positive number if yes.
 * Function’s algorithm: tree traversal dfs
 ***********************************************************************/
int verifyDataInTree(struct TreeNode* hashtree, char* data)
{
  int found;
  found =0;
  if(hashtree == NULL) return 0;  
  /*just wrote this need to test it*/
  if(hashtree->left !=NULL)
  { 
    /*verify left root and its children with recusion*/
    found = verifyDataInTree(hashtree->left, data);
  } 
    if(found == 1) return found;

  if(hashtree->right !=NULL)
  {
     /*verify right root and its children with recusion*/
    
    found = verifyDataInTree(hashtree->right, data);
  } 
  if(found == 1) return found; 

  if(hashtree->isLeaf == 1 && !strcmp(data, hashtree->data))  return 1;
  
  return found;
}


/************************************************************************ 
 * Each parameter’s type and name: struct TreeNode* root
 *  input and/or output: outputs the tree data in order of tree traversal
 * (left , right and then root) prints on a single line, separated with
 * spaces, ending with newline (char*)
 * Function’s return value: void 
 * Print data for inorder tree traversal on single line,
 * separated with spaces, ending with newline.
 * Function’s algorithm: recursive traversal 
 **********************************************************************/
void printTree(struct TreeNode* root)
{
  if(root == NULL)
  {
    printf("\n");
    return;
  }
  /*calling a helper cause it would have been redundant
    to write the same code here with a printline at the end*/
  printTreeHelper(root);
  /*since first node we have to print newline at the end*/
  printf("\n");
}

/************************************************************************ 
 * Each parameter’s type and name: struct TreeNode* root
 *  input and/or output: outputs the tree data in order of tree traversal
 * (left , right and then root) prints on a single line, separated with
 * spaces, ending with newline (integer data)
 * Function’s return value: void 
 * This funciton is a recursive helper Prints data for inorder tree 
 * traversal on single line, separated with spaces, ending with newline.
 * Function’s algorithm: recursive traversal 
 **********************************************************************/
void printTreeHelper(struct TreeNode* root)
{
  int k;
  /*if left branch is not null call it*/
  if(root->left !=NULL)
  {
    printTreeHelper(root->left); 
  } 
  /*once left branch has returned to this node print this node*/
  if(root->isLeaf == 1) 
  {
    printf("%s ",root->data);
  } 
  else 
  {
    k =0;
    for (k = 0; k < 32; k++)
    {
      printf("%02x", (unsigned char)root->data[k]);
    }
    printf(" ");
    }
  /*and call the right branch if it is not null*/
  if(root->right!=NULL)
  {
    printTreeHelper(root->right);
  }
}

/************************************************************ 
 * Each parameter’s type and name: struct TreeNode* root 
 * input and/or output: none
 * Function’s return value: void 
 * Free memory used by the tree.
 * Function’s algorithm: tree traversal, free memory
 ***********************************************************/
void freeTree(struct TreeNode* root)
{
  if(root == NULL) return;  
  /*just wrote this need to test it*/
  if(root->left !=NULL)
  { 
    /*free left root and its children with recusion*/
    freeTree(root->left);
    root->left =NULL;
  } 
  if(root->right !=NULL)
  {  
     /*free right root and its children with recusion*/
    freeTree(root->right);
    root->right =NULL;
  } 
  /*free root of the tree*/
  free(root->data);
  free(root);
  root =NULL;
}

/*********************************************************************** 
 * Each parameter’s type and name: struct TreeNode* hashtree, char* data
 * input and/or output: none 
 * Function’s return value: struct HashNode*  
 * Return all the hash values required for the merkle proof
 * They need to be in order from root on down
 * If the data isn't in the tree, returns NULL
 * Function’s algorithm: HashTrees
 **********************************************************************/
struct HashNode * giveProof(struct TreeNode* hashtree, char* data)
{
  struct HashNode* temp;
  temp = NULL;
  if(hashtree ==NULL) return NULL; 
  if(!verifyDataInTree(hashtree,data)) return NULL;

  temp =giveProofHelper(hashtree, data, temp); 
  removeEnd(temp,data);
   /*so data is verfied that it is in the tree
   add node to the list node->next will point to the next node in the list
   call giveProof recursively or with a helper
  check the left branch for the data if the data is present in the left branch
   add right branch to the proof */
  return temp;
}

/*********************************************************************** 
 * Each parameter’s type and name: struct HashNode* list, char* data
 * input and/or output: none 
 * Function’s return value: void 
 * removes the data from the end of the HashNode list because it's not 
 * needed for the Merkle Proof
 * Function’s algorithm: recursive iteration
 **********************************************************************/
void removeEnd(struct HashNode * list, char* data)
{
  if(list->next != NULL)
  {
    if(list->next->next == NULL && !strcmp(list->next->hash, data))
    {
      free(list->next->hash);
      free(list->next);
      list->next =NULL;
      return;
    }
    removeEnd(list->next,data);
  } 
}

/************************************************************************ 
 * Each parameter’s type and name: struct TreeNode* hashtree,
 * char* data, struct HashNode* node)
 *  input and/or output:none 
 * Function’s return value: struct HashNode*
 * recursively searches the tree for the data passed to the function. 
 * Once that data is found then it adds the hashes needed to reproduce the 
 * merkle root including the data that was present.
 * Function’s algorithm: DFS
 **************************************************************************/
struct HashNode * giveProofHelper(struct TreeNode* hashtree, char* data,
                                   struct HashNode* node)
{
  struct HashNode* temp;
  struct HashNode* opposite;
  /*create node if the leaf is found*/
  if(hashtree->isLeaf ==1 && !strcmp(data, hashtree->data))
  { 
    temp = createHashNode(data); 
    return temp;
  } 
  if(hashtree->left != NULL)
  { 
    /*then traverses the left branch after its done searching the right 
    branch of the node*/
    node = giveProofHelper(hashtree->left,data,node);
    /*return node containing the leaf*/
    if(node != NULL && hashtree->left->isLeaf)
    {
      return node;
    } 
    /* create nodes containing the hashes needed to make the merkle root*/
    if(node!= NULL)
    {
      /*creates node containing opposite hash to the one returned and 
      a node containing the current root*/
      temp =createHashNode(hashtree->data); 
      opposite = createHashNode(hashtree->right->data); 
      opposite->next = node;
      temp->next = opposite;
      return temp;
    } 
  }

  if(hashtree->right != NULL)
  {
    /*traverses right branch and its children */
    node = giveProofHelper(hashtree->right,data,node);
    /*create nodes containing the hashes needed to recreate the merkle root*/
    if(node!= NULL)
    { 
      /*creates node containing opposite hash to the one returned and 
      a node containing the current root*/
      temp =createHashNode(hashtree->data); 
      opposite = createHashNode(hashtree->left->data); 
      opposite->next = node;
      temp->next = opposite;
      return temp;
    } 
  } 
  /*return the stack of visited nodes*/
  return NULL;
}

/********************************************************************** 
 * Each parameter’s type and name: char* data 
 * input and/or output: none 
 * Function’s return value: struct HashNode* 
 * creates a HashNode and allocates memory for it on the heap
 * Function’s algorithm: malloc
 **********************************************************************/
struct HashNode * createHashNode(char* data)
{
  struct HashNode * temp;
  temp = malloc(sizeof(struct HashNode));
  temp->hash = calloc(33,sizeof(unsigned char));
  strcpy(temp->hash, data);
  temp->next =NULL;
  return temp;
} 
