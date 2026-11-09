#include "student.h"
#include <stdio.h>
#include <string.h>

void printStudent(const struct Student *student)
{

  printf("%-8d%-8s", student->id, student->name);
  for (int i = 0; i < SUBJECT_COUNT; i++)
  {

    printf("%-8d", student->scores[i]);
  }

  printf("\n");
}

void printAll(const struct Student *students, int count)
{

  printf("%-8s%-8s%-8s%-8s%-8s\n", "ID", "Name", "C", "Math", "English");
  printf("----------------------------------------\n");

  for (int i = 0; i < count; i++)
  {

    printStudent(students + i);
  }
}

int addStudent(struct Student students[], int *count,
               const struct Student *newStudent)
{

  if (*count >= MAX_STUDENTS)
  {

    return 0;
  }

  for (int i = 0; i < *count; i++)
  {

    if ((students + i)->id == newStudent->id)
    {

      return -1;
    }
  }

  students[*count] = *newStudent;
  *count += 1;
  return 1;
}

int findById(const struct Student students[], int count, int id)
{
  for (int i = 0; i < count; i++)
  {
    if (students[i].id == id)
    {
      return i;
    }
  }

  return -1;
}

int findByName(const struct Student students[], int count, const char name[])
{
  for (int i = 0; i < count; i++)
  {
    if (strcmp(name, students[i].name) == 0)
    {
      return i;
    }
  }
  return -1;
}
