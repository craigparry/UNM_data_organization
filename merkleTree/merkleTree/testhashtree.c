/************************************************************************** 
 * Craig Parry 
 * 
 * This file tests that the file hashtree.c implements hashtree.h correctly
 * it is depended on hashtree.c hashtree.h and lonesha256.h
 * 
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "hashtree.h"
#include <string.h>

void printProof(struct HashNode* list);
void freeProof(struct HashNode* list);
void printHash(char* hash);

/********************************************************************* 
 * Each parameter’s type and name: struct HashNode* list
 *  input and/or output: prints the Merkle Proof created in giveproof 
 * Function’s return value: void 
 * This function iterates the HashNode List recrusively and prints the 
 * hashes contained by the nodes 
 * Function’s algorithm: recursive iteration 
 ********************************************************************/
void printProof(struct HashNode* list)
{
  if(list == NULL) return;

  printHash(list->hash);
  printf(" ");
  printProof(list->next);
  if(list->next ==NULL) printf("\n");
} 

/*********************************************************************** 
 * Each parameter’s type and name: char* hash
 * input and/or output: prints the hash value  
 * Function’s return value: void
 * Prints the hash value of the char* that has been passed through the 
 * lonesha256 hashing function in hex representation 
 * Function’s algorithm: printf
 ***********************************************************************/
void printHash(char* hash)
{ 
  int k;
  k =0;
  for (k = 0; k < 32; k++)
  {
    printf("%02x", (unsigned char)hash[k]);
  }
  printf(" ");
} 
/*********************************************************************** 
 * Each parameter’s type and name: struct HashNode* list
 * input and/or output: none
 * Function’s return value: void 
 * Frees the hashNode list containing the Merkle proof
 * Function’s algorithm: free, recursive iteration 
 **********************************************************************/
void freeProof(struct HashNode* list)
{
  if(list == NULL) return;
  if(list->next == NULL)
  {
    free(list->hash);
    free(list); 
    return;
  }
  freeProof(list->next);
  free(list->hash);
  free(list);
  list =NULL;
}

int main(){
  int k = 0;
  char c1[] = "apple";
  char c2[]= "Pug";
  char c3[] = "pig";
  char c4[] = "not";
  char* hashed;
  char* hashed2;
  char* hashed3;
  struct HashNode* hashList;
  struct HashNode* hashList2;
  struct TreeNode* leaf1;
  struct TreeNode* leaf2;
  struct TreeNode* branch; 
  struct TreeNode* leaf3;
  struct TreeNode* leaf4;
  struct TreeNode* branch2;
  struct TreeNode* branch3; 
  struct TreeNode* branch4;
 
  hashList = NULL;
  hashList2 = NULL;
  leaf1 = NULL;
  leaf2 = NULL;
  branch = NULL;
  leaf3 = NULL;
  leaf4 = NULL;
  branch2 = NULL;
  branch3 = NULL;
  branch4 = NULL;
  hashed = NULL;
  hashed2 = NULL;
  hashed3 = NULL;

  /* test hash*/
  printf("testing hash c1:\n"); 
  hashed = hash(c1); 
  hashed2 = hash(c2); 
  hashed3 = hash(c3);
  printHash(hashed);
  printf("\n");
  printf("testing hash c2 \n");
  printHash(hashed2);
  printf("\n");
  printf("testing hash c3 \n");
  printHash(hashed3);
  printf("\n");
  free(hashed);
  free(hashed2); 
  free(hashed3);

  /* create leaf node */
  printf("Testing creating leaf nodes and printing: \n"); 
  leaf1 =createLeafNode(c1);
  leaf2 =createLeafNode(c2);

  printTree(leaf1);
  printTree(leaf2);

  /*create branchNode */
  printf("create branch with apple and Pug\n");
  branch =createBranchNode(leaf1,leaf2);
  printTree(branch);

  printf("create new branch with branch and pig\n");
  branch = createBranchNode(branch,createLeafNode(c3));
  printTree(branch);

  printf("recreate branch, to verify hashing is consistent\n");
  leaf3 =createLeafNode(c1);
  leaf4 =createLeafNode(c2);
  
  branch2 =createBranchNode(leaf3,leaf4);
  branch2 = createBranchNode(branch2,createLeafNode(c3));
  printTree(branch2);

  if(!strcmp(branch2->data,branch->data))
  {
    printf("Merkle Roots match\n");
  } 

  /* verify data in tree*/
  printf("testing if apple is in the tree:\n");
  k =verifyDataInTree(branch, c1);
  if(k==1)
  {
    printf("data present \n"); 
  } 

  printf("testing if Pug is in the tree:\n");
  k =verifyDataInTree(branch, c2);
  if(k==1)
  {
    printf("data present \n"); 
  } 

  printf("testing if pig is in the tree:\n");
  k =verifyDataInTree(branch, c3);
  if(k==1)
  {
    printf("data present \n"); 
  } 

  printf("testing if not is in the tree:\n");
  k =verifyDataInTree(branch, c4);
  if(k==1)
  {
    printf("data present \n"); 
  } 
  else printf("data not present \n");

  printf("Creating third branch and comparing merkle roots\n");
  branch3 = createBranchNode(createLeafNode(c3),createBranchNode(createLeafNode(c2),createLeafNode(c1)));
  if(strcmp(branch3->data,branch->data)){
    printf("Merkle Roots don't match as expected\n");
  }
  printf("Branch3:\n");
  printTree(branch3);

  printf("Creating branches with NULL args");
  branch4 = createBranchNode(NULL,NULL);
  printTree(branch4);
  if(branch4 != NULL)
  {
    printf("Should have been NULL\n");
  }

  printf("Printing branches created with NULL args\n");
  branch4 = createBranchNode(NULL, createLeafNode(c3)); 
  printTree(branch4);
  printf("Add that branch to a NULL branch\n");
  branch4 = createBranchNode(branch4, NULL);
  printTree(branch4);

  /* give proof / create HashNode*/
  hashList = giveProof(branch, c1);
  hashList2 = giveProof(branch,c3);
  
  printf("GiveProof for apple:\n");
  printProof(hashList);
  printf("GiveProof for pig:\n");
  printProof(hashList2);
  /* free tree */
  freeTree(branch);
  freeTree(branch2);
  freeTree(branch3);
  freeTree(branch4);
  freeProof(hashList);
  freeProof(hashList2);
  branch =NULL;
  branch2=NULL;
  hashList =NULL;
  hashList2 =NULL;

  return 0;
}
