/**************************************************/
/* Craig Parry                                    */
/* Date 10/26/18                                  */
/* CS 241 Section # 002                           */
/* hw-06 pstring.c                                */
/* implementing methods of the string library.    */
/* run the file with tests in the main method     */
/**************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************************************************** 
 * Each parameter’s type and name: char*s, char* t
 * input and/or output: none
 * Function’s return value: int
 * checks if char* s ends with the entirety of char* t
 * retturns a 1 if the string t occurs at the end of 
 * string s
 * Function’s algorithm: pointer comparison 
 ****************************************************/
int pstrend(char* s,char* t)
{
  /*returns 1 if the string t occurs at the end of the
  string s and zero otherwise*/
  int sizeS;
  int sizeT;
  /*uses strlen to find the last index of the pointer*/
  sizeS = strlen(s);
  sizeT = strlen(t);

  while(sizeT >0){
    sizeS--;
    sizeT--;
    /*compares the indexes until a error is found or until t reaches zero*/
    if(*(s+sizeS)!= *(t+sizeT))
    {
      return 0; 
    } 
    if(sizeT == 0){
      return 1;
    }
  }
  return 1;
}

/********************************************************* 
 * Each parameter’s type and name: char* s, char* t, int n
 * input and/or output: none  
 * Function’s return value: char* 
 * this function copies string t to string s for n characters
 * changing the original char* s
 * Function’s algorithm: pointers assignment 
 ********************************************************/
char* pstrncpy(char* s,char* t,int n)
{
  /*copies at most n characters of t to s and returns s */
  /* Pad with null terminators if t has fewer than n characters.*/
  int i;

  for(i=0; i < n; i++)
  {
      if(*t != '\0')
      { 
        *s = *t; 
        s++;
        t++;
      } else 
      {
        *s = '\0';
        s++;
      }  
  } 
  if(*(s) != '\0')
  {
    *(s)='\0';
  }
  s = s-(n);
  return s;
}

/************************************************************ 
 * Each parameter’s type and name: char* s, char* t, int n
 * input and/or output: none 
 * Function’s return value: char* 
 * this function concatonates char* t onto char*s for n chars
 * Function’s algorithm: pointers 
 ***********************************************************/
char* pstrncat(char* s,char* t,int n)
{
  int sizeS;
  int sizeT; 
  int i;
  char* abort;
  abort = "abort trap: 6";

  sizeT =strlen(t);
  sizeS = strlen(s);

  if(sizeS < sizeT) return abort; 
  /*can safely execute for the maximum char array length defined
  if the memory allocated for the array is less than the amount of chars
  expected for the array to concatonate correctly we may get 
  unexpected behavior*/
  
  s = s+sizeS;

  for(i=0;i<n;i++)
  {
    
    *s=*t;
    s++;
    t++;
  } 

  *(s++) = '\0';
  s = s-(sizeS + n+1);
  return s;
}

/********************************************************* 
 * Each parameter’s type and name: char* s, char* t, int n 
 * input and/or output: none
 * Function’s return value: int 
 * ths function compares string s to t for n characters
 * Function’s algorithm: pointer comparison
 ********************************************************/
int pstrncmp(char* s,char* t,int n)
{
  /* compares at most n characters of strings to string t. 
   Returns a value less than zero if s < t, 0 if s = t, 
   or greater than zero if s > t.*/
  int boolean;
  int i;
  boolean =0;
   
  for(i=0;i<n;i++)
  {
    if(*s!=*t)
    {
      if(*s<*t)return -1;
      if(*s>*t)return 1;
    }
    s++;
    t++;
  }
  return boolean;
}

int main()
{
  int ex1; 
  int ex2;
  int value;
  int value2;

  char s1[] = {'a','p','p','l','e','\0'};
  char s2[] = {'p','i','n','e','a','p','p','l','e','\0'};
  char s3[]={'a','n','d','\0'};
  char s4[]={'s','t','r','a','n','d','\0'};
  char* s5;
  char* s6;
  char* s7;
  char* s8;
  char s9[] = {'c','o','t','t','o','n','\0'};
  char s10[] = {'c','o','t','t','o','n','w','o','o','d','\0'};
  char* s11;

  s11 =s3;
  s5 =s1;
  s6 =s2;

  ex1 =pstrend(s2,s1);
  ex2 =pstrend(s3,s4);

  if(ex1 == 1){
    printf("ex1 pstrend: true\n");
  } else printf("ex1 pstrend: false\n");
   if(ex2 == 1){
    printf("ex2 pstrend: true\n");
  } else printf("ex2 pstrend: false\n");
  printf("ex1 %d\n",ex1);
  printf("ex2 %d\n",ex2);

  s7 = pstrncpy(s3,s2,5);
  /*s3 and s7 should be equal*/
  printf("pstrncpy: %s\n",s7);
 
  /*library strcat*/ 
  s8 = strcat(s11,s4);
  printf("strcat: %s\n",s8);
  /*pstrncat print*/
  s8 = pstrncat(s11,s4, 3);
  printf("pstrncat: %s\n",s8);
  /*abort trap error s3 is not large enough to concatonate */
  /* uncomment for error case abort trap, wont complete the program
  if visible: printf("%s\n",strcat(s3,s10));
  */

  /*can change values of length and change arrays or char* 
  to compare values of the compared strings*/
  value =pstrncmp(s10,s9,20);
  printf("pstrncmp: %d\n",value);
  if(value == 1) printf("greater\n"); 
  if(value == 0) printf("equal\n");
  if(value == -1) printf("less\n");
  
  printf("strcmp: %d\n",value2 =strcmp(s10,s10));
  if(value >0) printf("greater\n"); 
  if(value == 0) printf("equal\n");
  if(value < 0) printf("less\n");

  return 0;
} 
