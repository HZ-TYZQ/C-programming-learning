#include <stdio.h>

int isValidNumerator(int num)
{

  if (num < -100 || num > 100)
  {

    return 0;
  }
  return 1;
}

int isValidDenominator(int num)
{

  if (num < 0 || num > 100)
  {

    return 0;
  }
  return 1;
}

int main(void)
{

  int numerator1;
  int denominator1;
  int numerator2;
  int denominator2;
  char operator;
  int resultNumerator;
  int resultDenominator;

  scanf("%d %d %c %d %d", &numerator1, &denominator1, &operator, &numerator2,
        &denominator2);

  if (isValidNumerator(numerator1) && isValidDenominator(denominator1) &&
      isValidNumerator(numerator2) && isValidDenominator(denominator2) &&
      denominator1 != 0 && denominator2 != 0)
  {

    if (operator == '+')
    {

      resultNumerator = numerator1 * denominator2 + numerator2 * denominator1;
      resultDenominator = denominator1 * denominator2;
    }

    else if (operator == '-')
    {

      resultNumerator = numerator1 * denominator2 - numerator2 * denominator1;
      resultDenominator = denominator1 * denominator2;
    }

    else if (operator == '*')
    {

      resultNumerator = numerator1 * numerator2;
      resultDenominator = denominator1 * denominator2;
    }

    else if (operator == '/' && numerator2 != 0)
    {

      resultNumerator = numerator1 * denominator2;
      resultDenominator = denominator1 * numerator2;
    }
    else if (operator == '/' && numerator2 == 0)
    {

      printf("Error: Division by zero.\n");
      return 0;
    }
  }
  else
  {

    printf("Error: Invalid fraction.\n");
    return 0;
  }
  if (resultDenominator < 0)
  {

    resultDenominator = -resultDenominator;
    resultNumerator = -resultNumerator;
  }

  printf("%d/%d\n", resultNumerator, resultDenominator);

  return 0;
}
