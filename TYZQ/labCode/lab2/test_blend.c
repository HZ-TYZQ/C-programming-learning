 /************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        test_blend.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 2 Exercise B Unit Test
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
    int a[MAX_SIZE][MAX_SIZE];
    int b[MAX_SIZE][MAX_SIZE];
    int out[MAX_SIZE][MAX_SIZE];
    const int sizes[3][2] = {{1, 1}, {2, 3}, {MAX_SIZE, MAX_SIZE}};
    for (int test = 0; test < 3; test++) {
        int rows = sizes[test][0], cols = sizes[test][1];
        for (int r = 0; r < MAX_SIZE; r++) {
            for (int c = 0; c < MAX_SIZE; c++) {
                a[r][c] = (r * 31 + c * 17) % 256;
                b[r][c] = 255 - a[r][c];
                out[r][c] = -1;
            }
        }
        blend_images(a, b, out, rows, cols);
        for (int r = 0; r < MAX_SIZE; r++) {
            for (int c = 0; c < MAX_SIZE; c++) {
                CHECK(a[r][c] == (r * 31 + c * 17) % 256,
                      "first input changed");
                CHECK(b[r][c] == 255 - a[r][c], "second input changed");
                CHECK(out[r][c] == (r < rows && c < cols ? 127 : -1),
                      "odd mean or inactive position");
            }
        }
    }
    int low[MAX_SIZE][MAX_SIZE] = {{0, 255, 20}, {30, 50, 70}};
    int high[MAX_SIZE][MAX_SIZE] = {{0, 255, 41}, {50, 70, 90}};
    const int expected[2][3] = {{0, 255, 30}, {40, 60, 80}};
    blend_images(low, high, out, 2, 3);
    for (int r = 0; r < 2; r++) {
        for (int c = 0; c < 3; c++) {
            CHECK(out[r][c] == expected[r][c], "mixed blend values");
        }
    }
    puts("PASS");
    return 0;
}
