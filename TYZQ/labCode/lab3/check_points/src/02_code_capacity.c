/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        02_code_capacity.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 3 Check Point 2
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **              YOUR NAME HERE
 **
 ** DATE:        2026-10-09
 **
 ************************************************************/

#include <stdio.h>
#include <string.h>

#define CODE_ROOM 7 /* TODO: replace with the minimum safe capacity. */

/**************************************************************
 * Function: main
 * Displays a string's visible length, array capacity and terminator
 * byte to help check the chosen CODE_ROOM value. No input is needed.
 *
 * returns: 0 if the array contains a terminated string, or 1 otherwise.
 **************************************************************/
int main(void)
{
  char code[CODE_ROOM] = "ab1234";
  /* Supplied check: never call strlen on an unterminated array. */
  size_t length = 0;
  while (length < sizeof code && code[length] != '\0')
  {
    length++;
  }
  if (length == sizeof code)
  {
    puts("No terminator within the array. Increase CODE_ROOM.");
    return 1;
  }

  printf("Visible length: %zu\n", strlen(code));
  printf("Array capacity: %zu\n", sizeof code);
  printf("Terminator byte: %d\n", (int)code[strlen(code)]);
  return 0;
}
