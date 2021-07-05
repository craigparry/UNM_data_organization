/************************************************************************ 
 * Craig Parry
 * This file is used to make linkedlists holding integer values, needs to 
 * be compiled with linkedlist.h 
 * 
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

struct ListNode * sortedHelper(struct ListNode* newNode, 
                              struct ListNode* nextNode, struct ListNode* head);
int removeHelper(struct ListNode* nextNode, int data, struct ListNode** headRef);
void freeListHelper(struct ListNode* nextNode, struct ListNode* head);
void printHelper(struct ListNode* nextNode, struct ListNode* head);
int lengthHelper(struct ListNode* nextNode, struct ListNode* head);
void reverseHelper(struct ListNode* workNode, struct ListNode* prevNode,
                    struct ListNode** headRef);

/*************************************************************** 
 * Each parameter’s type and name: int data
 * Input/output: none 
 * Function’s return value: struct ListNode containing int data 
 * This funtion creates a ListNode containing integer data
 * Function’s algorithm: linkedlist Node
 **************************************************************/
struct ListNode * createNode(int data)
{
  struct ListNode* temp;
  /* Allocate a new node with given data. */
  temp = malloc(sizeof(struct ListNode)); 
  /*assign data and initialize next and prev nodes to NULL*/
  temp->data = data;
  temp->next = NULL;
  temp->prev = NULL;
  return temp;

}

/****************************************************************** 
 * Each parameter’s type and name: struct ListNode* head, int data
 * input and/or output: none
 * Function’s return value: struct ListNode* (head of list) 
 * creates a new node with the specified data and inserts it into 
 * the list in a sorted numerical order
 * Function’s algorithm: linkedList
 ******************************************************************/
struct ListNode * insertSorted(struct ListNode* head, int data)
{ 
  struct ListNode* temp;
  temp = createNode(data);
  /* return the new node if the head is NULL or empty list*/
  if(head == NULL) 
  { 
    return temp;
  } 
  /*if the head is not connected to any other nodes(list of one node)*/
  if(head->next ==NULL)
  {
      /*data in new node is less than head*/
      if(temp->data < head->data)
      { 
        temp->next = head;
        temp->prev = head;
        head->prev = temp;
        head->next = temp;
        return temp;
      }
      /*data in new node is greater than head*/
      else
      {
        temp->next = head;
        temp->prev = head;
        head->prev = temp;
        head->next = temp;
        return head;
      }
  }
  
  /*if nodes are already connected data is less than head node*/
  if(temp->data <= head->data)
  {
    /*if data is smaller since dealing with ints
    make the new node the head*/
    
    temp->next = head;
    temp->prev = head->prev;
    head->prev->next = temp;
    head->prev = temp;
    return temp;
  } 
  /*not the end of the list and number is not less than head
  * call helper method with next node and the head to compare too*/
  sortedHelper(temp,head->next, head);
  return head;
  
}

/**************************************************************** 
 * Each parameter’s type and name: struct ListNode* newNode, 
 * struct ListNode*nextNode, struct ListNode* head
 *  input and/or output: none
 * Function’s return value: struct ListNode* (head)
 * recursive helper, takes the created node and inserts it into
 * the list in its sorted order and returns the head of the list. 
 * Function’s algorithm: linkedlist
 ****************************************************************/
struct ListNode * sortedHelper(struct ListNode* newNode,
                               struct ListNode* nextNode, struct ListNode* head)
{
  /*if the nextNode is the beginning of the list attach node to
    the end of the list*/
  if(nextNode == head)
  {
    newNode->next = nextNode;
    newNode->prev = nextNode->prev;
    nextNode->prev->next= newNode;
    nextNode->prev= newNode; 
    
    return head;
  }
  /*if node data is less the the current node attach nonde before
    and connect links */
  if(newNode->data < nextNode->data)
  {
    /*connect new node to node prev and next */
    newNode->next = nextNode;
    newNode->prev = nextNode->prev;
    /*connect prev not to newNode*/
    newNode->prev->next = newNode;
    /*connect next node to newNode*/
    nextNode->prev = newNode;
    return head;
  }
  /*if the end of list hasn't been reached and data is not less than
    nextNode call helper again to iterate */
  return sortedHelper(newNode,nextNode->next, head); 
}

/********************************************************************** 
 * Each parameter’s type and name: struct ListNode** headRef, int data
 *  input and/or output: None 
 * Function’s return value: int zero if data not found, one if found 
 * looks for the data in the list and removes the node if the data is 
 * found, returns a 1 if found and 0 if not, connects the links and returns
 * a new head when necessary, when node is removed it frees the memory 
 * allocated with it 
 * Function’s algorithm: linkedlist 
 **********************************************************************/
