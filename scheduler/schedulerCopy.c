/****************************************************************** 
 * Craig Parry
 * 11/05/18
 * this file creates persons who are either students or professors 
 * and also creats UNMclasses. Professors can be assigned to those 
 * classes and students can then be enrolled into those classes for
 * a particular semster. 
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*creates struct for Person*/
struct Person
{
  char* firstName;
  char* lastName;
  int ID;
  int isStudent;
};

// global array to hold the created people
int people=0;
struct Person* createdPeople[1000];
// createdPeople = malloc(sizeof(createdPeople));

/******************************************************************* 
 * Each parameter’s type and name: char* firstname, char*lastname,
 * int idnum, int student
 *  input and/or output: none 
 * Function’s return value: struct Person pointer
 * creates a Person struct and assigns values of firstName, lastName, 
 * ID, and isStudent
 * Function’s algorithm: malloc and struct assignment
 ********************************************************************/

struct Person * createPerson(char* firstname, char* lastname, int idnum,
          int student)
{
  
  /*creates temp struct Person* and assigns values*/
  struct Person* temp;
  /*allocates memory for the struct Person created*/
  temp = malloc(sizeof(struct Person));
  // malloc the first and last name as well
  temp->firstName = malloc(sizeof(firstname));
  temp->lastName = malloc(sizeof(lastname));

//!!!!! malloc: should also allocate space for firstName and lasName on the heap
  //assign values to the person
  strcpy(temp->firstName, firstname);
  strcpy(temp->lastName,lastname);
  
  temp->ID = idnum;
  temp->isStudent = student;
  //add them to the createdPeople array and increment people created
  createdPeople[people]= temp;
  people++;
  return temp;
  
}
/********************************************************************* 
 * Each parameter’s type and name: struct Person* p
 * input and/or output: outputs the first and last name of the person
 * Prof. is printed before thier name if not a student
 * Function’s return value: void
 * prints the first and last name of the person with a prof. prefix if 
 * not a student 
 * Function’s algorithm: Printf, Structs 
 *********************************************************************/

void printperson(struct Person* p){
  /*prints Prof. if not a student*/
  if(p->isStudent == 0) printf("Prof. "); 
  /*prints first and last name of pointer struct*/
  printf("%s %s\n",p->firstName,p->lastName);

}

/*struct to create a UNMclass*/ 
struct UNMclass
{
  // should malloc for department since its a string
  char* department;
  int CRN;
  // persons should already be malloced so just point to them 
  struct Person* teacher;
  int regCapacity;/*ok to assume no larger than 500*/
  
  /*array containing pointers to students*/
  // dont need to malloc since it is a fixed data structure inside the struct
  struct Person** students; 
  int enrolled; 

};

/*********************************************************************** 
 * Each parameter’s type and name: char* dept, int coursenum,
 * struct Person* instructor, int cap
 * input and/or output: none
 * Function’s return value: struct UNMclass*
 * creates a struct UNMclass pointer on the heap and assigns the values
 * of department, CRN, teacher and regCapacity
 * also creates an array of Person pointers to hold the students enrolled
 * Function’s algorithm: structs assignment, malloc
 ***********************************************************************/

struct UNMclass * createunmclass(char* dept, int coursenum,
        struct Person* instructor, int cap)
{
  struct UNMclass* tempClass;
  /*allocates memory for the struct Person created*/
  tempClass = malloc(sizeof(struct UNMclass));
  tempClass->department =malloc(sizeof(char*));
  tempClass->students = malloc(sizeof(struct Person)* 500); 
  
//!!!!! should also allocate space for any strings on the heap
// malloc department struct Person and struct Person* students[] 

  /*assigns the values of the UNMclass to params*/
  strcpy(tempClass->department,dept);
  tempClass->CRN = coursenum;
  tempClass->teacher = instructor;
  tempClass->regCapacity = cap;
  tempClass->enrolled =0;

  // malloc the students enrolled array as well
  return tempClass;
}

/************************************************************************ 
 * Each parameter’s type and name: struct UNMclass* c
 * input and/or output: outputs the department and teh course number
 * Function’s return value: void
 * prints the departments name and the course number seperated by a space
 * Function’s algorithm: Printf, Structs 
 ***********************************************************************/
void printunmclass(struct UNMclass* c)
{
  printf("%s %d\n",c->department,c->CRN); 
}

/*********************************************************************** 
 * Each parameter’s type and name: 
 * input and/or output: 
 * Function’s return value: 
 * creates a str

 * Function’s algorithm: 
 ***********************************************************************/
int enroll(struct Person* student, struct UNMclass* course)
{ 
  int enrollSize;
  int i;
  
  //printf("enrollSize %d \n", course->enrolled);

  if(student->isStudent == 0) return -1;
  if(course->enrolled < course-> regCapacity)
  { 
    
    for(i = 0; i < course->enrolled; i++)
    {
      if(course-> students[i]->ID == student->ID) 
      {
        return -1;
      }
    } 
  }

  course-> students[course->enrolled] = student;
  course->enrolled++;

  return 0;

/*enroll should return a zero if enrollment was successful 
and a different number otherwise. Enrollment is unsuccessful 
if a UNMclass is full or a person is not a student.*/

 
}

