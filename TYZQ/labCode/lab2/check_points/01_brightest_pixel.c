/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        01_brightest_pixel.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 2 Check Point 1
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **              YOUR NAME HERE
 **
 ** DATE:        2026-10-08
 **
 ************************************************************/

#include <stdio.h>

int main(void)
{
  int pixels[5] = {40, 210, 80, 255, 120};
  int brightest = pixels[0];
  int brightest_index = 0;

  /* TODO: Traverse the array once. When a brighter pixel is found,
     update both brightest and brightest_index. If the maximum occurs
     more than once, keep its first index. */
  for (int i = 0; i < 5; i++)
  {
    if (pixels[i] > brightest)
    {
      brightest = pixels[i];
      brightest_index = i;
    }
  }

  printf("Brightest value: %d\n", brightest);
  printf("Index: %d\n", brightest_index);
  return 0;
}
