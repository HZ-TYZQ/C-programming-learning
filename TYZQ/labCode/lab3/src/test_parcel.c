/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        test_parcel.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 3 Exercise C Local Tests
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **
 ** DATE:        2026-10-09
 **
 ************************************************************/

#include <stdio.h>
#include "parcel.h"

/**************************************************************
 * Function: check
 * Checks one search case and prints a diagnostic if its result differs.
 *
 * name: The case label used in a failure message.
 * parcels: The records passed to find_parcel.
 * count: The number of active records to search.
 * target: The normalised tracking code to find.
 * expected: The expected index, or -1 when the code is absent.
 *
 * returns: 1 if the case passes, or 0 if it fails.
 **************************************************************/
static int check(const char *name, const struct Parcel parcels[], int count,
                 const char *target, int expected)
{
    int actual = find_parcel(parcels, count, target);
    if (actual != expected) {
        printf("FAIL %s: expected %d, got %d\n", name, expected, actual);
        return 0;
    }
    return 1;
}

/**************************************************************
 * Function: main
 * Runs the supplied Exercise C search cases without keyboard input.
 * Prints PASS Exercise C if all cases pass, or failure diagnostics.
 *
 * returns: 0 if all cases pass, or 1 if any case fails.
 **************************************************************/
int main(void)
{
    const struct Parcel parcels[] = {
        {"AB1234", "Mia Chen", 2, 3},
        {"AB1234", "Iya Li", 3, 2},
        {"CD5678", "Ava Patel", 2, 1}
    };
    int passed = 1;
    passed &= check("empty", parcels, 0, "AB1234", -1);
    passed &= check("first occurrence", parcels, 3, "AB1234", 0);
    passed &= check("last", parcels, 3, "CD5678", 2);
    passed &= check("absent", parcels, 3, "ZX9000", -1);
    passed &= check("active count", parcels, 1, "CD5678", -1);
    if (passed) {
        puts("PASS Exercise C");
    }
    return !passed;
}
