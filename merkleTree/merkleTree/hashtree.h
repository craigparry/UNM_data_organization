#ifndef HASHTREE_H
#define HASHTREE_H

/* This is the node storing each node in the hash tree*/
struct TreeNode
{
  char* data;
  int isLeaf;
  struct TreeNode* left;
  struct TreeNode* right;
};

/* This is the node storing each node in the list for the proof.*/
struct HashNode
{
  char* hash;
  struct HashNode* next;
};

/* Hashes the data by using a SHA256 hash in the lonesha C library.
 * Saves this as a character array, saved
 * on the heap. Returns a pointer to this character array. */
char* hash(char* data);

/* Alloc a new leaf node with given data and returns a pointer to it.
 * Assume data does not lives on the heap. */
struct TreeNode* createLeafNode(char* data);

/* Alloc a new inner node where the data is the hash of the data of child1
 * plus the data of child2 */
struct TreeNode* createBranchNode(struct TreeNode* child1, struct TreeNode* child2);

/* Verify if the given data is in a leaf node of the tree.
 * Returns a 0 if not, positive number if yes. */
int verifyDataInTree(struct TreeNode* hashtree, char* data);

/* Print data for inorder tree traversal on single line,
 * separated with spaces, ending with newline. */
void printTree(struct TreeNode* root);

/* Free memory used by the tree. */
void freeTree(struct TreeNode* root);

/* Return all the hash values required for the merkle proof
 * They need to be in order from root on down
 * If the data isn't in the tree, returns NULL */
struct HashNode* giveProof(struct TreeNode* hashtree, char* data);





#endif
