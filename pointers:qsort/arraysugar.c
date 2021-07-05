/**************************************************/
/* Craig Parry                                    */
/* Date 10/26/18                                  */
/* CS 241 Section # 002                           */
/* hw-06 arraysugar.c                             */
/* This program shows how we can use a different  */
/* syntax to access indexes of an array using     */
/* pointers. We can use *(arr+0) interchangably   */
/* with arr[0]                                    */
/**************************************************/

#include <stdio.h>
#include <limits.h>

/***************************************************** 
 * Each parameter’s type and name: int* arr1, int size
 * input and/or output: prints int array values, -1
 * if overflow
 * we can access and index arrays using pointer syntax
 * INT_MIN to INT_MAX
 * Function’s return value: void
 * the function acesses each index of the array using 
 * pointers to print the content of the array
 * Function’s algorithm: pointers
 ****************************************************/
void printIntArr(int* arr1, int size)
{
  int i;
  i =0;

  /*uses size of the array to control indexing*/
  while(i<size)
  {
    /* if int is an overflow value then print -1
     usint INT_MIN INT_MAX in limits.h*/
    if((*arr1+i) <= INT_MAX && (*arr1+i)>=INT_MIN)
    {
      printf("%d",*(arr1+i));
      i++;
    } else printf("-1");
  }
  printf("\n");
}

int main(void)
{
  int s1[] = {1,3,5,7,9};
  int s2[] = {2,4,6,8,10};
  int s3[] ={3,3,3,3,3,3,3}; 
  int s4[] = {1,5,6,0,7,9,10,17,8};
  int s5[] = {5,5,5,5,7}; 

  printIntArr(s1, sizeof(s1)/sizeof(int));
  printIntArr(s2, sizeof(s2)/sizeof(int));
  printIntArr(s3, sizeof(s3)/sizeof(int));
  printIntArr(s4, sizeof(s4)/sizeof(int));
  printIntArr(s5, sizeof(s5)/sizeof(int));
  
  return 0;
}
