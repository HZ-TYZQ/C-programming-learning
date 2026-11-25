/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        util.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 3 Exercises A and E Input and Output Utilities
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **              YOUR NAME HERE
 **
 ** DATE:        2026-11-02
 **
 ************************************************************/

#include "util.h"
#include "parcel.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static const char PRIORITY_LABELS[3][10] = {"STANDARD", "PRIORITY", "URGENT"};

/**************************************************************
 * Function: read_line
 * Reads one line from standard input without printing a prompt.
 * Removes the newline and discards any part that does not fit.
 *
 * input:
 *     text: The writable array receiving the null-terminated string.
 *     capacity: The total array size, including the terminator; at least 2.
 *
 * returns: 1 if a line is read, including a blank line or text ending at EOF;
 *          0 if fgets fails, including EOF before any input.
 **************************************************************/
int read_line(char text[], int capacity)
{
  if (fgets(text, capacity, stdin) == NULL)
  {
    return 0;
  }

  size_t length = strlen(text);
  int index = (int)length - 1;

  if (length > 0 && text[index] == '\n')
  {
    text[index] = '\0';
  }
  else
  {
    int ch;
    while ((ch = getchar()) != EOF && ch != '\n')
    {
    }
  }

  return 1;
}

/**************************************************************
 * Function: read_int
 * Reads one line and converts it to an integer without printing a prompt.
 *
 * input: None (reads from standard input).
 *
 * returns: The integer read, or 0 if reading or conversion fails.
 **************************************************************/
int read_int(void)
{
  /* Exercise E TODO: Use read_line with a local INPUT_CAPACITY-character array.
     Parse one integer with sscanf. Return it on success, or 0 if reading
     or conversion fails. Inputs in the organizer are valid integers.
     Do not print a prompt or a message. */
  char buf[INPUT_CAPACITY];
  int value;

  if (!read_line(buf, sizeof(buf)))
  {
    return 0;
  }

  if (sscanf(buf, "%d", &value) != 1)
  {
    return 0;
  }

  return value;
}

/**************************************************************
 * Function: print_parcel
 * Prints one parcel as CODE | Recipient | PRIORITY_LABEL | arrival N,
 * followed by a newline and without a prompt.
 *
 * input:
 *     parcel: The record to display; its priority must be in the range 1--3.
 *
 * returns: void
 **************************************************************/
void print_parcel(struct Parcel parcel)
{
  /* Exercise E TODO: Print one record, without a prompt, in this exact order:
     CODE | Recipient | PRIORITY_LABEL | arrival N
     Use one space on each side of every | and one space after arrival.
     End with one newline. N is the decimal arrival_order value.
     Map priority 1, 2, 3 to PRIORITY_LABELS entries 0, 1, 2.
     Assume priority is valid. */
  printf(
    "%s | %s | %s | arrival %d\n",
    parcel.code,
    parcel.recipient,
    PRIORITY_LABELS[parcel.priority - 1],
    parcel.arrival_order);
}
