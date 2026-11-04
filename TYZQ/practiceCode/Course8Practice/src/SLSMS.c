#include <iso646.h>
#include <stdio.h>

#define DEVICE_COUNT 3
#define MAX_READINGS 5

// Function prototypes
void showMenu(void);

// More function prototypes will be added later.
void addReading(int readings[][MAX_READINGS], int counts[], int device,
                int value);

void displayReadings(int readings[][MAX_READINGS], const int counts[]);

void calculateStats(const int data[], int count, int *sum, double *average,
                    int *minimum, int *maximum);

int searchReadings(const int data[], int count, int target, int matches[]);

void reverse_array(int *arr, int size);

// Sort and swap
int shouldSwapAscending(int left, int right);

int shouldSwapDescending(int left, int right);

void bubbleSort(int data[], int count, int (*shouldSwap)(int, int));

int main(void) {

  // Data storage
  int readings[DEVICE_COUNT][MAX_READINGS] = {{0}};
  int counts[DEVICE_COUNT] = {0};

  int choice = 0;

  // TODO: Implement the main menu loop.
  do {

    showMenu();
    scanf("%d", &choice);

    switch (choice) {

    case 1: {

      int device;
      int value;

      printf("Enter device number (1-3): ");
      scanf("%d", &device);

      printf("Enter reading (0-100): ");
      scanf("%d", &value);

      addReading(readings, counts, device, value);
      break;
    }
    case 2:

      displayReadings(readings, counts);
      break;

    case 3: {
      int device;
      int deviceIndex;

      int sum;
      int minimum;
      int maximum;
      double average;

      printf("Please input the device number: ");
      scanf("%d", &device);
      if (device < 1 || device > DEVICE_COUNT) {

        printf("Invalid device number.\n");
        break;
      }

      deviceIndex = device - 1;

      if (counts[deviceIndex] <= 0) {

        printf("Please input data first.\n");
        break;
      }

      calculateStats(readings[deviceIndex], counts[deviceIndex], &sum, &average,
                     &minimum, &maximum);
      printf("========== DEVICE STATISTICS ==========\n");
      printf("Device: %d\n", device);
      printf("Count: %d\n", counts[deviceIndex]);
      printf("Sum: %d\n", sum);
      printf("Average: %.2f\n", average);
      printf("Minimum: %d\n", minimum);
      printf("Maximum: %d\n", maximum);
      printf("=======================================\n");

      break;
    }

    case 4: {
      int device;
      int deviceIndex;
      int target;

      int matches[MAX_READINGS];
      int matchCount;

      printf("Please input the device number: ");
      scanf("%d", &device);

      if (device < 1 || device > DEVICE_COUNT) {

        printf("Invalid device number.\n");
        break;
      }

      deviceIndex = device - 1;

      printf("Please input the search target: ");
      scanf("%d", &target);

      matchCount = searchReadings(readings[deviceIndex], counts[deviceIndex],
                                  target, matches);

      if (matchCount == 0) {

        printf("Target not found.\n");
        break;
      } else {

        printf("Match count: %d\n", matchCount);
      }

      printf("Indices:");

      for (int i = 0; i < matchCount; i++) {

        printf(" %d", matches[i]);
      }

      printf("\n");

      break;
    }

    case 5: {
      int device;
      int deviceIndex;

      printf("Please input the device number: ");
      scanf("%d", &device);

      if (device < 1 || device > DEVICE_COUNT) {

        printf("Invalid device number.\n");
        break;
      }

      deviceIndex = device - 1;
      if (counts[deviceIndex] == 0) {

        printf("No data to reverse.\n");
        break;
      }

      reverse_array(readings[deviceIndex], counts[deviceIndex]);

      printf("Readings reversed successfully.\n");

      break;
    }

    case 6: {
      int device;
      int deviceIndex;
      int order;

      printf("Please input the device number: ");
      scanf("%d", &device);

      if (device < 1 || device > DEVICE_COUNT) {

        printf("Invalid device number.\n");
        break;
      }

      deviceIndex = device - 1;
      if (counts[deviceIndex] == 0) {

        printf("No data to sort.\n");
        break;
      }

      printf("Select sorting order:\n1. Ascending\n2. Descending\n");

      scanf("%d", &order);

      if (order < 1 || order > 2) {

        printf("Invalid order.\n");
        break;
      }

      if (order == 1) {

        bubbleSort(readings[deviceIndex], counts[deviceIndex],
                   shouldSwapAscending);
      }

      if (order == 2) {

        bubbleSort(readings[deviceIndex], counts[deviceIndex],
                   shouldSwapDescending);
      }

      printf("Readings sorted successfully.\n");

      break;
    }
    case 0:

      printf("Goodbye!\n");
      break;

    default:

      printf("Invalid choice.\n");
      break;
    }
  } while (choice != 0);

  return 0;
}

