/**********************************************************************
*Craig Parry 8/26
* Run the through command line without arguments.
* When prompted through standard in, input the coordinates with the 
* format "x, y". Once two coordinates are entered, the distance 
* between the points will be calculated automatically
**********************************************************************/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
/*
* Point struct to hold coordinate values of x and y
*/
struct Point 
{
  int xCoord; 
  int yCoord;
};
/*
* Parses the string value for the coordinate value held in the string and
* returns an int
*/
int parse(char* str)
{ 
  int i =0; 
  int length = strlen(str);
  // struct Point* temp; 
  // for(i; i < strlen(str); i++)
  int hold; 
  int yvalue;
 
  
  hold = 0;

  while(i <= length)
  {
    /* need to convert to digit number from char, because
    * is digit returns zero or 1 
    */
    
    if(isdigit(*(str+i)))
    {
      hold = hold*10;
      hold += (*(str+i) - '0');
      
    } 

    if(isspace(*(str+i)) !=0 || *(str+i) == '\0' || *(str+i) == ',')
    {
     break;
    }
    i++;
  } 

  return hold;
}
/*
* Makes a point using the struct Point type
*/
struct Point * makePoint(int x, int y)
{
  struct Point* temp; 
  temp = malloc(sizeof(struct Point));
  temp->xCoord = x;
  temp->yCoord = y;

  return temp;
}

int main()
{
  /* Need to read input from command line with 
  * open buffer and calculate the distance 
  * points are (x1, y1) and (x2,y2)
  */ 
  char c; 
  c = 'c';
  char* str;

  struct Point* p1; 
  struct Point* p2; 
  int x;
  int y; 
  x = 0;
  y = 0;

  while(c != 'n' && c!= 'N')
  {
    /*parses the first coordinate values and makes a point*/
    printf("Enter first coordinate. ex. \"x1, y1\" ");
    scanf("%s", str);
    x = parse(str);
    scanf("%s", str);
    y = parse(str);
    p1 = makePoint(x,y);
    /*parses the second coordinate value and makes a point*/
    printf("Enter second coordinate. ex. \"x2, y2\" ");
    scanf("%s", str);
    x = parse(str);
    scanf("%s", str);
    y = parse(str);
    p2 = makePoint(x,y);

    printf("You entered coordinates: (%d, %d), (%d, %d)\n",
      p1->xCoord, p1->yCoord, p2->xCoord, p2->yCoord);
    // distance functin and print aqui
    float distance; 
    distance = sqrt(((double)pow((p2->xCoord - p1->xCoord),2)
      +(double)pow((p2->yCoord - p1->yCoord),2)));
    printf("Distance: %f\n", distance);
    
    do
    {
      printf("Another? (y/n)");
      scanf("%s",str);
      c = *str;
    }while(c != 'n' && c != 'N' &&  c != 'y' && c != 'Y');

    free(p1);
    free(p2);
    p1 = NULL;
    p2 = NULL;
  }
  return 0;
}