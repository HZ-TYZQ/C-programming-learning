/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        sorting.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 3 Exercise D Dispatch Sort
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
 * Function: compare_parcel
 * Checks whether two records are out of dispatch order: higher priority
 * first, then earlier arrival, then lexicographically smaller code.
 *
 * input:
 *     first: The first record to compare; it must not be modified.
 *     second: The second record to compare; it must not be modified.
 *
 * returns: 1 if first belongs after second, or 0 otherwise,
 *          including when all three ordering keys are equal.
 **************************************************************/
int compare_parcel(struct Parcel first, struct Parcel second)
{
  /* TODO: Return 1 exactly when first belongs after second.
     Compare priority descending, arrival order ascending, then code
     lexicographically ascending. Return 0 otherwise. */
  if (first.priority != second.priority)
  {
    return first.priority < second.priority;
  }
  if (first.arrival_order != second.arrival_order)
  {
    return first.arrival_order > second.arrival_order;
  }
  if (strcmp(first.code, second.code) > 0)
  {
    return 1;
  }

  return 0;
}

/**************************************************************
 * Function: sort_parcels
 * Sorts the active records in dispatch order using Bubble Sort.
 * Moves complete records so that all fields stay together.
 *
 * input:
 *     parcels: The writable array to sort in place.
 *     count: The number of active records, from 0 to MAX_PARCELS.
 *            Records outside this range must remain unchanged.
 *
 * returns: void
 **************************************************************/
void sort_parcels(struct Parcel parcels[], int count)
{
  /* TODO: Bubble Sort the active records in place. Compare adjacent
     records with compare_parcel and swap entire structures. */
  for (int i = 0; i < count - 1; i++)
  {
    for (int j = 0; j < count - i - 1; j++)
    {
      if (compare_parcel(parcels[j], parcels[j + 1]))
      {
        struct Parcel temp = parcels[j];
        parcels[j] = parcels[j + 1];
        parcels[j + 1] = temp;
      }
    }
  }
}