// Function definitions
void showMenu(void) {

  // TODO: Print the menu.
  printf("========== SMART LAB ==========\n");
  printf("1. Add a reading\n");
  printf("2. Display all readings\n");
  printf("3. Show device statistics\n");
  printf("4. Search for a reading\n");
  printf("5. Reverse device readings\n");
  printf("6. Sort device readings\n");
  printf("0. Exit\n");
  printf("================================\n");
  printf("Enter your choice: ");
  return;
}

// More function definitions will be added later.

void addReading(int readings[][MAX_READINGS], int counts[], int device,
                int value) {

  if (device < 1 || device > DEVICE_COUNT) {

    printf("Invalid device number.\n");
    return;
  }
  if (value < 0 || value > 100) {

    printf("Invalid value.\n");
    return;
  }

  int deviceIndex = device - 1;

  if (counts[deviceIndex] >= MAX_READINGS) {

    printf("Storage is full.\n");
    return;
  }

  readings[deviceIndex][counts[deviceIndex]] = value;

  counts[deviceIndex]++;

  printf("Reading added successfully.\n");

  return;
}

void displayReadings(int readings[][MAX_READINGS], const int counts[]) {
  printf("========== DEVICE READINGS ==========\n");

  for (int i = 0; i < DEVICE_COUNT; i++) {
    printf("Device %d: ", i + 1);
    if (counts[i] == 0) {

      printf("No data.\n");
      continue;
    }

    for (int j = 0; j < counts[i]; j++) {

      printf("%d ", readings[i][j]);
    }

    printf("\n");
  }

  printf("=====================================\n");
}

void calculateStats(const int data[], int count, int *sum, double *average,
                    int *minimum, int *maximum) {

  *sum = 0;
  *minimum = data[0];
  *maximum = data[0];

  for (int i = 0; i < count; i++) {

    *sum += data[i];
    if (*minimum > data[i]) {

      *minimum = data[i];
    }

    if (*maximum < data[i]) {

      *maximum = data[i];
    }
  }

  *average = (double)*sum / count;

  return;
}

int searchReadings(const int data[], int count, int target, int matches[]) {

  int matchCount = 0;

  for (int i = 0; i < count; i++) {

    if (data[i] == target) {

      matches[matchCount] = i;
      matchCount++;
    }
  }

  return matchCount;
}

void reverse_array(int *arr, int size) {

  if (size <= 1) {
    return;
  }

  int *start = arr;
  int *end = arr + size - 1;

  while (start < end) {

    int temp = *start;

    *start = *end;

    *end = temp;

    start++;

    end--;
  }
}

int shouldSwapAscending(int left, int right) {

  if (left > right) {

    return 1;
  } else {

    return 0;
  }
}

int shouldSwapDescending(int left, int right) {

  if (left < right) {

    return 1;
  } else {

    return 0;
  }
}

void bubbleSort(int data[], int count, int (*shouldSwap)(int, int)) {

  if (count <= 1) {
    return;
  }

  for (int i = 0; i < count - 1; i++) {

    for (int j = 0; j < count - i - 1; j++) {

      if ((*shouldSwap)(data[j], data[j + 1])) {

        int temp = data[j];
        data[j] = data[j + 1];
        data[j + 1] = temp;
      }
    }
  }
}
