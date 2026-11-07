#include <stdio.h>

int isPalindrome(int n)
{
  int digits[5];
  int i = 0;
  int count = 0;
  int *left;
  int *right;

  while (n != 0)
  {

    int digit = n % 10;
    n /= 10;

    digits[count] = digit;

    count++;
  }

  left = &digits[0];
  right = &digits[count - 1];

  for (int i = 0; left < right; i++)
  {

    if (*left != *right)
    {
      return 0;
    }

    left++;
    right--;
  }

  return 1;
}

int main(void)
{
  int L;
  int R;
  int count = 0;
  int first = 1;
  scanf("%d", &L);
  scanf("%d", &R);
  printf("Palindromes:");

  // Check every number from L to R and print each palindrome
  if (L < first || R > 99999)
  {

    return 0;
  }
  for (int number = L; number <= R; number++)
  {

    if (isPalindrome(number))
    {

      printf(" %d", number);
      count++;
    }
  }

  if (count == 0)
  {

    printf(" none");
  }

  // Print "none" if no palindromes were found

  printf("\nCount: %d\n", count);
  return 0;
}
