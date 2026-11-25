/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        test_util.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 3 Exercise E Utility Test Driver
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
 * Reads one integer without a prompt and prints Number: followed by
 * its value. Displays the same parcel at each of the three priorities
 * so that Exercise E output can be checked against the sample.
 *
 * returns: 0 on completion; output must be checked manually.
 **************************************************************/
int main(void)
{
    printf("Number: %d\n", read_int());
    for (int priority = 1; priority <= 3; priority++) {
        struct Parcel parcel = {"AB1234", "Mia Chen", priority, 3};
        print_parcel(parcel);
    }
    return 0;
}
