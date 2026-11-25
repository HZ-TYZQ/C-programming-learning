/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        parcel.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 3 Exercise C Parcel Search
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **              YOUR NAME HERE
 **
 ** DATE:        2026-10-09
 **
 ************************************************************/

#include "parcel.h"
#include <string.h>

/**************************************************************
 * Function: find_parcel
 * Finds the first active parcel whose tracking code equals the target.
 * Does not modify the records or the target string.
 *
 * input:
 *     parcels: The array of records with already normalised tracking codes.
 *     count: The number of active records to search, from 0 to MAX_PARCELS.
 *     target: The null-terminated, already normalised code to find.
 *
 * returns: The zero-based index of the first match, or -1 if absent.
 **************************************************************/
int find_parcel(const struct Parcel parcels[], int count, const char targetp[])
{
  /* TODO: Return the index of the first code equal to target, or -1
     when absent. Search only the first count records; do not modify them. */

  for (int i = 0; i < count; i++)
  {
    if (!strcmp(parcels[i].code, targetp))
    {
      return i;
    }
  }

  return -1;
}