int removeItem(struct ListNode** headRef, int data)
{ 
  struct ListNode * temp;  
  temp = *headRef;

  /*returns zero if list doesn't exist*/
  if(temp == NULL) return 0;
 
  /*if data exists at first node remove and return new head*/
  if(temp->data == data)
  { 
    /*if next node is the beginning of the list (list size of one) 
    * make headRef equal null list/ empty */
    if(temp->next == NULL || temp->next == temp)
    {
      *headRef = NULL;
    } 
    else
    {
      /*if not the only node, connect the other nodes, change the headRef
       to the new head node*/
      *headRef= temp->next;
      temp->prev->next = temp->next;
      temp->next->prev = temp->prev;
    }
    /*free allocated data */
    free(temp);
    return 1;
  } 
  /*if the first node is also the endpointer data not present*/
  if(temp->next == NULL) 
  {
    return 0;
  }
  /*more than one nodeand data not found call the helper*/
  return removeHelper(temp->next,data, headRef);
}

/****************************************************************************** 
 * Each parameter’s type and name: struct ListNode* nextNode, int data, 
 * sruct ListNode** headRef
 *  input and/or output: none
 * Function’s return value: int zero for data not found 1 for found and removed
 * iterates through the list recursively and removes node if the data is 
 * present in the list, returns zero if not found and 1 if found
 * Function’s algorithm: linkedlist 
 *****************************************************************************/

int removeHelper(struct ListNode* nextNode, int data, struct ListNode** headRef)
{
  /*if the end of the list has been reached*/
  if(*headRef == nextNode) return 0; 
  /*if the data is found remove it, connect links and free the allocated memory*/
  if(nextNode-> data == data)
  {
    nextNode->prev->next = nextNode->next;
    nextNode->next->prev = nextNode->prev;
    free(nextNode);
    return 1; 
  } 
  /*if its not the end of the list and the data hasn't been found*/
  return removeHelper(nextNode->next, data, headRef);
}

/************************************************************************ 
 * Each parameter’s type and name: struct ListNode* head, int data
 *  input and/or output: none 
 * Function’s return value: struct ListNode* (head of the list)
 * Treats list as a stack. (LIFO - last in, first out)
 * Insert data at head of list, return new list head.
 * Function’s algorithm: stack 
 ***********************************************************************/

struct ListNode * pushStack(struct ListNode* head, int data)
{
  struct ListNode * temp = createNode(data);
  /*if the list is empty or doesn't exist return the new node as the head*/
  if(head == NULL)
  {
    return temp;
  } 
  /*if the node is the only node in the list(uninitilized), connect the nodes 
  together*/
  if(head->next == NULL)
  {
    temp->next = head;
    temp->prev = head;
    head->next = temp;
    head->prev = temp;
  }
  /* if the nodes are already connected connnect the new node as the head*/
  else
  {
    temp->next = head;
    temp->prev = head->prev;
    head->prev->next = temp;
    head->prev = temp;
  }
  return temp;
}

/************************************************************************* 
 * Each parameter’s type and name: struct ListNode** headRef 
 *  input and/or output: none
 * Function’s return value: int, data in the first node of the list 
 * returns -1 if list is empty 
 * removes the first node of the list and connects the new head of the list
 * changing the headRef to the list and returns the int data value of the
 * removed node before freeing the memory allocated for it
 * Function’s algorithm: stack 
 *************************************************************************/
int popStack(struct ListNode** headRef)
{
  struct ListNode * temp; 
  int tempData; 
  /*make sure it doesn't try to pop a NULL stack*/
  if(*headRef == NULL) return -1; 
  temp = *headRef; 
  /*if the next node is uninitialized or is the last node make the
    new head null for an empty list*/
  if(temp->next == NULL || temp->next == temp)
  {
    tempData = temp->data;
    *headRef = NULL;
    free(temp);
    return tempData;
  }
  /*if not the only node remove the nodes and change the head ref*/
  temp->next->prev = temp->prev;
  temp->prev->next = temp->next;
  tempData = temp->data;
  *headRef = temp->next;
  
  /*freeing what temp is pointing to*/
  free(temp);
  /*return data*/
  return tempData;
}

/****************************************************************** 
 * Each parameter’s type and name: struct ListNode* head
 *  input and/or output: none
 * Function’s return value: int length of the list
 * This function iterates through the list recursively counting the 
 * amount of nodes in the list using the systems stack
 * Function’s algorithm: recursive stack 
 *******************************************************************/
int listLength(struct ListNode* head)
{   
  /*if the list is empty or NULL return 0*/
  if(head == NULL) return 0;
  /*if weve reached the end of the list return count*/
  if(head->next == head)
  { 
    return 1; 
  }
  /*if we haven't reached the end of the list call return 1 plus
    a recursive call to the helper function to count the list*/
  else
  { 
    return 1+lengthHelper(head->next,head);
  }
}

/********************************************************************
 * Each parameter’s type and name: struct ListNode* nextNode,
 * struct ListNode* head
 * input and/or output: none
 * Function’s return value: int length of the list 
 * recursively call the function until we have reached the beginning 
 * of the list again and return 0 adding 1 each time we call the method
 * Function’s algorithm 
 ********************************************************************/