/*********************************************************************** 
 * Each parameter’s type and name: 
 * input and/or output: 
 * Function’s return value: 
 * creates a str

 * Function’s algorithm: 
 ***********************************************************************/

void printschedule(struct Person* student, struct UNMclass* schedule[])
{

  int sizeSchedule; 
  int sizeEnrolled; 
  int i;
  int k;
  i=0;
 
  // while class in the schedule[] is not null
  while(schedule[i])
  {

    
    // access the number of students enrolled for a class, assign to sizeEnrolled
    sizeEnrolled = schedule[i]->enrolled;
    for(k=0; k < sizeEnrolled; k++)
    {
      
      if(schedule[i]->students[k]->ID == student->ID)
      {
        printunmclass(schedule[i]);
        break;
      } 
    } 
    i++;
  } 

/*printschedule should look through the spring19 schedule of classes 
to find each one that the student is enrolled in. This method should 
print the department name followed by a space followed by the class 
number. Each course a student is enrolled in should be on a new line.
For instance, if a student “Julia Campbell” was enrolled in CS241, 
CS251, Math162, and English107, this method should print out:

CS 241  
CS 251  
Math 162  
English 107*/

}

// free malloced person probably will want to free all of the people 
// in the class
void freeThePeople()
{
  int i;
  
  for(i = 0; i < people; i++)
  {
    free(createdPeople[i]->firstName);
    free(createdPeople[i]->lastName);
    free(createdPeople[i]);
  }
} 

// freee class with all of the students included
void freeClass(struct UNMclass* schedule[])
{
  int i;
  i =0;

  while(schedule[i])
  {
    
      free(schedule[i]->department);
      free(schedule[i]->students);
      free(schedule[i]);
      i++;
    
  }
} 

/* Here are all the function declarations you need.
Comment them out as you need.*/




int main()
{
  /*creating array pointer of struct UNMclass to hold all the classes 
  offered during the spring of 19*/

  struct UNMclass* spring19[1000]; // assume that there are fewer than 1000 classes

  /*Here's some testing code the graders will test your code on.
    You'll need to write additional tests like we have here. */ 
  int i,j;
  /* declare your spring19 datastructure here */
  struct Person* instructor = createPerson("Elliot","Velez",235, 0);
  struct Person* instructor2 = createPerson("Silvia","Johnson",236, 0);
  
 // printf("1. here\n"); 

  for (i=0; i<12; i++)
  { /*create some CS classes */
    spring19[i]=createunmclass("CS", 200+i*10+1, instructor, 3);
  }

  //printf("2. here\n");
  for (i=0; i<5; i++)
  { /*create some Math classes */
    spring19[12+i]=createunmclass("Math", 108+i, instructor2, 3);
  }
  
  
  /*can we enroll a prof in a class? */
  for (i=0; i<17; i++)
  {
    enroll(instructor, spring19[i]);
  }
 // printf("3. here\n");
  printperson(instructor); /*should print out prof. before name */
  printschedule(instructor, spring19); /*shouldn't print anything */
  printf("\n");
 // printf("4. here \n"); 
  
  /* Thank you https://www.fakenamegenerator.com/gen-random-us-us.php
     for all the names in this program. */
  char * fns[] = {"Sophia","Eric","James","Gabriel","Cecilia"};
  char * lns[] = {"Johnson", "Franklin","Collins","Rivera","Beck"};
  
 // printf("4. here\n");
  for (i=0; i<5; i++)
  { /*create some random students */
    struct Person* student = createPerson(fns[i],lns[i],237+i, 1);
    for (j=0; j<17; j=j+i+1)
    { /*now let's enroll that student in random classes */
      enroll(student, spring19[j]);
    }
    printperson(student); 
    printschedule(student, spring19);
    printf("\n");
  }
  /* before exiting, free the memory. Left as an exercise
     for the student. */
  // freeSemester(spring19); 

  freeThePeople();
  freeClass(spring19);
  // printf("trying \n");
  // //end of the array 
  // printperson(createdPeople[people-1]);
  return 0;

  // struct Person* p1;
  // char* fname;
  // char* lname;
  // char a[]={'c','r','a','i','g','\0'};
  // char b[]={'p','a','r','r','y','\0'};
  // fname =a;
  // lname =b;
  // /*creates struct person and allocates memory on the heap
  // with function*/
  // p1 = createPerson(fname,lname,101510121,0);
  // printperson(p1);
  
  // if(strcmp(p1->firstName,fname)==0)
  // {
  //   printf("firstname correct\n");
  // }
  // if(strcmp(p1->lastName,lname)==0)
  // {
  //   printf("lastname correct\n");
  // }
  // if(p1->ID == 101510121)
  // {
  //   printf("ID correct\n");
  // }
  // if(p1->isStudent==1)
  // {
  //   printf("is student true");
  // }

  // /*frees memory allocated by createPerson function */
  // free(p1);

  
  // return 0;
}
