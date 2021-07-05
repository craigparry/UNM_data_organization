/*************************************************/
/* Craig Parry                                   */
/* Date 09/28/18                                 */
/* CS 241 Section # 002                          */
/* hw-04 maze.c reads mazes from input and solves*/
/* the randomly generated mazes generated from   */
/* mazegeneration.py which auto generates mazes  */
/* ranging from 1 cell to 40 cells               */
/*************************************************/ 

#include <stdio.h>

/*max row and column definitions*/
#define ROW 82
#define COL 162
/*character maze double array which will hold the input maze globally*/
char maze[ROW][COL];
/*character double array that holds found locations globally*/
char disc[ROW][COL];
/* variable for read input characters*/
char c;
/*boolean for errors caused by input*/
int errorCase;

/*function declarations that weren't explicitly declared*/
void errorCheck(void);
int colCount(void);
int rowCount(void);

/************************************************************ 
 * parameter’s type and name: none 
 * input: none
 * output: none 
 * Function’s return value: void
 * This function accesses the global char maze double array 
 * and clears all previous input replacing it with a ' '
 * Function’s algorithm: nested for loops
 ***********************************************************/
void clearMaze(void)
{
  extern char maze[ROW][COL];
  int i;
  int j;
  
  /*increments rows*/
  for(i=0; i < ROW; i++)
  {
    /*increments columns assigns values to ' '*/
    for (j=0; j < COL; j++)
    {   
     maze[i][j] = ' ';
    }
  }    
}

/************************************************************************* 
 * parameter’s type and name: none 
 * input: none
 * output: none
 * Function’s return value: int number of collumns occupied by '+' or '-'
 * This function accesses the global char maze double array and counts 
 * the number of columns occupied by a '+' or a  '-' and returns that value
 * Function’s algorithm: for loop
 *************************************************************************/
int colCount(void)
{
  int i;
  char temp;
  int count;
  count = 0;
  /*increments columns sets temp to char stored in location of array*/
  for(i=0;i < COL; i++)
  {
    temp = maze[0][i];
    /*checks if the value of the char at that location of array is 
    a '-' or '+' and increments count if true and returns when false*/
    if(temp == '-'|| temp == '+')
    {
      count++;
    }else return count;
  }  
  return 0;
}

/************************************************************************* 
 * parameter’s type and name: none 
 * input: none
 * output: none
 * Function’s return value: int number of rows occupied by '+' or '|'
 * This function accesses the global char maze double array and counts 
 * the number of rows occupied by a '+' or a  '|' and returns that value
 * Function’s algorithm: for loop
 *************************************************************************/
int rowCount(void)
{
  
  char temp;
  int i,count;
  count = 0;
  /*increments rows and sets temp to char stored in location of array*/
  for(i=0;i < ROW; i++)
  {
    temp = maze[i][0];
    /*checks if the value of the char at that location of array is 
    a '|' or '+' and increments count if true and returns when false*/
    if(temp == '|'|| temp == '+')
    {
      count++;
    }else return count;
  }  
  return 0;
}

/************************************************************************* 
 * parameter’s type and name: none 
 * input: none
 * output: none
 * Function’s return value: void
 * This function accesses the global char maze double array and uses 
 * colCount() and rowCount() to find the last cell of the maze then 
 * places a star at that location
 * Function’s algorithm: array indexing 
 *************************************************************************/
void findLastCell(void)
{
  extern char maze[ROW][COL];
  int col;
  int row;
  /*sets indexes corresponding to the last cell*/
  col = (colCount()-3);
  row = (rowCount()-2);
  
  /*sets location in maze double array to char '*' */
  maze[row][col] = '*';
}

/************************************************************************* 
 * parameter’s type and name: int row, int col 
 * input: none
 * output: none
 * Function’s return value: int boolean 1 or 0
 * This function accesses the global char maze double array and checks 
 south, then east, then north, then west for open spaces to search for the 
 end of the maze. after it discovers a location that is not blocked by a 
 wall and has not been previously discovered it marks that location as 
 discovered in the global disc double array. Once it finds the '*' placed
 at the end of the maze if recursively places a '*' a each location that it
 visited without hitting a dead end. 
 * Function’s algorithm: recursive backtracking using south, east, north west 
 * as the ordered rule for directional checks
 *************************************************************************/
