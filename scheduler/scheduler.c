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

/*need another counter for classes if regestering 
more than one semsester at a time*/
int numClasses=0;
/* global array to hold the created people */
int people=0;
struct Person* createdPeople[1000];

/******************************************************************* 
 * Each parameter’s type and name: char* firstname, char*lastname,
 * int idnum, int student
 *  input and/or output: none 
 * Function’s return value: struct Person pointer
 * creates a Person struct and assigns values of firstName, lastName, 
 * ID, and isStudent
 * if person already exists they will be pointed to, not duplicated
 * Function’s algorithm: malloc and struct assignment
 ********************************************************************/

struct Person * createPerson(char* firstname, char* lastname, int idnum,
          int student)
{
  /*checks for the student ID in the current createdPeople
  array and returns a pointer to that person if they already exist*/
  int i;
  struct Person* temp;

  for(i = 0; i < people; i++)
  {
    if(createdPeople[i]->ID == idnum)
    {
      return createdPeople[i];
    }
  }

  /*creates temp struct Person* and assigns values*/
  
  /*allocates memory for the struct Person created*/
  temp = malloc(sizeof(struct Person));
  /* malloc the first and last name as well */
  temp->firstName = malloc(sizeof(char)*(strlen(firstname)+1));
  temp->lastName = malloc(sizeof(char)*(strlen(lastname)+1));


  /*assign values to the person */
  strcpy(temp->firstName, firstname);
  strcpy(temp->lastName,lastname);
  
  temp->ID = idnum;
  temp->isStudent = student;
  /*add them to the createdPeople array and increment people created */
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
  /* malloc for department since its a string*/
  char* department;
  int CRN;
  /* persons should already be malloced so just point to them */
  struct Person* teacher;
  /*ok to assume no larger than 500*/
  int regCapacity;
  
  /*array containing pointers to students*/
  
  struct Person** students; 
  int enrolled; 

};

/*********************************************************************** 
 * Each parameter’s type and name: char* dept, int coursenum,
 * struct Person* instructor, int cap
 * input and/or output: none
 * Function’s return value: struct UNMclass pointer
 * creates a struct UNMclass pointer on the heap and assigns the values
 * of department, CRN, teacher and regCapacity
 * also creates an array of Person pointers to hold the students enrolled
 * if error creating class, CRN will be set to zero
 * Function’s algorithm: structs assignment, malloc
 ***********************************************************************/

