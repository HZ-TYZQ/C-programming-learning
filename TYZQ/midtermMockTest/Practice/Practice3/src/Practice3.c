#include <stdio.h>

int main(void)
{

  int currentModeCode = 0;
  double brghtness = 0;

  scanf("%lf %d", &brghtness, &currentModeCode);

  if (brghtness < 30.0)
  {

    currentModeCode = 1;
  }
  if (brghtness > 70.0)
  {

    currentModeCode = 0;
  }

  char *mode = (currentModeCode == 1) ? "DARK" : "LIGHT";

  printf("Mode: %s\n", mode);

  return 0;
}
