/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        print_image.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 2 Exercise A Image Output Function
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **              YOUR NAME HERE
 **
 ** DATE:        2026-10-08
 **
 ************************************************************/

#include "image.h"
#include <stdio.h>

/**************************************************************
 * Function: print_image
 * Prints a 2D array of integers as an image to the console.
 *
 * image: A 2D array of integers representing the image.
 * rows: The number of rows in the image.
 * cols: The number of columns in the image.
 *
 * Output: Print active pixels in row order with one space between adjacent
 * values, no leading or trailing spaces, and one newline after every row,
 * including the last. Print no prompts or headings.
 *
 * returns: void
 **************************************************************/
void print_image(const int image[][MAX_SIZE], int rows, int cols)
{
  // YOUR CODE HERE

  for (int r = 0; r < rows; r++)
  {
    for (int c = 0; c < cols; c++)
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
