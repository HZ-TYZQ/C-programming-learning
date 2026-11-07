#include <stdio.h>

int main(void)
{

  int a, b, c, d = 0;
  scanf("%d %d %d %d", &a, &b, &c, &d);

  int total = a + b + c + d;
  float avg = (float)total / 4;

  printf("%d\n%.2f\n", total, avg);

  return 0;
}
