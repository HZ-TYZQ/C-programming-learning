/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        image.h
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 2 Shared Image Interface
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **
 ** DATE:        2026-10-08
 **
 ************************************************************/

#ifndef IMAGE_H
#define IMAGE_H

#define MAX_SIZE 20

void print_image(const int image[][MAX_SIZE], int rows, int cols);

void blend_images(
    const int image1[][MAX_SIZE],
    const int image2[][MAX_SIZE],
    int output[][MAX_SIZE],
    int rows,
    int cols
);

void adjust_brightness(
    const int input[][MAX_SIZE],
    int output[][MAX_SIZE],
    int rows,
    int cols,
    int change
);

void rotate_clockwise(
    const int input[][MAX_SIZE],
    int output[][MAX_SIZE],
    int n
);

void rotate_counterclockwise(
    const int input[][MAX_SIZE],
    int output[][MAX_SIZE],
    int n
);

#endif
