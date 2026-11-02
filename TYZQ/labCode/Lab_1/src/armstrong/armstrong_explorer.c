/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        armstrong_explorer.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 1 Exercise C
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **              YOUR NAME HERE
 **
 ** DATE:        2026-10-07
 **
 ************************************************************/

#include <stdio.h>

#include "armstrong.h"

int main(void) {
  printf("=== Armstrong Number Explorer ===\n");

  /* Declare the upper limit, current number, and result counter. */
  int upper_limit;
  int number;
  int count = 0;

  /* TODO: Print "Enter a three-digit upper limit: " and read the input. */
  printf("Enter a three-digit upper limit: ");
  scanf("%d", &number);

  /*
   * TODO: Reject invalid input.
   * Error message: "Invalid input: enter a number from 100 to 999."
   * Repeat the input prompt and read another value inside the loop.
   * Assign the valid input value to upper_limit.
   */

  while (number < 100 || number > 999) {
    printf("Invalid input: enter a number from 100 to 999.\n");
    printf("Enter a three-digit upper limit: ");
    scanf("%d", &number);
  }

  upper_limit = number;

  /* TODO: Print "Armstrong numbers from 100 to <upper limit>:". */
  printf("\nArmstrong numbers from 100 to %d:\n", upper_limit);

  /*
   * TODO: Search from 100 through the upper limit.
   * Call is_armstrong_number, print each match, and update the counter.
   */

  for (number = 100; number <= upper_limit; number++) {

    if (is_armstrong_number(number)) {
      printf("%d\n", number);
      count++;
    }
  }

  /* TODO: If the counter is zero, print "No Armstrong numbers were found." */
  if (count == 0) {
    printf("No Armstrong numbers were found.\n");
  }

  /* TODO: Print "Total found: <count>" and finish the program. */
  printf("Total found: %d\n", count);
  return 0;
}
