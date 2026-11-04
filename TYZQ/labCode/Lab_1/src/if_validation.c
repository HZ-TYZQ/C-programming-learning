/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        04_if_validation.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 1 Check Point 4
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **              YOUR NAME HERE
 **
 ** DATE:        2026-10-07
 **
 ************************************************************/

#include <stdio.h>

int main(void) {
  int number;

  printf("Enter a three-digit number: ");

  int result = scanf("%d", &number);

  if (result == 0) {

    printf("Invalid input.\n");
    return 0;
  }

  if (result == EOF) {

    return 0;
  }

  if (result == 1) {
    /* TODO: Fill in the conditions for the if statements */
    if (number < 100) {
      printf("The number is too small.\n");
    } else if (number > 999) {
      printf("The number is too large.\n");
    } else {
      printf("Valid three-digit number.\n");
    }
  }

  return 0;
}
