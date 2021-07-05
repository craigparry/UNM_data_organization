/********************************************************************** 
 * Craig Parry 
 * 
 * This file test hashtreelist.c which makes a list containing Merkle 
 * trees in each node. 
 * this file is dependent on hashtreelist.chashtreelist.h, hashtree.h, 
 * hashtree.c, and lonesha256.c 
 * 
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "hashtree.h"
#include <string.h>
#include "hashtreelist.h"

int main(){
  int i;
  int test = 0;
  char c1[] = "apple";
  char c2[] = "Pug";
  char c3[] = "pig";
  char c4[] = "cat";
  char c5[] = "dog";
  char c6[] = "snow";
  char c7[] = "nothere";
  struct TreeListNode* testList;
  struct TreeListNode* firstNode;
  struct TreeNode* leaf1;
  struct TreeNode* leaf2;
  struct TreeNode* branch; 

  struct TreeNode* leaf3;
  struct TreeNode* leaf4;
  struct TreeNode* branch2;

  struct TreeNode* leaf5;
  struct TreeNode* leaf6;
  struct TreeNode* dupBranch;

  struct TreeNode* leaf7;
  struct TreeNode* leaf8;
  struct TreeNode* dupBranch2;

  leaf1 = NULL;
  leaf2 = NULL;
  branch = NULL;
  leaf3 = NULL;
  leaf4 = NULL;
  branch2 = NULL;
  leaf5 = NULL;
  leaf6 = NULL;
  dupBranch = NULL;
  leaf7 = NULL;
  leaf8 = NULL;
  dupBranch2 = NULL;
  testList = NULL;
  firstNode = NULL;

  /*creating a couple of small trees to put into the list
   to test the functions*/
  printf("Creating a small trees to test: two duplicates \n"); 
  leaf1 =createLeafNode(c1);
  leaf2 =createLeafNode(c2);
  branch =createBranchNode(leaf1,leaf2);
  branch = createBranchNode(branch,createLeafNode(c3));

  leaf3 =createLeafNode(c4);
  leaf4 =createLeafNode(c5);
  branch2 =createBranchNode(leaf3,leaf4);
  branch2 = createBranchNode(createLeafNode(c6),branch2);

  leaf5 =createLeafNode(c1);
  leaf6 =createLeafNode(c2);
  dupBranch =createBranchNode(leaf5,leaf6);
  dupBranch = createBranchNode(dupBranch,createLeafNode(c3));

  leaf7 =createLeafNode(c4);
  leaf8 =createLeafNode(c5);
  dupBranch2 =createBranchNode(leaf7,leaf8);
  dupBranch2 = createBranchNode(createLeafNode(c6),dupBranch2);

  /*createNode*/
  printf("(CreateNode test)\n");
  
  firstNode =createNode(createLeafNode(c1));

  if(verifyDataInTree(firstNode->root, c1) > 0)
  {
    printf("Data present in first ListNode\n");
  }

  freeList(firstNode);
  firstNode = NULL;
  
  /*addnode */
  testList = addNode(testList,branch);
  testList = addNode(testList, branch2);

  /* find data*/
  printf("(Testing find data) \n");
  test =findData(testList, c2);
  if(test >= 0 )
  {
    printf("data found, height: %d \n",test);
  }
  else printf("data not found \n");
  
  test = findData(testList,c6);

  if(test > 0 )
  {
    printf("data found, height: %d \n",test);
  }
  else printf("data not found \n");
  
  test =findData(testList, c7);

  if(test > 0 )
  {
    printf("data found, height: %d \n",test);
  }
  else printf("data not found \n");

  testList = addNode(testList, dupBranch);
  testList = addNode(testList, dupBranch2);

  /*check hash*/
  printf("(Testing check Hash) \n");
  
  for(i=0;i<5;i++)
  {
    test =0;
    test = checkHash(testList,i,branch->data);
    if(test == 1){
      printf("Hash of branch found at height: %d\n",i);
    }
    else printf("Hash of branch not found at height: %d\n",i);
    test =0;
    test = checkHash(testList,i,branch2->data);
    if(test == 1){
      printf("Hash of branch2 found at height: %d\n",i);
    }
    else printf("Hash of branch2 not found at height: %d\n",i);
  }

  freeList(testList);

  return 0;
}
