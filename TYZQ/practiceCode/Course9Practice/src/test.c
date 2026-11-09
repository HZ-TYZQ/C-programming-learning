#include "student.h"
#include <stdio.h>

int main(void)
{

  struct Student students[MAX_STUDENTS] = {
      {101, "Mia", {80, 90, 100}},
      {102, "Ben", {70, 75, 80}},
      {103, "Leo", {100, 95, 90}},
  };

  int count = 3;

  printAll(students, count);

  struct Student newStudent = {104, "Alice", {95, 98, 100}};

  struct Student duplicate = {104, "Another", {60, 70, 80}};

  int result_a;
  int result_b;

  result_a = addStudent(students, &count, &newStudent);
  printf("Add Alice: %d\n", result_a);
  printf("count: %d\n", count);

  printAll(students, count);

  result_b = addStudent(students, &count, &duplicate);
  printf("Add Another: %d\n", result_b);
  printf("count: %d\n", count);

  printAll(students, count);

  struct Student full[MAX_STUDENTS] = {0};
  int fullCount = 0;
  int allFilled = 1;

  for (int i = 0; i < MAX_STUDENTS; i++)
  {
    struct Student s = {200 + i, "Filler", {60, 70, 80}};

    if (addStudent(full, &fullCount, &s) != 1)
    {
      allFilled = 0;
    }
  }
  printf("fill %d students: %s (count=%d, expect %d)\n", MAX_STUDENTS,
         allFilled ? "PASS" : "FAIL", fullCount, MAX_STUDENTS);

  struct Student overflow = {999, "Overflow", {100, 100, 100}};

  int before = fullCount;
  int result_c = addStudent(full, &fullCount, &overflow);

  printf("add when full: %d (expect 0), count: %d (expect %d) -> %s\n",
         result_c, fullCount, before,
         (result_c == 0 && fullCount == before) ? "PASS" : "FAIL");

  printf("last slot unchanged: ");
  printStudent(&full[MAX_STUDENTS - 1]);

  printf("Search 102:\n");
  printf("%d\n", findById(students, count, 102));
  printf("Search 999:\n");
  printf("%d\n", findById(students, count, 999));

  printf("%d\n", findByName(students, count, "Mia"));
  printf("%d\n", findByName(students, count, "Unknown"));
  printf("%d\n", findByName(students, count, "mia"));

  struct Student alice = {104, "Alice", {95, 98, 100}};

  int total;
  double average;
  int maximum;
  int minimum;

  calculateStats(&alice, &total, &average, &maximum, &minimum);

  printf("Total: %d\n", total);
  printf("Average: %.2f\n", average);
  printf("Maximum: %d\n", maximum);
  printf("Minimum: %d\n", minimum);

  return 0;
}
