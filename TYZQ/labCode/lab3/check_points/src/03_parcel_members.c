/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        03_parcel_members.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 3 Check Point 3
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **              YOUR NAME HERE
 **
 ** DATE:        2026-10-09
 **
 ************************************************************/

#include "../parcel.h"
#include <stdio.h>

/**************************************************************
 * Function: main
 * Provides records for practising member access and copying a complete
 * structure. Displays selected fields for checking; no input is needed.
 *
 * returns: 0 on completion.
 **************************************************************/
int main(void)
{
  struct Parcel parcels[3] = {
    {"AB1234", "Mia Chen", 2, 3},
    {"ZX9000", "Leo Wang", 3, 2},
    {"", "", 0, 0}};
  for (int i = 0; i < 2; i++)
  {
    /* TODO: Replace the two member names to print code and priority. */
    printf("%s: %d\n", parcels[i].code, parcels[i].priority);
  }
  /* TODO: Copy one entire record into parcels[2], then inspect it. */
  parcels[2] = parcels[0];
  printf("Copied record: %s, priority %d\n", parcels[2].code, parcels[2].priority);
  return 0;
}
