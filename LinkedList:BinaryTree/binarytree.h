#ifndef BINARYTREE_H
#define BINARYTREE_H

struct TreeNode
{
  int data;
  struct TreeNode* left;
  struct TreeNode* right;
};

/* Alloc a new node with given data. */
struct TreeNode* createTreeNode(int data);

/* Print data for inorder tree traversal on single line,
 * separated with spaces, ending with newline. */
void printTree(struct TreeNode* root);

/* Free memory used by the tree. */
void freeTree(struct TreeNode* root);

/* Print dfs traversal of a tree in visited order,
   each node on a new line,
   where the node is preceeded by the count */
void dfs(struct TreeNode* root);

#endif
