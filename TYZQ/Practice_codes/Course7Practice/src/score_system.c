#include <stdio.h>

#define MAX_STUDENTS 10

// Function prototype
int input_scores(int scores[], int capacity);
void display_scores(int scores[], int n);
void show_statistics(int scores[], int n);
int search_all_scores(int scores[], int n, int target, int found_indices[]);
void bubble_sort(int scores[], int n);

// TODO: Add a input function after Lecture 8 to avoid dead cycle

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
    scanf("%d", &choice);

    switch (choice) {

    case 1:
      n = input_scores(scores, MAX_STUDENTS);
      printf("Current count: %d\n", n);
      break;

    case 2: {

      if (n == 0) {

        printf("Please input scores first.\n");
        break;
      }

      display_scores(scores, n);

      break;
    }
    case 3: {

      if (n == 0) {

        printf("Please input scores first.\n");
        break;
      }

      show_statistics(scores, n);
      break;
    }

    case 4: {

      if (n == 0) {
        printf("Please input scores first.\n");
        break;
      }

      int target;
      int found_indices[MAX_STUDENTS];
      int count;

      printf("Please input a target score: ");
      scanf("%d", &target);

      count = search_all_scores(scores, n, target, found_indices);

      if (count == 0) {

        printf("Score not found.\n");

      } else {

        printf("Found %d students:\n", count);

        for (int i = 0; i < count; i++) {

          printf("Student %d: %d\n", found_indices[i] + 1,
                 scores[found_indices[i]]);
        }
      }

      break;
    }

    case 5: {

      if (n == 0) {

        printf("Please input scores first.\n");
        break;
      }

      bubble_sort(scores, n);

      printf("Scores sorted successfully!");

      display_scores(scores, n);

      break;
    }

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

  do {

    printf("Please input the number of students: ");

    scanf("%d", &input_number);

    if (input_number < 1 || input_number > capacity) {

      printf("Invalid input, please retry.\n");
      continue;
    }

    student_count = input_number;

  } while (student_count == 0);

  for (int i = 0; i < student_count; i++) {

    int score = -1;

    printf("Please input the integer score of student %d:", i + 1);

    do {

      scanf("%d", &score);

      if (score < 0 || score > 100) {

        printf("Invalid input, please retry: ");
        continue;
      }

    } while (score < 0 || score > 100);

    scores[i] = score;
  }

  return student_count;
}

void display_scores(int scores[], int n) {

  printf("\n===== Student Scores =====\n");

  for (int i = 0; i < n; i++) {

    int student_number = i + 1;

    printf("Student %d: %d\n", student_number, scores[i]);
  }
}

void show_statistics(int scores[], int n) {

  int total_score = 0;
  double average;

  for (int i = 0; i < n; i++) {

    total_score += scores[i];
  }

  average = (double)total_score / n;

  int max_score = scores[0];
  int min_score = scores[0];

  for (int i = 1; i < n; i++) {

    if (max_score < scores[i]) {
      max_score = scores[i];
    }

    if (min_score > scores[i]) {
      min_score = scores[i];
    }
  }

  int pass_count = 0;

  for (int i = 0; i < n; i++) {

    if (scores[i] >= 60) {
      pass_count++;
    }
  }

  printf("\n===== Statistics =====\n");
  printf("Average: %.2f\n", average);
  printf("Maximum: %d\n", max_score);
  printf("Minimum: %d\n", min_score);
  printf("Pass: %d\n", pass_count);
}

int search_all_scores(int scores[], int n, int target, int found_indices[]) {

  int count = 0;

  for (int i = 0; i < n; i++) {

    if (scores[i] == target) {

      found_indices[count] = i;

      count++;
    }
  }

  return count;
}

void bubble_sort(int scores[], int n) {

  for (int i = 0; i < n - 1; i++) {

    for (int j = 0; j < n - i - 1; j++) {

      int temp = scores[j];
      if (temp > scores[j + 1]) {

        scores[j] = scores[j + 1];
        scores[j + 1] = temp;
      }
    }
  }
}
