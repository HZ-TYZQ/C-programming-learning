#include <stdio.h>

int main()
{
  char *f_name = "sample_w.txt";
  FILE *file = fopen(f_name, "w");

  fprintf(file, "%d %d %d\n", 2024, 12, 16);
  fprintf(file, "@ 45!\n");
  fprintf(file, "IP1005\n%f", 89.99);

  fclose(file);
  return 0;
}
