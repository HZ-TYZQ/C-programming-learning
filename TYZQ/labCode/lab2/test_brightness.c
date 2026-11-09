 /************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        test_brightness.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 2 Exercise C Unit Test
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
    const int values[4] = {0, 100, 240, 255};
    const int changes[5] = {30, -30, 0, 255, -255};
    const int expected[5][4] = {
        {30, 130, 255, 255}, {0, 70, 210, 225}, {0, 100, 240, 255},
        {255, 255, 255, 255}, {0, 0, 0, 0}
    };
    const int sizes[3][2] = {{1, 1}, {2, 4}, {MAX_SIZE, MAX_SIZE}};
    int input[MAX_SIZE][MAX_SIZE], out[MAX_SIZE][MAX_SIZE];
    for (int test = 0; test < 3; test++) {
        int rows = sizes[test][0], cols = sizes[test][1];
        for (int k = 0; k < 5; k++) {
            for (int r = 0; r < MAX_SIZE; r++) {
                for (int c = 0; c < MAX_SIZE; c++) {
                    input[r][c] = values[(r + c) % 4];
                    out[r][c] = -1;
                }
            }
            adjust_brightness(input, out, rows, cols, changes[k]);
            for (int r = 0; r < MAX_SIZE; r++) {
                for (int c = 0; c < MAX_SIZE; c++) {
                    CHECK(input[r][c] == values[(r + c) % 4],
                          "input changed");
                    int want = r < rows && c < cols
                        ? expected[k][(r + c) % 4] : -1;
                    CHECK(out[r][c] == want, "brightness or inactive position");
                }
            }
        }
    }
    puts("PASS");
    return 0;
}
