#include <stdio.h>
#include <threads.h>

int main(void)
{

  int password;
  scanf("%d", &password);

  int number = password;
  int digit;
  int count = 1;

  if (number == 0)
  {
    count = 0;
  }
  else
  {
    int preDigit = -1;
    int repeatCount = 1;

    while (number != 0)
    {

      digit = number % 10;
      number /= 10;

      if (digit == preDigit)
      {
        repeatCount++;

        if (repeatCount > count)
        {
          count = repeatCount;
        }
      }
      else
      {
        repeatCount = 1;
      }
      preDigit = digit;
    }
  }

  printf("%d\n", count);
}
