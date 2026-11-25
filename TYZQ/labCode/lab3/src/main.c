/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        main.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 3 Exercise F Organizer
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **              YOUR NAME HERE
 **
 ** DATE:        2026-10-09
 **
 ************************************************************/

#include "parcel.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

/**************************************************************
 * Function: main
 * Runs the parcel organizer without input prompts. Reads the parcel
 * count, the records and a search code; displays the search result
 * and then all records in dispatch order, reusing Exercises A--E.
 *
 * input: No parameters. Read from standard input without prompts:
 *     a parcel count (1--MAX_PARCELS), then four lines per parcel:
 *     tracking code, recipient name, priority (1--3), and arrival order.
 *     Read the search code last. Names may contain spaces and fit the
 *     recipient array; numeric input is valid.
 *
 * output: On a match, print "Search result:" on one line and the matching
 *     record on the next. Otherwise print "Search result: NOT FOUND".
 *     Then print "Dispatch order:" and each sorted record on its own line.
 *     Use print_parcel for records: CODE | Recipient | PRIORITY_LABEL | arrival N
 *     with one space around each | and after arrival. Every line ends
 *     with a newline. Print no other labels or prompts.
 *     An out-of-range count prints "Invalid parcel count." and exits.
 *     An invalid parcel code prints "Invalid tracking code." and exits.
 *     An invalid search code prints "Invalid search code." and exits.
 *
 * returns: 0 on successful completion, or 1 for invalid input.
 **************************************************************/
int main(void)
{
  /* TODO: Write the complete main function body using the Exercise F
     requirements and flowchart. Reuse your functions from Exercises A--E. */
  struct Parcel parcels[MAX_PARCELS];
  char buf[INPUT_CAPACITY];
  int count;

  count = read_int();
  if (count < 1 || count > MAX_PARCELS)
  {
    printf("Invalid parcel count.\n");
    return 1;
  }

  for (int i = 0; i < count; i++)
  {
    if (!read_line(buf, sizeof(buf)) || !normalize_tracking_code(buf))
    {
      printf("Invalid tracking code.\n");
      return 1;
    }

    strcpy(parcels[i].code, buf);
    read_line(parcels[i].recipient, sizeof(parcels[i].recipient));
    parcels[i].priority = read_int();
    parcels[i].arrival_order = read_int();
  }

  if (!read_line(buf, sizeof(buf)) || !normalize_tracking_code(buf))
  {
    printf("Invalid search code.\n");
    return 1;
  }

  int index = find_parcel(parcels, count, buf);

  if (index == -1)
  {
    printf("Search result: NOT FOUND\n");
  }
  else
  {
    printf("Search result:\n");
    print_parcel(parcels[index]);
  }

  sort_parcels(parcels, count);
  printf("Dispatch order:\n");

  for (int i = 0; i < count; i++)
  {
    print_parcel(parcels[i]);
  }

  return 0;
}
