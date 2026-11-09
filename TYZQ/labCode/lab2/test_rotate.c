 /************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        test_rotate.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 2 Exercise D Rotation Unit Test
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **
 ** DATE:        2026-10-08
 **
 ************************************************************/

/* Supplied local test: do not edit or submit as application code. */
#include <stdio.h>
#include "image.h"

#define CHECK(condition, message) do { \
    if (!(condition)) { \
        printf("FAIL: %s\n", message); \
        return 1; \
    } \
} while (0)

int main(void)
{
    int input[MAX_SIZE][MAX_SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int cw[MAX_SIZE][MAX_SIZE], ccw[MAX_SIZE][MAX_SIZE];
    const int want_cw[3][3] = {{7, 4, 1}, {8, 5, 2}, {9, 6, 3}};
    const int want_ccw[3][3] = {{3, 6, 9}, {2, 5, 8}, {1, 4, 7}};
    for (int r = 0; r < MAX_SIZE; r++) {
        for (int c = 0; c < MAX_SIZE; c++) {
            cw[r][c] = ccw[r][c] = -1;
        }
    }
    rotate_clockwise(input, cw, 3);
    rotate_counterclockwise(input, ccw, 3);
    for (int r = 0; r < MAX_SIZE; r++) {
        for (int c = 0; c < MAX_SIZE; c++) {
            int active = r < 3 && c < 3;
            CHECK(cw[r][c] == (active ? want_cw[r][c] : -1),
                  "clockwise result or inactive position");
            CHECK(ccw[r][c] == (active ? want_ccw[r][c] : -1),
                  "counterclockwise result or inactive position");
            CHECK(input[r][c] == (active ? r * 3 + c + 1 : 0),
                  "input changed");
        }
    }
    const int sizes[3] = {1, 2, MAX_SIZE};
    int stage2[MAX_SIZE][MAX_SIZE] = {0};
    int stage3[MAX_SIZE][MAX_SIZE] = {0};
    int restored[MAX_SIZE][MAX_SIZE] = {0};
    for (int test = 0; test < 3; test++) {
        int n = sizes[test];
        for (int r = 0; r < MAX_SIZE; r++) {
            for (int c = 0; c < MAX_SIZE; c++) {
                input[r][c] = (r * 19 + c * 7) % 256;
                cw[r][c] = ccw[r][c] = -1;
            }
        }
        rotate_clockwise(input, cw, n);
        rotate_counterclockwise(input, ccw, n);
        CHECK(cw[0][n - 1] == input[0][0], "clockwise top-left corner");
        CHECK(ccw[n - 1][0] == input[0][0], "counterclockwise top-left corner");
        rotate_counterclockwise(cw, restored, n);
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                CHECK(restored[r][c] == input[r][c], "opposite turns");
            }
        }
        rotate_clockwise(cw, stage2, n);
        rotate_clockwise(stage2, stage3, n);
        rotate_clockwise(stage3, restored, n);
        for (int r = 0; r < MAX_SIZE; r++) {
            for (int c = 0; c < MAX_SIZE; c++) {
                CHECK(input[r][c] == (r * 19 + c * 7) % 256, "input changed");
                if (r < n && c < n) {
                    CHECK(restored[r][c] == input[r][c], "four clockwise turns");
                } else {
                    CHECK(cw[r][c] == -1 && ccw[r][c] == -1,
                          "inactive position changed");
                }
            }
        }
    }
    puts("PASS");
    return 0;
}
