/*****************************************
 *Craig Parry
 *
 *
 ****************************************/

#include <stdio.h>
#include <stdlib.h>
#include "hashtree.h"
#include "hashtreelist.h"
#include "readtree.h"
#include <string.h>

void readOpened(char* stream)
{
 struct TreeListNode * treeList;
  struct TreeNode * treeRoot;
  treeList =NULL;
  treeRoot =NULL;
 
  int i;
  i=0;
  char c;
  FILE* toRead;
  char buffer[100];
  /*buffer = calloc(100,sizeof(char)); */

  toRead = fopen((const char*)stream,(const char*) "r"); 
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
      printf("testing string: %s\n",buffer);
      // treeRoot = putFileIntoHashTree(buffer);
      // treeList = addNode(treeList, treeRoot);
      i=0;
      // if(c != EOF)
      // {
      //   c =getc(toRead);
      // }
      // else c =0;
    }

    if(c == EOF && i >0){
      buffer[i] = '\0';
      printf("testing string EOF: %s\n",buffer);
      // treeRoot = putFileIntoHashTree(buffer);
      // treeList = addNode(treeList, treeRoot);
      i=0;
      
      break;
    }
  }

  // if(c == EOF && strlen(buffer)>0)
  // {
  //   printf("string length: %lu\n",strlen(buffer));
  //   printf("testing string out: %s\n",buffer);
  // }
   
  fclose(toRead);
}

/* Verify if the given data is in a leaf node of the tree.
 * Returns a 0 if not, positive number if yes. */
/************************************* 
 * Each parameter’s type and name: 
 *  input and/or output, 
 *  its meaning, 
 *  its range of values. 
 * Function’s return value. 
 * Description of what the function 
 *  does. 
 * Function’s algorithm 
 *************************************/
int verifyHashInTree(struct TreeNode* hashtree, char* data)
{
  int found;
  found =0;
  if(hashtree == NULL || hashtree->isLeaf == 1) return 0;  

  if(!strcmp(data, hashtree->data))  return 1;
  /*just wrote this need to test it*/
  if(hashtree->left !=NULL)
  { 
    /*verify left root and its children with recusion*/
    found = verifyHashInTree(hashtree->left, data);
  } 
    if(found == 1) return found;

  if(hashtree->right !=NULL)
  {
     /*verify right root and its children with recusion*/
    
    found = verifyHashInTree(hashtree->right, data);
  } 
  if(found == 1) return found; 
  
  return found;
}

int main(int argc, char* argv[])
{
  char* stream;
  int i;
  i=1;
  
  if(argc > 1)
  {
    
    while(i <argc)
    {
      stream = argv[i];
      readOpened(stream);
      i++;
    }
  }  
  return 0;
}
