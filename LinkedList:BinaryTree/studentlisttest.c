/********************************************************************** 
 * Craig Parry
 * This file is used to test the linkedlist.c file 
 * compile this file with linkedlist.c and linkedlist.h to run the test
 * 
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"


int main()
{
  /*testing creation of linked list and using insert sorted
    tests first node and whether it connects the initail node correctly to 
    the head and to the end of the list when they are initalized at null */
  int testInt;
  struct ListNode * LLP;
  struct ListNode * stack;
  LLP = NULL;
  stack =NULL;
  /*printing a NULL/empty list*/
  printf("Empty List: ");
  printList(LLP);
  /*insert on NULL list*/
  /*dependent on create node*/
  LLP = insertSorted(LLP,1); 
  if((LLP)->data != 1) printf("Error insert on empty list");
  /*remove list of one with NULL initialized pointers*/
  testInt = removeItem(&LLP,1);
  LLP = NULL;
  
  if(testInt != 1) printf("Error removing item"); 
  /*insert on list after its been emptied*/
  LLP =insertSorted(LLP,1);
  LLP =insertSorted(LLP,3);
  /*insertSorted greater than inital number*/
  printf("Sorted List: ");
  printList(LLP);
 
  removeItem(&LLP,3);
  /*remove last item that has initialized pointers*/
  testInt=removeItem(&LLP,1);
  LLP =NULL;
  if(testInt != 1 || LLP != NULL) 
  {
    printf("Error removing self referencing node\n"); 
  }

  /*insert number that is is less than initial node*/
  LLP =insertSorted(LLP,5);
  LLP =insertSorted(LLP,3);
    
  LLP =insertSorted(LLP,1);
  /*insert node greater than those in the list*/
  LLP =insertSorted(LLP,6);
  /*sorted list*/
  printf("Sorted List: ");
  printList(LLP);
  /*test reverse list*/
  reverseList(&LLP);
  printf("Reverse Sorted: ");
  printList(LLP);
  /*reverse again to make sure no connections were broken*/
  printf("Reverse again: ");
  reverseList(&LLP);
  printList(LLP); 
  /*free filled list*/
  freeList(LLP);
  LLP = NULL;
  /*free list of one node*/
  LLP= insertSorted(LLP,1);
  freeList(LLP);
  /*cannot set LLP to NULL within the function freeList because we cannot
  assign the memory reference to NULL, would be more effective to have a 
  pointer to a pointer so that we can change it*/
  LLP=NULL;
  /*reverse empty list*/
  reverseList(&LLP); 

  /* push, pop, on one node and multiple nodes
   * and test listlength  
   */
  /*test push stack and pop with one item on the list*/
  stack = pushStack(stack,5); 
  testInt = popStack(&stack); 
  stack = NULL;
  if(testInt != 5) printf("Error: popStack\n");
  /*connecting multiple nodes and popping of them stack
   to check for pointer functionality*/
  stack = pushStack(stack,5); 
  stack = pushStack(stack,3); 
  printf("Stack: ");
  printList(stack);

  testInt = popStack(&stack); 
  if(testInt != 3) printf("Error: popStack\n");

  testInt = popStack(&stack); 
  if(testInt != 5) printf("Error: popStack\n");
  stack =NULL;
  printf("Empty Stack: ");
  printList(stack);
  /*listLength test on empty list*/
  testInt =listLength(stack); 
  if(testInt != 0) printf("Error listLength\n");
  /*new stack of more than two nodes */
  printf("New Stack: ");
  stack = pushStack(stack,5); 
  stack = pushStack(stack,3); 
  stack = pushStack(stack,7); 
  stack = pushStack(stack,8); 
  stack = pushStack(stack,2); 
  stack = pushStack(stack,10); 
  /*print stack using recursive helper*/
  printList(stack);
  /*test listLength*/
  printf("List Length: %d\n",listLength(stack));
  reverseList(&stack);
  /*popStack and reverse to make sure no connections were lost
    points to new head and doesn't break prev to last node*/
  testInt = popStack(&stack);
  if(testInt != 5) printf("Error: popStack\n");

  printf("Reversed stack: ");
  printList(stack);
  /*push to stack and reverse to make sure new connections are added
  correctly*/
  stack = pushStack(stack,27);


  reverseList(&stack);
  printf("Reverse again: ");
  printList(stack);
  /*testing freelist*/
  freeList(stack);

  return 0;
}
