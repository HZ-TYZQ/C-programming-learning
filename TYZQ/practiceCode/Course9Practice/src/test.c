#include "student.h"

int main(void) {

  struct Student students[] = {
      {101, "Mia", {80, 90, 100}},
      {102, "Ben", {70, 75, 80}},
      {103, "Leo", {100, 95, 90}},
  };

  int count = 3;

  printAll(students, count);

  return 0;
}
