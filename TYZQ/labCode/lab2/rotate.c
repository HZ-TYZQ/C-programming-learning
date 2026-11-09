/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        rotate.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 2 Exercise D Rotation
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **              YOUR NAME HERE
 **
 ** DATE:        2026-10-08
 **
 ************************************************************/

#include "image.h"

/**************************************************************
 * Function: rotate_clockwise
 * Rotates an image 90 degrees clockwise.
 *
 * input: The input image.
 * output: The rotated image.
 * n: The size of the square image.
 *
 * returns: void
 **************************************************************/
void rotate_clockwise(const int input[][MAX_SIZE], int output[][MAX_SIZE],
                      int n)
{
  // YOUR CODE HERE
  for (int row = 0; row < n; row++)
  {
    for (int col = 0; col < n; col++)
    {
      output[row][col] = input[n - col - 1][row];
    }
  }
}

/**************************************************************
 * Function: rotate_counterclockwise
 * Rotates an image 90 degrees counterclockwise.
 *
 * input: The input image.
 * output: The rotated image.
 * n: The size of the square image.
 *
 * returns: void
 **************************************************************/
void rotate_counterclockwise(const int input[][MAX_SIZE],
                             int output[][MAX_SIZE], int n)
{
  // YOUR CODE HERE

  for (int row = 0; row < n; row++)
  {
    for (int col = 0; col < n; col++)
    {
      output[row][col] = input[col][n - row - 1];
    }
  }
}
