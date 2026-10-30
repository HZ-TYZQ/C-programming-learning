#include <stdio.h>

#define MAX_ARRAY_LENGTH 10

void selectionSort(int arr[], int n, int order) {
  /* Original
    if (order == 1) {

      for (int i = 0; i < n - 1; i++) {

        int maxIndex = i;

        for (int j = i + 1; j < n; j++) {

          if (arr[j] > arr[maxIndex]) {

            maxIndex = j;
          }
        }

        int temp = arr[maxIndex];
        arr[maxIndex] = arr[i];
        arr[i] = temp;
      }
    } else if (order == 2) {

      for (int i = 0; i < n - 1; i++) {

        int minIndex = i;

        for (int j = i + 1; j < n; j++) {

          if (arr[j] < arr[minIndex]) {

            minIndex = j;
          }
        }

        int temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
      }
    } else {

      printf("wrong order.\n");
    }
  */
  // Current
  for (int i = 0; i < n - 1; i++) {

    if (order != 1 && order != 2) {
      printf("wrong order.\n");
      return;
    }

    for (int j = i + 1; j < n; j++) {

      int selectedIndex = i;

      if ((order == 1 && arr[j] > arr[selectedIndex]) ||
          (order == 2 && arr[j] < arr[selectedIndex])) {

        selectedIndex = j;
      }

      int temp = arr[selectedIndex];
      arr[selectedIndex] = arr[i];
      arr[i] = temp;
    }
  }
}

int main(void) {
  int arr[MAX_ARRAY_LENGTH] = {4, 2, 0, 1, 9, 5, 7, 8, 3, 6};

  int choice = 0;

  do {

    printf("1: show the array\n2: sort the array\n0: exit\n");
    scanf("%d", &choice);

    if (choice == 1) {

      for (int i = 0; i < MAX_ARRAY_LENGTH; i++) {

        printf("%d, ", arr[i]);
      }
      printf("\n");
    }

    if (choice == 2) {

      int sortChoice = 0;

      printf("1: sort descending\n2: sort ascending\n");
      scanf("%d", &sortChoice);

      selectionSort(arr, MAX_ARRAY_LENGTH, sortChoice);
    }

    if (choice == 0) {

      printf("exit");
    }

  } while (choice != 0);
}
