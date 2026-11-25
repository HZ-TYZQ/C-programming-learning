/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        tracking.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 3 Exercise B Tracking Codes
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **              YOUR NAME HERE
 **
 ** DATE:        2026-10-09
 **
 ************************************************************/

#include "parcel.h"
#include <ctype.h>
#include <string.h>

/**************************************************************
 * Function: normalize_tracking_code
 * Validates a tracking code and uppercases its two letters if valid.
 * A valid code contains exactly two letters followed by four digits.
 *
 * input:
 *     code: A writable, null-terminated string with no newline.
 *           Invalid strings must remain unchanged.
 *
 * returns: 1 for a valid code, or 0 for an invalid code.
 **************************************************************/
int normalize_tracking_code(char code[])
{
  /* TODO: A valid code is exactly two letters followed by four digits.
     Check its length before indexing; do not change an invalid string.
     Uppercase the letters only after every position has been checked.
     Return 1 on success and 0 otherwise. Do not print anything. */

  size_t length = strlen(code);
  if (length != 6)
  {
    return 0;
  }
  else if (!isalpha((unsigned char)code[0]) || !isalpha((unsigned char)code[1]))
  {
    return 0;
  }

  for (int i = 2; i < 6; i++)
  {
    if (!isdigit((unsigned char)code[i]))
    {
      return 0;
    }
  }

  code[0] = toupper((unsigned char)code[0]);
  code[1] = toupper((unsigned char)code[1]);

  return 1;
}
