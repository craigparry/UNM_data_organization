#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"
// #include "binarytree.c"
#include "linkedlist.h"
// #include "linkedlist.c"

/* Makes a simple tree*/
struct TreeNode* makeTestTree(int n,int lim, int count)
{
  struct TreeNode* root = NULL;
  if(n > 1 && count <= lim)
  {
    root = createTreeNode(count);
    // printf("count %d\n",count);
    // printf("left: ");
    root -> left = makeTestTree(n-1, lim, 2*count);
    // printf("right: ");
    root -> right = makeTestTree(n-2, lim, 2*count+1);
    // printf("exit\n");
  }
  return root;
}

int main(void)
{
  struct TreeNode* tree=makeTestTree(4,7,1);

  printf("test tree: ");
  printTree(tree);
  // printf("here: ");
  dfs(tree);
  freeTree(tree);
  tree = NULL;

  tree = makeTestTree(13,41,2);

  printf("second test tree: ");
  printTree(tree);
  dfs(tree);
  freeTree(tree);
  tree = NULL;

  printf("empty test tree: ");
  printTree(tree);
  dfs(tree);

  tree = makeTestTree(43,87, 1);
  printf("third test tree: ");
  printTree(tree);
  dfs(tree);
  freeTree(tree);
  tree = NULL;

  return 0;
}