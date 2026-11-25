/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        test_tracking.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 3 Exercise B Local Tests
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **
 ** DATE:        2026-10-09
 **
 ************************************************************/

#include <stdio.h>
#include <string.h>
#include "parcel.h"

/**************************************************************
 * Function: check
 * Tests both the return value and the resulting tracking-code string.
 *
 * name: The case label used in a failure message.
 * input: The original string to copy into a writable test array.
 * expected_result: The expected validation flag, 1 or 0.
 * expected_code: The expected string after validation and normalisation.
 *
 * returns: 1 if both results match, or 0 with a diagnostic otherwise.
 **************************************************************/
static int check(const char *name, const char *input, int expected_result,
                 const char *expected_code)
{
    char code[32];
    strcpy(code, input);
    int result = normalize_tracking_code(code);
    if (result != expected_result || strcmp(code, expected_code) != 0) {
        printf("FAIL %s: returned %d, code [%s]\n", name, result, code);
        return 0;
    }
    return 1;
}

/**************************************************************
 * Function: main
 * Runs the supplied Exercise B cases without keyboard input.
 * Prints PASS Exercise B if all cases pass, or failure diagnostics.
 *
 * returns: 0 if all cases pass, or 1 if any case fails.
 **************************************************************/
int main(void)
{
    int passed = 1;
    passed &= check("lowercase", "ab1234", 1, "AB1234");
    passed &= check("mixed case", "aB1234", 1, "AB1234");
    passed &= check("lowercase second letter", "Ab1234", 1, "AB1234");
    passed &= check("uppercase", "ZX9000", 1, "ZX9000");
    passed &= check("empty", "", 0, "");
    passed &= check("short", "AB123", 0, "AB123");
    passed &= check("long", "AB12345", 0, "AB12345");
    passed &= check("wrong letter", "1B1234", 0, "1B1234");
    passed &= check("wrong digit", "ab12X4", 0, "ab12X4");
    passed &= check("space", "AB 234", 0, "AB 234");
    for (int i = 0; i < 6; i++) {
        char invalid[] = "ab1234";
        char name[40];
        invalid[i] = i < 2 ? '1' : 'X';
        snprintf(name, sizeof name, "invalid character at position %d", i);
        passed &= check(name, invalid, 0, invalid);
    }
    if (passed) {
        puts("PASS Exercise B");
    }
    return !passed;
}