int pathFinder(int row, int col)
{ 
  extern char maze[ROW][COL];
  extern char disc[ROW][COL];

 
  int found;
  found = 0;
  /*call pathfinder with first location of node row 1 col 2*/
  /*needs a check for the end of the board to set basecase */
  /*if the base case is found then return 1 for true*/
  if(maze[row][col] == '*')
  {
    return 1;
  } 
  /*set first location to discovered*/
  disc[row][col] = 'y';
  
  /*checks if values passed are not going to fall off of the board
  before incrementing or decrementing them*/
  if((row+1) < ROW && (row-1) >= 0 && (col+2) < COL && (col-2) >=0)
  {
    /*checks if locaton south is undiscovered and a free space
    if true then sets location to discoverd and calls pathFinder
    with the new location*/
    if((maze[row+1][col] == ' ' || maze[row+1][col] == '*') 
        && disc[row+1][col] != 'y') 
    { 
      disc[row+1][col] = 'y';
      found = pathFinder((row + 1),(col));

      /* if the path returned found the base case then set this location
      at row, col to '*' */
      if(found == 1)
      {
        maze[row][col]='*';
        return 1;
      }
    }

    /*checks if locaton west is undiscovered and a free space
    if true then sets location to discoverd and calls pathFinder
    with the new location*/
    if((maze[row][col+2] == ' ' || maze[row][col + 2] == '*')
        && disc[row][col+2] != 'y') 
    {
      disc[row][col+2] = 'y';
      found = pathFinder((row),(col+2));

      /* if the path returned found the base case then set this location
      at row, col to '*' */
      if(found == 1)
      {    
        maze[row][col]='*';
       return 1;
      }
    } 

    /*checks if locaton north is undiscovered and a free space
    if true then sets location to discoverd and calls pathFinder
    with the new location*/
    if((maze[row-1][col] == ' ' || maze[row-1][col] == '*')&& disc[row-1][col] != 'y') 
    { 
      disc[row-1][col]= 'y';
      found = pathFinder((row - 1),(col));

      /* if the path returned found the base case then set this location
      at row, col to '*' */
      if(found == 1)
      {
        
        maze[row][col]='*';
        return 1;
      }
    }

    /*checks if locaton west is undiscovered and a free space
    if true then sets location to discoverd and calls pathFinder
    with the new location*/
    if ((maze[row][col - 2] == ' ' || maze[row][col-2] == '*')&& disc[row][col - 2] != 'y')
    {
      disc[row][col - 2] = 'y';
      found = pathFinder((row),(col-2));

      /* if the path returned found the base case then set this location
      at row, col to '*' */
      if(found == 1)
      {
        maze[row][col]='*';
        return 1; 
      }
    }
  }
  return 0;
}

/************************************************************************* 
 * parameter’s type and name: none 
 * input: auto generated maze or file of auto generated mazes
 * output: none
 * Function’s return value: void
 * This function reads in command line inupt or input from a file 
 * each character that is read in on a single line will be stored in each 
 * row of the global maze double array until the input reaches a double 
 * newline character (if input is mazes generated from mazegeneration.py
 * it will store properly)
 * Function’s algorithm: array indexing 
 *************************************************************************/
void readInMaze(void)
{ 
  extern char maze[ROW][COL];
  extern char c;
  int i;
  int j;

  /* gets input char and assign values to the index of the maze double 
  array at row i and column j*/
  /* if c is newline before the maze get another character*/
  while((c = getchar())=='\n');
  /*loop the indexes of the maze double array*/
  for(i=0; i < ROW && c !=EOF;i++)
  {
    for(j=0;j < COL && c != EOF;j++)
    {
      /* newlines move the index of row to the next row
      if two newlines in a row stop reading in the maze
      otherwise read the next char and put in next index value */
      if (c == '\n')
      {
        maze[i][j] = c;
        c = getchar();
        if(c == '\n') return;
        else break;
      }else 
      {
        maze[i][j]= c;
        c = getchar();
      }
    }
  }
}

