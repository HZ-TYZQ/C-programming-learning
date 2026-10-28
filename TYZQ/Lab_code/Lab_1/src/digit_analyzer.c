/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        digit_analyzer.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 1 Exercise A
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **              YOUR NAME HERE(I'm Iron MAN!)
 **
 ** DATE:        2026-10-07
 **
 ************************************************************/

#include <stdio.h>

int main(void) {
  int number;
  int hundreds;
  int tens;
  int ones;
  int digit_sum;
  int digit_product;
  int reversed;
  double average;

  printf("Enter a three-digit number: ");
  scanf("%d", &number);

  /*
   * TODO: Calculate the hundreds, tens, and ones digits, their sum and
   * product, the reversed number, and the average digit value.
   * Use the supplied variables; choose your own calculation steps.
   */
  hundreds = number / 100;
  tens = (number / 10) % 10;
  ones = number % 10;
  digit_sum = hundreds + tens + ones;
  digit_product = hundreds * tens * ones;
  reversed = ones * 100 + tens * 10 + hundreds * 1;
  average = digit_sum / 3.0;

  printf("Hundreds digit: %d\n", hundreds);
  printf("Tens digit: %d\n", tens);
  printf("Ones digit: %d\n", ones);
  printf("Sum of digits: %d\n", digit_sum);
  printf("Product of digits: %d\n", digit_product);
  printf("Reversed number: %d\n", reversed);
  printf("Average digit value: %.2f\n", average);

  return 0;
}
