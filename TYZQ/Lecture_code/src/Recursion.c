#include <stdio.h>

void test(int n)
{
  if (n == 0)
  {
    return;
  }

  printf("%d ", n);

  test(n - 1);

  printf("%d ", n);
}

int main(void)
{
  test(3);

  return 0;
}
