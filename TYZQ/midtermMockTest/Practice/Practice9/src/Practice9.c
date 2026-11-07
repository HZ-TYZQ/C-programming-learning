#include <stdio.h>
#define MAX_SEATS 100

int can_book(const int seats[], int n, int start, int k)
{
  // Return 1 if the seats can be booked; otherwise return 0
  if (start < 0 || start + k > n)
  {
    return 0;
  }

  for (int i = start; i < start + k; i++)
  {
    if (seats[i] != 0)
    {
      return 0;
    }
  }
  return 1;
}

int main(void)
{
  int n, k, start, first;
  int seats[MAX_SEATS];
  // Read the input
  scanf("%d %d", &n, &k);

  for (int i = 0; i < n; i++)
  {
    scanf("%d", &seats[i]);
  }

  start = -1;

  for (int i = 0; i <= n - k; i++)
  {
    if (can_book(seats, n, i, k))
    {
      start = i;
      break;
    }
  }

  if (start == -1)
  {
    printf("Unavailable\n");
    return 0;
  }

  for (int i = start; i < start + k; i++)
  {
    seats[i] = 1;
  }

  // Find and book adjacent seats
  // Print the result
  printf("%d\n", start + 1);

  for (int i = 0; i < n; i++)
  {
    if (i == 0)
    {
      printf("%d", seats[i]);
    }
    else
    {
      printf(" %d", seats[i]);
    }
  }

  printf("\n");
  return 0;
}