struct UNMclass * createunmclass(char* dept, int coursenum,
        struct Person* instructor, int cap)
{
  struct UNMclass* tempClass;
  /*allocates memory for the struct Person created*/
  tempClass = malloc(sizeof(struct UNMclass));
  /*allocate memory for the pointer to Person pointer of size 500*/
  tempClass->students = malloc(sizeof(struct Person)* 500); 
  /*is instructor is a student then class is invalid
  still have to return a struct UNMclass pointer
  so sets all int values to 0, department to Invalid Class
  leaves teacher unset and places the class in the schedule
  so we can free it*/
  if(instructor->isStudent == 1)
  {
    tempClass->department =malloc(sizeof(char)*15);
    strcpy(tempClass->department,"Invalid Class");
    tempClass->CRN = 0;
    tempClass->regCapacity =0;
    tempClass->enrolled =0;
    numClasses++;
    return tempClass;
  }
  /*mallocs the length of the string assigned to department*/
  tempClass->department =malloc(sizeof(char)*(strlen(dept)+1));
  /*assigns the values of the UNMclass to params
   increments number of classes,sets enrolled students to zero*/
  strcpy(tempClass->department,dept);
  tempClass->CRN = coursenum;
  tempClass->teacher = instructor;
  tempClass->regCapacity = cap;
  /*Regcapacity can never be negative or zero students*/
  if(cap < 1)
  {
    tempClass->regCapacity =1;
  } 
  tempClass->enrolled =0;
  numClasses++;
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
 * Each parameter’s type and name: struct Person* student,
 * struct UNMclass* course
 * input and/or output: none
 * Function’s return value: int
 * enroll should return a zero if enrollment was successful 
 * and a different number otherwise. Enrollment is unsuccessful 
 * if a UNMclass is full or a person is not a student.
 * Function’s algorithm: struct assignment, field access 
 ***********************************************************************/
int enroll(struct Person* student, struct UNMclass* course)
{ 
  
  int i;
  /*if the Person is not a student */
  if(student->isStudent == 0) return -1;
  /*if Person is a student enrollment must not be at capacity*/
  if(course->enrolled >= course-> regCapacity) return -1;
  
  /*makes sure to not double enroll a Person*/
  for(i = 0; i < course->enrolled; i++)
  {
    if(course-> students[i]->ID == student->ID) 
    {
      return -1;
    }
  } 
  
  /*enrolls new student in the course and increments enrolled students */
  course-> students[course->enrolled] = student;
  course->enrolled++;

  return 0;
}

/*********************************************************************** 
 * Each parameter’s type and name: struct Person* student, 
 * struct UNMclass* schedule[]
 * input and/or output: printed schedule with the name of the person 
 * followed by their courses on new lines
 * Function’s return value: void
 * this function prints the schedule of the associted person if they are 
 * a student, by looking through the full schedule of classes 
 * Function’s algorithm: printf 
 ***********************************************************************/

void printschedule(struct Person* student, struct UNMclass* schedule[])
{
  int sizeEnrolled; 
  int i;
  int k;
  i=0;
 
  if(student->isStudent != 1) return;
    /* while i is less than the number of classes*/
    while(i< numClasses)
    {
      /* access the number of students enrolled for a class
       assign to sizeEnrolled*/
      sizeEnrolled = schedule[i]->enrolled;
      for(k=0; k < sizeEnrolled; k++)
      {
        /*if student ID is found in the class then schedule is printed*/
        if(schedule[i]->students[k]->ID == student->ID)
        {
          printunmclass(schedule[i]);
          break;
        } 
      } 
      i++;
    }     
}

/********************************************************************* 
 * Each parameter’s type and name: none
 * input and/or output: none
 * Function’s return value: void
 * frees the memory allocated from the heap for struct Persons created
 * Function’s algorithm: free() malloced memory
 *********************************************************************/
void freeThePeople()
{
  int i;
  
  for(i = 0; i < people; i++)
  {
    free(createdPeople[i]->firstName);
    free(createdPeople[i]->lastName);
    free(createdPeople[i]);
  }
  people =0;
} 

/********************************************************************* 
 * Each parameter’s type and name: struct UNMclass* schedule[]
 * input and/or output: none
 * Function’s return value: void
 * frees the allocated memory from the heap that held classes for a 
 * particular semester 
 * Function’s algorithm: free() malloced memory
 *********************************************************************/
void freeClass(struct UNMclass* schedule[])
{
  int i;
  i =0;

  while(i<numClasses)
  {
    
      free(schedule[i]->department);
      free(schedule[i]->students);
      free(schedule[i]);
      i++;    
  }
  numClasses =0;
} 

int main()
{ 
  struct UNMclass * testSchedule[20];
/* Thank you https://www.fakenamegenerator.com/gen-random-us-us.php
     for all the names in this program. */
  char * fns[] = {"Sophia","Eric","James","Gabriel","Cecilia"};
  char * lns[] = {"Johnson", "Franklin","Collins","Rivera","Beck"};
 
  /*creating array pointer of struct UNMclass to hold all the classes 
  offered during the spring of 19*/
  /*assumes fewer than 1000 classes*/
  struct UNMclass* spring19[1000]; 

  /*Here's some testing code the graders will test your code on.
    You'll need to write additional tests like we have here. */ 
  int i,j;
  /* declare your spring19 datastructure here */
  struct Person* instructor = createPerson("Elliot","Velez",235, 0);
  struct Person* instructor2 = createPerson("Silvia","Johnson",236, 0);
  
  for (i=0; i<12; i++)
  { /*create some CS classes */
    spring19[i]=createunmclass("CS", 200+i*10+1, instructor, 3);
  }
  
  for (i=0; i<5; i++)
  { /*create some Math classes */
    spring19[12+i]=createunmclass("Math", 108+i, instructor2, 3);
  }
  
  /*can we enroll a prof in a class? */
  for (i=0; i<17; i++)
  {
    enroll(instructor, spring19[i]);
  }
 
  printperson(instructor); /*should print out prof. before name */
  printschedule(instructor, spring19); /*shouldn't print anything */
  printf("\n");
  
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
  freeThePeople();
  freeClass(spring19);

  /*tests should return nothing if code is working correctly*/
  
  /*Person created should not be equal to Null*/
  createPerson("Craig", "Parry",500,1);
  if(createdPeople[0] == NULL)
  {
    printf("Unsucessful create person \n");
  } 
  /*cannot create the same person twice, by ID number
  can have duplicate names, but not ID numbers */
  /*should look through the people already created 
  and return pointer to already created person */
  createPerson("Craig", "Parry",500,1);
  if(people != 1)
  {
    printf("people: %d, person recreated.\n",people);
  } 
  /*create class if Person is not a professor*/
  testSchedule[0]=createunmclass("CS",101,createdPeople[0],0);
  if(strcmp(testSchedule[0]->department,"Invalid Class")!=0)
  {
    printf("Error: Professor cant be a student");
  }
  /*whether create class returns null*/
  if(testSchedule[0]==NULL)
  {
    printf("Created class does not exist\n");
  } 

  /*create professor*/
  createPerson("teacher", "mcteacher",501,0);
  
  testSchedule[1] = createunmclass("CS",101,createdPeople[1],2);
  /*enrolling studnet shoud return a zero for success, -1 otherwise*/
  if(enroll(createdPeople[0],testSchedule[1])!=0)
  {
    printf("Error enrolling student\n");
  }
  /*makes sure to not double enroll a Person 
  should return -1 for error enrolling*/
  if(enroll(createdPeople[0],testSchedule[1])!=-1)
  {
    printf("Error: studnet was allowed to enroll multiple times\n");
  }
  /*try to enroll professor in class 
  should return -1 for error enrolling*/
  if(enroll(createdPeople[1],testSchedule[1])!=-1)
  {
    printf("Error: you cant enroll a teacher\n");
  }
  /*shoud be under capacity and returning a 0*/
  if(enroll(createPerson("Student","one",2,1),testSchedule[1])!=0)
  {
    printf("Error enrolling studnet\n");
  }
  /*course has reached capacity*/
  /*enrolling should be over capactity of students in the class
  and returning a -1*/
  if(enroll(createPerson("Student","two",3,1),testSchedule[1])!=-1)
  {
    printf("Error: overenrolled class\n");
  }

  /*print schedule if person is not a student*/
  /*should do nothing since professor*/
  printschedule(createdPeople[1],testSchedule);

  /*duplicate classes: can have duplicates at this point
  so a professor can have multiple sections and error classes 
  can all be zero*/
  
  /* before exiting, free the memory. Left as an exercise
     for the student. */
 
  /*frees the Persons created and the full schedule of classes created 
  from memory stored on the heap*/
  freeThePeople();
  freeClass(testSchedule);
  return 0;

}
