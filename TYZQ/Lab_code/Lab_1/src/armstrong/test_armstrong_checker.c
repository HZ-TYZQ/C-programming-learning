 /************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        test_armstrong_checker.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 1 Exercise B Unit Test
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **
 ** DATE:        2026-10-07
 **
 ************************************************************/

#include <stdio.h>

#include "armstrong.h"

static int tests_passed = 0;

static void check_case(int test_number, int number, int expected)
{
    int actual = is_armstrong_number(number) != 0;
    const char *result = actual == expected ? "PASS" : "FAIL";

    printf("Test %d: %d -> %s\n", test_number, number, result);

    if (actual == expected) {
        tests_passed++;
    }else{
        printf("Tests with input %d failed.\n", number);
    }
}

int main(void)
{
    check_case(1, 100, 0);
    check_case(2, 153, 1);
    check_case(3, 352, 0);
    check_case(4, 370, 1);
    check_case(5, 371, 1);
    check_case(6, 407, 1);
    check_case(7, 999, 0);

    if (tests_passed == 7) {
        printf("All 7 tests passed.\n");
        return 0;
    }

    printf("%d of 7 tests passed.\n", tests_passed);
    return 1;
}
