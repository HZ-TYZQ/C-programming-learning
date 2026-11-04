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
  int input;
  int ch;

  while (1) {

    printf("Enter a three-digit number: ");

    int result = scanf("%d", &input);

    if (result == 0) {

      printf("Invalid input.\n");

      while ((ch = getchar()) != '\n' && ch != EOF) {
      }

      if (ch == EOF) {

        break;
      }

      continue;
    }

    else if (result == 1) {

      if (input >= 100 && input <= 999) {

        printf("The number is valid!\n");
        number = input;
      }

      else {

        printf("The number should be between 100-999.\n");
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        if (ch == EOF) {

          break;
        }

        continue;
      }

      break;
    }

    else {

      break;
    }
  }

  return 0;
}
