/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        armstrong_checker.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 1 Exercise B
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **              YOUR NAME HERE
 **
 ** DATE:        2026-10-07
 **
 ************************************************************/

#include "armstrong.h"

int is_armstrong_number(int number) {
  /*
   * TODO: Extract each digit and calculate the sum of their cubes.
   * Return a non-zero value for an Armstrong number and zero otherwise
   */
  int hundreds = number / 100;
  int tens = (number / 10) % 10;
  int ones = number % 10;

  int cube_sum =
      hundreds * hundreds * hundreds + tens * tens * tens + ones * ones * ones;

  return cube_sum == number;
}
