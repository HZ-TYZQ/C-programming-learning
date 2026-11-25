/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        test_read_line.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 3 Exercise A Line Input Test Driver
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **
 ** DATE:        2026-11-02
 **
 ************************************************************/

#include <stdio.h>
#include "util.h"

/**************************************************************
 * Function: main
 * Reads two lines without prompts into arrays of sizes 8 and 40.
 * Prints them as First: [text] and Next: [text] for manual checking.
 * Prints a failure message if either line cannot be read.
 *
 * returns: 0 if both reads succeed, or 1 if either read fails.
 **************************************************************/
int main(void)
{
    char first[8];
    char next[40];

    if (!read_line(first, sizeof first)) {
        puts("FAIL: first line could not be read");
        return 1;
    }
    printf("First: [%s]\n", first);
    if (!read_line(next, sizeof next)) {
        puts("FAIL: next line could not be read");
        return 1;
    }
    printf("Next: [%s]\n", next);
    return 0;
}
