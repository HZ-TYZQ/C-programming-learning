#include <stdio.h>

int image[2][3] = {{10, 20, 30}, {40, 50, 60}};

int main(void)
{
  for (int r = 0; r < 2; r++)
  {
    for (int c = 0; c < 3; c++)
    {
      if (c == 0)
      {
        printf("%d", image[r][c]);
      }
      else
      {
        printf(" %d", image[r][c]);
      }
    }
    printf("\n");
  }
}
