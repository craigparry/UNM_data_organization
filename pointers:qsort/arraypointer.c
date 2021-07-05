/*****************************************************/
/* Craig Parry                                       */
/* Date 10/26/18                                     */
/* CS 241 Section # 002                              */
/* hw-06 arraypointer.c                              */
/* this program shows how arrays are passed to       */
/* functions by reference as a pointer to the first  */ 
/* element of the array, instead of by value. It also*/
/* shows that floats and ints are passed by value.   */
/* compile and run in the command line               */
/*****************************************************/

#include <stdio.h>
#include <stdlib.h>

/***********************************************
 * Each parameter’s type and name: int y
 * input and/or output: prints Integer and size
 * integers are passed to functions by value
 * so we can directly print their value and 
 * access the size of thier type  
 * range: MAX_INT, MIN_INT
 * Function’s return value: void
 * prints the value of the int and its byte size
 * Function’s algorithm: printf
 ***********************************************/
void printInt(int y)
{ 
  int size;
  printf("Integer: %d\n",y);
  size =sizeof(y);
  printf("Size after: %d\n",size);
}
/****************************************** 
 * Each parameter’s type and name: float x
 * input and/or output: prints float and size
 * floats are passed to functions by value
 * so we can acess thier values directly when 
 * passed to a function
 * its range of values. 
 * range: max value for float and min for float
 * Function’s return value: void
 * prints the size of the float passed and 
 * its byte size
 * Function’s algorithm: printf
 *******************************************/
void printFloat(float x)
{ 
  int fSize;
  printf("floating point: %f\n",x);
  fSize= sizeof(x);
  printf("Size after: %d\n",fSize);
}
/********************************************* 
 * Each parameter’s type and name: char* examp
 * input and/or output: the size of examp and 
 * each character passed char*
 * arrays are passed to funcitons by reference
 * so we can use pointers to assign indexes 
 * and acess thier values at that location
 * range:chars  
 * Function’s return value: void 
 * the function accesses each pointed to location's
 * value while it is not a null terminator
 * Function’s algorithm: printf, pointers
 ********************************************/
void printArrayChars(char* examp)
{
  /*should always be the size of a char pointer*/
  printf("Size in func: %lu\n",sizeof(examp)/sizeof(char));
  while(*examp)
  {
    printf("%c\n", *examp);
    examp++;
  }
  printf("\n");
}
/******************************************************
 * Each parameter’s type and name: char* ex1, char* ex2 
 * input and/or output: prints ex1 and ex2
 * arrays are passed to functions by reference
 * range: chars
 * Function’s return value: void 
 * prints the char* or char array
 * Function’s algorithm: printf, pointers 
 ******************************************************/
void printArrays(char* ex1, char* ex2)
{

  printf("%s\n", ex1);
  printf("%s\n", ex2);
}


int main(void)
{
  float floating;
  int decimal; 
  char s1[] ="pumpkin";
  char s2[] ="orange";
  char s3[] ="spice";
  char* s4;
  char* s5;
  char* s6;

  decimal = 1000020;
  floating=1.234566777765;
  s4 ="ghost";
  s5 ="zombie";
  s6 ="evil build a bear"; 
  
  /*the function will be able to print whether the 
  array or the pointer is passed to the function because 
  they are both passed by reference and the int/floats are passed 
  directly or in a variable by value*/
  printf("Passed to function as char[] and char*:\n");
  printArrays(s1,s4);
  printf("Size of Array: %lu\n",sizeof(s2)/sizeof(char));
  printArrayChars(s2);
  printf("Size of Array: %lu\n",sizeof(s3)/sizeof(char));
  printArrayChars(s3);
  printf("Size of char*: %lu\n",sizeof(s5)/sizeof(char));
  printArrayChars(s5);
  printf("Size of float before: %lu\n",sizeof(floating));
  printFloat(floating);
  printf("Size of int before: %lu\n",sizeof(decimal));
  printInt(decimal);

  return 0;
}
