#include <stdio.h>
#define MAX_READINGS 100

double average_three(double left, double current, double right)
{
  // Return the average of the three values
  return (left + current + right) / 3;
}

int main(void)
{
  int n;
  double readings[MAX_READINGS], smoothed[MAX_READINGS];
  // Read the input
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {

    scanf("%lf", &readings[i]);
  }
  // Smooth the readings
  for (int i = 0; i < n; i++)
  {

    if (i == 0 && n > 1)
    {

      smoothed[i] = (readings[i] + readings[i + 1]) / 2;
    }
    else if (i > 0 && i < n - 1 && n > 2)
    {

      smoothed[i] =
          average_three(readings[i - 1], readings[i], readings[i + 1]);
    }
    else if (i == n - 1 && n > 1)
    {

      smoothed[i] = (readings[i - 1] + readings[i]) / 2;
    }
    else if (n == 1)
    {
      smoothed[i] = readings[i];
    }
  }

  // Print the results
  for (int i = 0; i < n; i++)
  {

    if (i == 0)
    {
      printf("%.2f", smoothed[i]);
    }
    else
    {
      printf(" %.2f", smoothed[i]);
    }
  }
  printf("\n");
  return 0;
}
