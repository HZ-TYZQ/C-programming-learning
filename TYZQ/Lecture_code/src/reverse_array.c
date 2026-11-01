

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
