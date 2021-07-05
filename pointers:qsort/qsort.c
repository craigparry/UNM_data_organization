/**************************************************/
/* Craig Parry                                    */
/* Date 10/26/18                                  */
/* CS 241 Section # 002                           */
/* hw-06 qsort.c                                  */
/* This file implements quicksort, run this file. */
/* with no flags or flags marking -r reverse, -f  */
/* folded lower and uppercase letters, or -n for  */
/* for numeric sorts and pipe a file with letters,*/ 
/* words or numbers into the file                 */
/**************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLEN 1000
/*max #lines to be sorted */
#define MAXLINES 5000 
/* size of available space */
#define ALLOCSIZE 10000 
/* pointers to text lines */
char *lineptr[MAXLINES]; 
/*storage for alloc */
static char allocbuf[ALLOCSIZE]; 
/* next free position*/
static char *allocp = allocbuf; 

/*************************************************** 
 * Each parameter’s type and name: int n 
 * input and/or output: none 
 * Function’s return value: char* 
 * alloc is used to store characters in the allocp
 * pointer which has allocated storage for characters
 * Function’s algorithm: array pointer
 ****************************************************/
char *alloc(int n) 
{
  if(allocbuf + ALLOCSIZE - allocp >= n)
  {
    allocp += n;
    return allocp -n; 
  } else return 0;
}

/************************************************************
 * Each parameter’s type and name: 
 * input and/or output: input file of chars
 * Function’s return value: int 
 * the function is getting chars from the the input file
 * and assigning their values to the passed in char* 
 * and returning the number of chars read by the line
 * Function’s algorithm: pointers and getchar()
 ***********************************************************/
int getLine(char* s, int lim)
{
  int c, i; 

  i =0; 
  while(--lim > 0 && (c=getchar()) != EOF && c != '\n')
  {
    /*changed to pionter syntax*/
    *(s+i) = c;
    i++;
  }
  if(c== '\n')
  {
    /*changed to pionter syntax*/
    *(s+i) = c;
    i++;
  }
  /*changed to pointer syntax*/
  *(s+i) ='\0';
  return i;
}

/***************************************************************
 * Each parameter’s type and name: char** lineptr, int maxlines
 * input and/or output: reads lines from file expecting
 * numbers, letters or words 
 * Function’s return value: int 
 * reads lines from a text file and stores them in 
 * the point to char pointer lineptr for storage
 * Function’s algorithm: pointers and input
***********************************************************/
int readlines(char **lineptr, int maxlines)
{
  int len, nlines; 
  char *p, line[MAXLEN];

  nlines =0;
  while((len =getLine(line, MAXLEN)) > 0)
  {
    if(nlines >= maxlines|| (p=alloc(len)) == NULL)
    {
      return -1;
    }
    else {
      /*changed to pointer syntax*/
      *(line+(len-1))='\0';
      strcpy(p,line);
      /*changed to pointer syntax*/
      *(lineptr+(nlines++)) = p;
    }
  }
    return nlines;   
}

/*************************************************************
 * Each parameter’s type and name: char** lineptr, int nlines 
 * input and/or output: prints out the lines stored in pointer
 * char pointer lineptr 
 * Function’s return value: void
 * this funtion iterates through linptr and prints out the
 * each line stored in the pointer
 * Function’s algorithm: pointers
 ***********************************************************/
void writeLines(char** lineptr, int nlines, int dir)
{
  int i;

  /*control for direction*/
  if(dir == 0)
  {
    for(i =0; i < nlines; i++)
    { 
      /*changed to pointer syntax*/
      printf("%s\n",*(lineptr+i));
    }
  } else
  {
    /*prints in reverse*/
    for(i =nlines-1; i >= 0; i--)
    { 
      /*changed to pointer syntax*/
      printf("%s\n",*(lineptr+i));
    }
  }
}

/**************************************************** 
 * Each parameter’s type and name: char* s1, char* s2
 * input and/or output: none
 * Function’s return value: int 
 * compares s1 and s2 numerically 
 * Function’s algorithm: numerical comparison
 **************************************************/

