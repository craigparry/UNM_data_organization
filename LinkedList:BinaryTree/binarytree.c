/************************************************************************** 
 * Craig Parry
 * this file is used to create binarytrees holding integer data and needs
 * to be compiled with the binarytree.h, linkedlist.c and linkedlist.h files
 * 
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"
#include "linkedlist.h"

void printTreeHelper(struct TreeNode* root);
struct ListNode * dfsHelper(struct TreeNode* root, struct ListNode* stack);

/****************************************************************** 
 * Each parameter’s type and name: int data
 * input and/or output: none 
 * Function’s return value: struct TreeNode*
 * creates a new TreeNode and allocates memory for it on the heap
 * Function’s algorithm: structs
 *****************************************************************/
struct TreeNode * createTreeNode(int data)
{
  struct TreeNode* temp;
  /*allocate memory on the heap*/
  temp = malloc(sizeof(struct TreeNode));

  /*initialize pointers to NULL*/
  temp->left = NULL;
  temp->right = NULL;
  temp->data = data;

  return temp;
}

/************************************************************************ 
 * Each parameter’s type and name: struct TreeNode* root
 *  input and/or output: outputs the tree data in order of tree traversal
 * (left , right and then root) prints on a single line, separated with
 * spaces, ending with newline (integer data)
 * Function’s return value: void 
 * This funciton traverses the tree in order printing the left branch, 
 * right branch, and then the root. prints on a single line, separated 
 * with spaces, ending with newline
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
 * This funciton is a recursive helper function to traverses the tree 
 * in order printing the left branch, right branch, and then the root.
 * prints on a single line, separated with spaces, ending with newline
 * Function’s algorithm: recursive traversal 
 **********************************************************************/
void printTreeHelper(struct TreeNode* root)
{
  /*if left branch is not null call it*/
  if(root->left !=NULL)
  {
    printTreeHelper(root->left); 
  } 
  /*once left branch has returned to this node print this node*/
  printf("%d ",root->data);
  /*and call the right branch if it is not null*/
  if(root->right!=NULL)
  {
    printTreeHelper(root->right);
  }
}

/********************************************************************** 
 * Each parameter’s type and name: struct Treenode* root
 * input and/or output: none 
 * Function’s return value: void
 * This function traverses the tree recursively and frees the allocated 
 * memory for each node
 * Function’s algorithm: recursive tree traversal  
 **********************************************************************/
/* Free memory used by the tree. */
void freeTree(struct TreeNode* root)
{
  if(root == NULL) return;  
  /*just wrote this need to test it*/
  if(root->left !=NULL)
  { 
    /*free left root and its children with recusion*/
    freeTree(root->left);
  } 
  if(root->right !=NULL)
  {
     /*free right root and its children with recusion*/
    freeTree(root->right);
  } 
  /*free root of the tree*/
  free(root);
  root =NULL;
}

/************************************************************************ 
 * Each parameter’s type and name: struct TreeeNode* root 
 * input and/or output: Prints dfs traversal of a tree in visited order,
 * each node on a new line, where the node is preceeded by the count.
 * searches the tree right branch before left
 * using a stack to keep track of visited nodes 
 * Function’s return value: void
 * this function prints dfs traversal of a tree in visited order,
 * each node on a new line, where the node is preceeded by the count
 * Function’s algorithm: depth first tree traversal
 **********************************************************************/
void dfs(struct TreeNode* root)
{ 
  int i; 
  int length;
  struct ListNode* temp = NULL;
  if(root == NULL)return;
  /*call helper function if not null*/
  temp = dfsHelper(root,temp);
  /*stack is a LIFO data structure so we need to reverse the stack 
  to access the first item visited with the popStack funciton*/
  reverseList(&temp);
  /*uses the listlength to keep track of a count of which count 
  a node was visited at and pops that node of the stack printing 
  the count before the nodes data*/
  length =listLength(temp);
  for(i=1; i <= length; i++)
  { 
    printf("%d: %d\n",i,popStack(&temp));
  } 
}

/************************************************************************ 
 * Each parameter’s type and name: struct TreeeNode* root,
 * struct ListNode* stack
 * input and/or output: Prints dfs traversal of a tree in visited order,
 * each node on a new line, where the node is preceeded by the count
 * searches the tree right branch before left
 * using a stack to keep track of visited nodes 
 * Function’s return value: void
 * this function prints dfs traversal of a tree in visited order,
 * each node on a new line, where the node is preceeded by the count
 * Function’s algorithm: depth first tree traversal
 **********************************************************************/
struct ListNode * dfsHelper(struct TreeNode* root, struct ListNode* stack)
{ 
  /*pushes the visited node onto the stack of visited nodes*/
  stack = pushStack(stack, root->data);
  if(root->right != NULL)
  {
    /*traverses right branch and its children before left*/
    stack = dfsHelper(root->right,stack);
  } 

  if(root->left != NULL)
  {
    /*then traverses the left branch after its done searching the right 
    branch of the node*/
    stack = dfsHelper(root->left,stack);
  }
  /*return the stack of visited nodes*/
  return stack;
} 
