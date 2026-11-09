/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        main.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 2 Exercise E Application
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **              YOUR NAME HERE
 **
 ** DATE:        2026-10-22
 **
 ************************************************************/

#include "image.h"
#include <stdio.h>

/**************************************************************
 * Function: main
 * The main function for the image processing application.
 * returns: 0 on successful completion.
 **************************************************************/
int main(void)
{
  // YOUR CODE HERE
  int size;
  int change;
  int direction;
  int image1[MAX_SIZE][MAX_SIZE];
  int image2[MAX_SIZE][MAX_SIZE];

  if (scanf("%d %d %d", &size, &change, &direction) != 3 || size < 1 ||
      size > 20 || change < -255 || change > 255 ||
      (direction != 1 && direction != -1))
  {
    printf("Invalid image input.\n");
    return 0;
  }

  for (int row = 0; row < size; row++)
  {
    for (int col = 0; col < size; col++)
    {
      if (scanf("%d", &image1[row][col]) != 1 || image1[row][col] < 0 ||
          image1[row][col] > 255)
      {
        printf("Invalid image input.\n");
        return 0;
      }
    }
  }

  for (int row = 0; row < size; row++)
  {
    for (int col = 0; col < size; col++)
    {
      if (scanf("%d", &image2[row][col]) != 1 || image2[row][col] < 0 ||
          image2[row][col] > 255)
      {
        printf("Invalid image input.\n");
        return 0;
      }
    }
  }

  int blended[MAX_SIZE][MAX_SIZE];
  int brightened[MAX_SIZE][MAX_SIZE];
  int rotated[MAX_SIZE][MAX_SIZE];

  blend_images(image1, image2, blended, size, size);
  adjust_brightness(blended, brightened, size, size, change);
  if (direction == 1)
  {
    rotate_clockwise(brightened, rotated, size);
  }
  else if (direction == -1)
  {
    rotate_counterclockwise(brightened, rotated, size);
  }

  print_image(rotated, size, size);
  return 0;
}
