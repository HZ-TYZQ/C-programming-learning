#include <stdio.h>

int main(void)
{

  int paper;
  int jobs;
  int pagesPerCopy;
  int copies;
  int required;
  int completed = 0;

  scanf("%d %d", &paper, &jobs);

  if (paper < 0 || paper > 10000 || jobs < 0 || jobs > 100)
  {

    return 0;
    ;
  }

  for (int i = 0; i < jobs; i++)
  {

    scanf("%d %d", &pagesPerCopy, &copies);

    required = pagesPerCopy * copies;

    if (required > paper)
    {

      continue;
    }
    else
    {

      paper -= required;
      completed++;
    }
  }

  printf("Completed jobs: %d\n", completed);
  printf("Remaining paper: %d\n", paper);
}
