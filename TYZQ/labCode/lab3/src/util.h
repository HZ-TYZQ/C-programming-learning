/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        util.h
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 3 Exercises A and E Utility Interface
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **              YOUR NAME HERE
 **
 ** DATE:        2026-10-20
 **
 ************************************************************/

#ifndef UTIL_H
#define UTIL_H

#include "parcel.h"
#define INPUT_CAPACITY 128

int read_line(char text[], int capacity);
int read_int(void);
void print_parcel(struct Parcel parcel);

#endif