int numcmp(char* s1, char* s2)
{
  double v1, v2; 

  v1 = atof(s1);
  v2 =atof(s2);
  if(v1< v2) return -1;
  else if (v1>v2) return 1;
  else return 0;
}

/********************************************************
 * Each parameter’s type and name: void** v, int i, int j
 * input and/or output: none
 * Function’s return value: void 
 * swaps the values of the two indexes (i & j)
 * of the pointer (**v) passed to the funtion 
 * Function’s algorithm: swap 
 ********************************************************/
void swap(void** v, int i, int j)
{
  /*changed to pointer syntax*/
  void *temp;
  temp =*(v+i);
  *(v+i)=*(v+j);
  *(v+j)=temp;
  
}

/***************************************************** 
 * Each parameter’s type and name: void** v, int left,
 * int right, int (*comp)(void*, void*)
 * input and/or output: none  
 * Function’s return value: void
 * partitions the pointer and sorts into two smaller pointers
 * by whatever is bigger than the partition and whatever is smaller
 * than the partition. then recursively calls itself until the until 
 * every piece of the pointer is sorted to a one to one comparison. 
 * Function’s algorithm: quicksort
 ****************************************************/
void qSort(void** v, int left, int right, int (*comp)(void*, void*))
{
  int i, last; 
  void swap(void **v, int, int);

  if(left >= right) 
    return;        
  swap(v, left, (left + right)/2);
  last = left;
  for(i = left+1; i <= right; i++)
  {
      /*changed to pointer syntax*/
      if ((*comp)(*(v+i), *(v+left)) < 0)
      {
        swap(v,++last,i);
      }
  }
      swap(v,left,last);
      qSort(v,left,last-1,comp);
      qSort(v,last+1,right,comp);
}

/*changes command line to pointer to char pointer*/
int main(int argc, char **argv)
{
  int nlines; 
  int numeric =0;
  /*flags for reverse and fold*/ 
  int reverse =0;
  int fold =0;

  if(argc > 3)
  {
    printf("Error: Too many arguments\n");
    return 0;
  }
  /*changed commandline arguement access to pointer*/
  if(argc > 1) 
  {
    if(argc > 1 && strcmp(*(argv+1), "-n")==0)
      {
        numeric =1;
      }
    if(argc > 1 && strcmp(*(argv+1), "-f")==0)
      {
        fold =1;
      }
    if(argc > 1 && strcmp(*(argv+1), "-r")==0)
      {
        reverse =1;
      }
  }
  if(argc >2)
  {
   if(argc > 1 && strcmp(*(argv+2),"-n")==0)
      {
        numeric =1;
      }
    if(argc > 1 && strcmp(*(argv+2),"-f")==0)
      {
        fold =1;
      }
    if(argc > 1 && strcmp(*(argv+2),"-r")==0)
      {
        reverse =1;
      }
  } 

  if((nlines = readlines(lineptr, MAXLINES)) >= 0)
  { 
    /*if numeric is flagged, pass in the function numcmp*/
    if(numeric ==1){
      qSort((void**) lineptr, 0, nlines-1, (int (*)(void*,void*))(numcmp));
    }
    /*if fold is flagged, pass in the function strcasecmp*/
    if(fold ==1 && numeric ==0 ){
      qSort((void**) lineptr, 0, nlines-1, (int (*)(void*,void*))(strcasecmp));
    } 
    if(fold ==0 && numeric ==0)
    {
      /*if fold is not flagged, pass in the function strcmp*/
      qSort((void**) lineptr, 0, nlines-1, (int (*)(void*,void*))(strcmp));
    }
    if(fold ==1 && numeric ==1)
    {
      printf("Incompatible flags\n");
      return 0;
    }
    writeLines(lineptr,nlines, reverse);
    return 0;
  } else 
  {
    printf("input too big to sort\n");
    return 1;
  }

  return 0;
}