int lengthHelper(struct ListNode* nextNode, struct ListNode* head)
{ 
  /*recursively call the function until we have reached the beginning 
  of the list again and return 0 adding 1 each time we call the method*/
  if(nextNode == head)
  {
    return 0;
  } 
  else return 1+lengthHelper(nextNode->next,head);
}

/*********************************************************************** 
 * Each parameter’s type and name: struct ListNode* head
 *  input and/or output: prints the values of the list seperated by a comma
 * and a space, ending with a newline
 * Function’s return value: void
 * recursively prints each node of the list on a single line 
 * seperating values with a comma and a space until the beginning of the
 * list is reached again 
 * Function’s algorithm: recursive iteration 
 ***********************************************************************/
void printList(struct ListNode* head)
{ 
  /*if the head is NULL/empty list print newline*/
  if(head == NULL)
  {
    printf("\n");
    return;
  }
  /*if the node is the only node in the list print data and newline*/
  if(head->next == NULL|| head->next == head)
  {
    printf("%d\n",head->data);
  }
  /*if we havent reached the end of the list print data and 
  call the recursive helper function */
  else
  {
    printf("%d, ",head->data);
    printHelper(head->next, head);
  }
}

/***************************************************************************
 * Each parameter’s type and name: struct ListNode* nextNode,
 * struct ListNode* head 
 *  input and/or output: prints the values of the list seperated by a comma
 * and a space, ending with a newline 
 * Function’s return value: void 
 * recursively iterates through the list printing the values of the list
 * seperated by a comma and a space, ending with a newline 
 * Function’s algorithm: recursive iteration
 ***************************************************************************/
void printHelper(struct ListNode* nextNode, struct ListNode* head)
{
  /*if weved reached the end of the list print data and a newline*/
  if(nextNode->next == head)
  { 
    printf("%d\n",nextNode->data);
  } 
  /*if the end of the list has not been reached, print data and call the helper
   function recursivly*/
  else 
  {
    printf("%d, ",nextNode->data);
    printHelper(nextNode->next, head);
  }
}

/************************************************************************** 
 * Each parameter’s type and name: struct ListNode* head
 *  input and/or output: none
 * Function’s return value: void
 * this function iterates through the linked list recursively and frees the
 * memory that was allocated for each node
 * Function’s algorithm: recursive iteration 
 **************************************************************************/
void freeList(struct ListNode* head)
{
/*if the list is empty return*/
 if(head ==NULL) return;
 /*if there is only one node in the list free the node and return*/
 if(head->next == NULL|| head->next == head)
 {
  free(head);
  head =NULL;
  return; 
 } 
 /*if theres more than one node call the recursive helper function
  then free the head*/ 
 freeListHelper(head->next, head);
 free(head);
 head = NULL;
}

/**************************************************************************** 
 * Each parameter’s type and name: struct ListNode* nextNode,
 * struct ListNode* head
 * input and/or output: none
 * Function’s return value: void
 * recursivley frees each item of the list as it iterates through recursively
 * Function’s algorithm: recursive iteration
 ***************************************************************************/
void freeListHelper(struct ListNode* nextNode, struct ListNode* head)
{ 
  /*if the next node is the head free current node and return */
  if(nextNode->next == head)
  {
    free(nextNode);
    nextNode =NULL;
    return;
  }
  /*if we havent reached the end of the list call the helper function
  recursivley then free the current node*/
  freeListHelper(nextNode->next, head);
  free(nextNode);
  nextNode =NULL;
}

/************************************* 
 * Each parameter’s type and name: struct ListNode* headRef
 *  input and/or output: none 
 * Function’s return value: void 
 * This funciton changes the pointers in the list so that each node
 * points in the opposite direction it started, reversing the order of the list
 * Function’s algorithm: recursive iteration
 *************************************/
void reverseList(struct ListNode** headRef)
{
  struct ListNode* temp;

  /*if the list is empty return*/
  if(*headRef == NULL) return;
  temp = *headRef;
  /* change the previous node to point to the next*/
  temp->prev = temp->next;
  /*call the recursive helper function*/
  reverseHelper(temp->next, temp, headRef);
  /*point headRef to the new head*/
  *headRef = temp->next;
}

/***************************************************************************** 
 * Each parameter’s type and name: struct ListNode* workNode,
 * struct ListNode* prevNode, struct ListNode** headRef
 *  input and/or output: none
 * Function’s return value: void 
 * This funciton changes the pointers in the list so that each node
 * points in the opposite direction it started, reversing the order of the list
 * Function’s algorithm: recursive iteration
 *****************************************************************************/
void reverseHelper(struct ListNode* workNode, struct ListNode* prevNode,
                    struct ListNode** headRef)
{
  /*if the current node is not the head*/
  if(workNode != *headRef)
  {
    /*change the prev to poin to the next node*/
    workNode->prev = workNode->next;
    /*call the helper*/
    reverseHelper(workNode->next, workNode,headRef);
    /*change the next node to point to the previous node*/
    workNode->next = prevNode;
    return;
  }
  /*if the current node is the head make its next node the previous node
    connecting the end of the list*/
  else
  {
    workNode->next = prevNode;
    return;
  }

}
