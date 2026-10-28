/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        05_switch_menu.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 1 Check Point 5
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
  char choice;

  printf("Enter your choice: ");
  scanf(" %c", &choice);

  /* TODO: Fill in the blanks in the switch statement */
  switch (choice) {
  case 'A':
    printf("Analyse digits\n");
    break;

  case 'C':
    printf("Check Armstrong number\n");
    break;

  default:
    printf("Unknown choice\n");
  }

  return 0;
}
