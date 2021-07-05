/************************************************************************** 
 * Craig Parry
 * this file is used to test the binarytree.c file and needs to be compiled
 * with the binarytree.c, binarytree.h, linkedlist.c and linkedlist.h files
 * 
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"
#include "linkedlist.h"

/* Makes a simple tree*/
struct TreeNode* makeTestTree(int n,int lim, int count)
{
  struct TreeNode* root = NULL;
  if(n > 1 && count <= lim)
  {
    root = createTreeNode(count);
    root -> left = makeTestTree(n-1, lim, 2*count);
    root -> right = makeTestTree(n-2, lim, 2*count+1);
  }
  return root;
}

int main(void)
{
 
  struct TreeNode* tree; 
  tree =NULL;
  /*testing function on null/empty trees */
  printf("Empty Tree: ");
  printTree(tree);
  /*free empty tree*/
  freeTree(tree);
  printf("Empty dfs: \n");
  dfs(tree);
  /*fills tree and tests functions*/
  tree = makeTestTree(15,60,1);

  printf("Filled tree: ");
  printTree(tree);
  printf("Filled dfs: \n");
  dfs(tree);
  freeTree(tree);
  tree = NULL;

  return 0;
}
