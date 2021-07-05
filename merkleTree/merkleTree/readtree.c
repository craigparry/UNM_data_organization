/************************************* 
 * Craig Parry
 * 
 * This file implements the functions in readtree.h to read in files
 * that contain names of files and that contain strings to be used as 
 * leafs in a Merkle tree and makes hashtreelist out of those files
 * this file is dependent on hashtreelist.chashtreelist.h, hashtree.h, 
 * hashtree.c, and lonesha256.c and readtree.h 
 * 
 *************************************/

#include <stdio.h>
#include <stdlib.h>
#include "hashtree.h"
#include "hashtreelist.h"
#include "readtree.h"
#include <string.h>

/************************************* 
 * Each parameter’s type and name: char* filename
 * input and/or output: input file (filename)
 * Function’s return value: structTreeNode* 
 * Reads in the contents of a file. Each line contains a leaf node. Which 
 * is used to make a Merkle Tree
 * Function’s algorithm: File I/O
 *************************************/
struct TreeNode * putFileIntoHashTree(char* filename)
{
  struct TreeNode* temp;
  char c;
  int i;
  char buffer[100];
  FILE* toRead;
  i=0;
  temp =NULL;
  
  /*open the file of the name passed to the function*/
  toRead = fopen((const char*)filename,(const char*) "r"); 
  /*arbirary assignment, 'a' is clobbered once the loop is entered*/
  c = 'a';
  while(c != EOF)
  {
    c =getc(toRead);

    if(c != '\n' && c !=EOF)
    {
      buffer[i] = c;
      i++;
    }
    if(c == '\n')
    {
      buffer[i] = '\0';
      /*pass buffer string to open file
      assign treeRoot pointer to tree returned*/
      temp = createBranchNode(temp,createLeafNode(buffer));
      i=0;
    }

    if(c == EOF && i >0){
      buffer[i] = '\0';
      /*pass buffer string to open file
      assign treeRoot pointer to tree returned*/
      temp = createBranchNode(temp,createLeafNode(buffer));
      i=0;
      
      break;
    }
  }
  fclose(toRead);
  return temp;
}

/************************************* 
 * Each parameter’s type and name: char* filename
 * input and/or output: input file (filename)
 * Function’s return value: structTreeListNode 
 * Reads in the contents of a file. Each line contains a filename of an element
  in the hashtree list. This will use putFileIntoHashTree as a helper function. 
 * Function’s algorithm: File I/O
 *************************************/
struct TreeListNode * readInFiles(char* filename)
{
  struct TreeListNode * treeList;
  struct TreeNode * treeRoot;
  int i;
  char c;
  FILE* toRead;
  char buffer[100];
  treeList =NULL;
  treeRoot =NULL;
  i=0;
 
  /*open the file of the name passed to the function*/
  toRead = fopen((const char*)filename,(const char*) "r"); 
  /*arbirary assignment, a is clobbered once the loop is entered*/
  c = 'a';
  while(c != EOF)
  {
    c =getc(toRead);

    if(c != '\n' && c !=EOF)
    {
      buffer[i] = c;
      i++;
    }
    if(c == '\n')
    {
      buffer[i] = '\0';
      /*pass buffer string to open file
      assign treeRoot pointer to tree returned*/
      treeRoot = putFileIntoHashTree(buffer);
      /*pass the tree root to addNode to create our treeList*/
      treeList = addNode(treeList, treeRoot);
      i=0;
    }

    if(c == EOF && i >0){
      buffer[i] = '\0';
      /*pass buffer string to open file
        assign treeRoot pointer to tree returned*/
      treeRoot = putFileIntoHashTree(buffer);
      /*pass the tree root to addNode to create our treeList*/
      treeList = addNode(treeList, treeRoot);
      i=0;
      break;
    }
  }
  fclose(toRead);
  return treeList;
}
