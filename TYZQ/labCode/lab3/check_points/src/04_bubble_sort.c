/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        04_bubble_sort.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 3 Check Point 4 Integer Bubble Sort
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **              YOUR NAME HERE
 **
 ** DATE:        2026-11-03
 **
 ************************************************************/

#include <stdio.h>

/**************************************************************
 * Function: main
 * Provides the loop structure for sorting a one-dimensional integer
 * array in ascending order. Prints the array after each pass so that
 * the completed comparison and swap can be checked. No input is needed.
 *
 * returns: 0 on completion.
 **************************************************************/
int main(void)
{
  int values[5] = {3, -1, 3, 0, 2};
  const int count = 5;

  for (int pass = 0; pass < count - 1; pass++)
  {
    for (int j = 0; j < count - 1 - pass; j++)
    {
      if (values[j] > values[j + 1])
      {
        int temp = values[j];
        values[j] = values[j + 1];
        values[j + 1] = temp;
      }
    }

    /* Supplied observation output: inspect the array after each pass. */
    printf("Pass %d:", pass + 1);
    for (int i = 0; i < count; i++)
    {
      printf(" %d", values[i]);
    }
    putchar('\n');
  }

  return 0;
}
