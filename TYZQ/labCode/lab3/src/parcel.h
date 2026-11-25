/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        parcel.h
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 3 Shared Parcel Interface
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **
 ** DATE:        2026-10-09
 **
 ************************************************************/

#ifndef PARCEL_H
#define PARCEL_H

#define MAX_PARCELS 20
#define CODE_CAPACITY 7
#define RECIPIENT_CAPACITY 40

struct Parcel {
    char code[CODE_CAPACITY];
    char recipient[RECIPIENT_CAPACITY];
    int priority;
    int arrival_order;
};

int normalize_tracking_code(char code[]);
int find_parcel(const struct Parcel parcels[], int count, const char target[]);
int compare_parcel(struct Parcel first, struct Parcel second);
void sort_parcels(struct Parcel parcels[], int count);

#endif