/************************************************************************* 
 * parameter’s type and name: none 
 * input: none
 * output: none
 * Function’s return value: void
 * this function checks to see if there are any characters read into the 
 * maze that are not '+' , ' ', '\n', '-', or '|' and checks the maze for 
 * symmetry by the number of nodes
 * if there is an error it changes errorCase to true
 * Function’s algorithm: array indexing and using integer division on the 
 * column and rows to find match the number of nodes of each for symmetry 
 *************************************************************************/
void errorCheck(void)
{
  int i;
  int j;
  extern int errorCase;
  extern char maze[ROW][COL];
  errorCase =0;
  /*loops over the entire maze double array and checks for invalid char
  if there is a invalid character change errorCase to true*/
  for(i=0; i < rowCount(); i++)
  {
    for (j=0; j < (colCount()+1); j++)
    { if(maze[i][j] == ' ' || maze[i][j] == '+' || maze[i][j] == '-' 
            || maze[i][j] == '|' || maze[i][j] == '\n')
      {
        ;
      } 
      else 
      {
        errorCase =1;
        return;
      }

    }
  }

  /*checks to see whether the maze is square, if it is not 
  changes errorCase to true */
  if((rowCount()/2) != (colCount()/4))
  {
    errorCase =1;
    return; 
  }

}

/************************************************************************* 
 * parameter’s type and name: none 
 * input: none
 * output: none
 * Function’s return value: void
 * this function loops over and clears the disc double array by placeing
 * 'n' inside of each index 
 * Function’s algorithm: array indexing
 *************************************************************************/
void clearDisc(void)
{ 
  extern char disc[ROW][COL];
  int i;
  int j;

  /*loops over the maze double array and places value to 'n' */
  for(i=0; i < ROW; i++)
  {
    for (j=0; j < COL; j++)
    {   
     disc[i][j] = 'n';
    }
  }    
}

/************************************************************************* 
 * parameter’s type and name: none 
 * input: none
 * output: prints out Error message, No Solution or a solved maze 
 * Function’s return value: void
 * this function checks the error case global variable for true and if 
 * true prints out Error. If the pathfinder returned without a solve 
 * then prints No Solution. Otherwise prints out the solved maze.
 * Function’s algorithm: array indexing
 *************************************************************************/
void printMaze(void)
{
  extern char maze[ROW][COL];
  int i;
  int j;
  
  if(maze[0][0] != ' ')
  {
    /*checks for maze with no solution prints no solution if true*/
    if(errorCase == 0 && maze[1][2] == ' ')
    {
      printf("No Solution\n\n");
      return;
    } 
    /*checks for true errorCase and prints Error if true*/
    if(errorCase ==1)
    {
      printf("Error\n\n"); 
      return;
    } 
  
    /*loops over the current array maze and prints each char at its
    current index*/
    for(i=0; i < rowCount(); i++)
    {
      for (j=0; j < (colCount()+1); j++)
      {
        if(maze[i][j] != '\n')
        {
          printf("%c", maze[i][j]);
        }else 
        {
          printf("%c", maze[i][j]);
          break;
        }
      } 
    }
    printf("\n");  
  }
}

int main(void)
{ 
  extern char maze[ROW][COL];
  extern char c;
  extern int errorCase;
  
  /* wile the input is not at the end of file 
  read in the current maze, check for errors, if error is true 
  print, else find the last cell and use pathfinder to solve
  then print maze and clear the global maze and disc double arrays */
  while(c !=EOF)
  {
    readInMaze();
    errorCheck();
    if(errorCase == 1){
      printMaze();
      clearMaze();
    } else 
    {
      findLastCell();
      pathFinder(1,2);
      printMaze();
      clearMaze();
      clearDisc();
    } 
  }
  return 0;
}
