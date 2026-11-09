/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        image_blend.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 2 Exercise B
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
 * Function: blend_images
 * Blends two images by averaging their pixel values.
 *
 * image1: The first image.
 * image2: The second image.
 * output: The blended image.
 * rows: The number of rows in the images.
 * cols: The number of columns in the images.
 *
 * returns: void
 **************************************************************/
void blend_images(const int image1[][MAX_SIZE], const int image2[][MAX_SIZE],
                  int output[][MAX_SIZE], int rows, int cols)
{
  // YOUR CODE HERE
  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      output[row][col] = (image1[row][col] + image2[row][col]) / 2;
    }
  }
}
