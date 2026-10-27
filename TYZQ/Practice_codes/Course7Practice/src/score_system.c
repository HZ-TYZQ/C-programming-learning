#include <stdio.h>

#define MAX_STUDENTS 10

// Function prototype
int input_scores(int scores[], int capacity);

int main(void) {

  int scores[MAX_STUDENTS] = {0};
  int n = 0;
  int choice = -1;

  do {
    printf("\n===== Student Score System =====\n");
    printf("1. Input Scores\n");
    printf("2. Display Scores\n");
    printf("3. Statistics\n");
    printf("4. Search\n");
    printf("5. Sort Ascending\n");
    printf("0. Exit\n");

    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1) {
      return 1;
    }

    switch (choice) {

    case 1:
      n = input_scores(scores, MAX_STUDENTS);
      printf("Current count: %d\n", n);
      break;

    case 2:
    case 3:
    case 4:
    case 5:
      printf("Feature not implemented yet.\n");
      break;

    case 0:
      printf("Goodbye!\n");
      break;

    default:
      printf("Invalid choice!\n");
    }

  } while (choice != 0);

  return 0;
}

// Step 1: Input function
int input_scores(int scores[], int capacity) {

  int student_count = 0;
  int input_number = 0;

  // TODO: Your code goes here
  do {

    printf("Please input the number of students: ");

    if (scanf("%d", &input_number) != 1) {

      printf("Input error.\n");
      continue;
    }

    if (input_number < 1 || input_number > capacity) {

      printf("Invalid input, please retry.\n");
      continue;
    }

    student_count = input_number;

  } while (student_count == 0);

  int score = -1;

  for (int i; i < student_count; i++) {

    printf("Please input the integer score of student %d:", i + 1);

    do {
      //
      scanf("%d", &score);

      if (score < 0 || score > 100) {

        printf("Invalid input, please retry.\n");
        continue;
      }

      scores[i] = score;

    } while (scores[i] == 0);
  }

  return student_count;
}
