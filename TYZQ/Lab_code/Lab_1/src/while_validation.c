/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        06_while_validation.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 1 Check Point 6
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
  scanf("%d", &number);

  while (number < 100 || number > 999) {
    printf("Invalid input. Try again: ");
    scanf("%d", &number);
  }

  return 0;
}
