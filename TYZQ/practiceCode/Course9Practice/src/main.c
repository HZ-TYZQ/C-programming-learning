#include "input.h"
#include "student.h"
#include <stdio.h>

int main(void)
{
  struct Student students[MAX_STUDENTS] = {0};

  int count = 0;
  int choice;
  do
  {

    printf("========== SRMS ==========\n1. Add Student\n2. Display All "
           "Students\n0. Exit\n==========================\n");

    // Enter choice.

    if (!readInt("Enter your choice: ", &choice))
    {
      return 0;
    }

    switch (choice)
    {

    case 1:
    {

      struct Student newStudent;

      if (!readInt("Student ID: ", &newStudent.id))
      {

        return 0;
      }

      if (readString("Student name: ", newStudent.name,
                     sizeof(newStudent.name)) == NULL)
      {
        return 0;
      }

      for (int i = 0; i < SUBJECT_COUNT; i++)
      {

        while (1)
        {
          int scoreInput;
          printf("Subject %d ", i + 1);

          if (!readInt("Score: ", &scoreInput))
          {

            return 0;
          }

          if (scoreInput >= 0 && scoreInput <= 100)
          {
            newStudent.scores[i] = scoreInput;
            break;
          }

          printf("Invalid score.\n");
          continue;
        }

        printf("\n");
      }
      int result = addStudent(students, &count, &newStudent);
      if (result == 0)
      {

        printf("The list is full.\n");
        break;
      }

      if (result == -1)
      {

        printf("Repeated student ID.\n");
        break;
      }

      printf("Add student successfully!\n");
      break;
    }
    case 2:

      if (count <= 0)
      {

        printf("No students found.\n");

        break;
      }

      printAll(students, count);

      break;

    case 0:

      printf("Goodbye!\n");
      return 0;

    default:

      printf("Invalid choice.\n");
    }
  } while (1);

  return 0;
}
