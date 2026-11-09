/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        brightness.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 2 Exercise C
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
 * Function: adjust_brightness
 * Adjusts the brightness of an image.
 *
 * input: The input image.
 * output: The adjusted image.
 * rows: The number of rows in the image.
 * cols: The number of columns in the image.
 * change: The amount to change the brightness by.
 *
 * returns: void
 **************************************************************/
void adjust_brightness(const int input[][MAX_SIZE], int output[][MAX_SIZE],
                       int rows, int cols, int change)
{
  // YOUR CODE HERE
  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      if (input[row][col] + change > 255)
      {
        output[row][col] = 255;
      }
      else if (input[row][col] + change < 0)
      {
        output[row][col] = 0;
      }
      else
      {
        output[row][col] = input[row][col] + change;
      }
    }
  }
}
