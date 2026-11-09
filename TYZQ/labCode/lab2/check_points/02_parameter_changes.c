/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        02_parameter_changes.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 2 Check Point 2
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **              YOUR NAME HERE
 **
 ** DATE:        2026-10-20
 **
 ************************************************************/

#include <stdio.h>
#include "../image.h"

void change_values(int value, int image[][MAX_SIZE])
{
    value = 0;
    image[0][0] = value;
}

int main(void)
{
    int number = 10;
    int image[MAX_SIZE][MAX_SIZE] = {{10}};

    /* Before running, predict the two values printed after this call.
     * Afterwards, explain why the assignments affect the caller differently.
     */
    change_values(number, image);

    printf("number: %d\n", number);
    printf("image[0][0]: %d\n", image[0][0]);
    return 0;
}
