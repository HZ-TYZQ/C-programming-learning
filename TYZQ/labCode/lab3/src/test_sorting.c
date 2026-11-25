/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        test_sorting.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 3 Exercise D Local Tests
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
 * Function: check_pair
 * Tests the comparator on one pair and reports an unexpected result.
 *
 * name: The case label used in a failure message.
 * first: The first record passed to compare_parcel.
 * second: The second record passed to compare_parcel.
 * expected: The expected comparator flag, 1 or 0.
 *
 * returns: 1 if the result matches, or 0 if it differs.
 **************************************************************/
static int check_pair(const char *name, struct Parcel first,
                      struct Parcel second, int expected)
{
    int actual = compare_parcel(first, second);
    if (actual != expected) {
        printf("FAIL %s: expected %d, got %d\n", name, expected, actual);
        return 0;
    }
    return 1;
}

/**************************************************************
 * Function: same_record
 * Checks every field to verify that a complete record was preserved.
 *
 * actual: The record produced by the code under test.
 * expected: The record it should match.
 *
 * returns: 1 if all fields match, or 0 otherwise.
 **************************************************************/
static int same_record(struct Parcel actual, struct Parcel expected)
{
    return strcmp(actual.code, expected.code) == 0 &&
           strcmp(actual.recipient, expected.recipient) == 0 &&
           actual.priority == expected.priority &&
           actual.arrival_order == expected.arrival_order;
}

/**************************************************************
 * Function: check_sort
 * Sorts a copy of the supplied array and checks every record, including
 * inactive records that must remain unchanged.
 *
 * name: The case label used in a failure message.
 * input: The original records to copy; this array remains unchanged.
 * expected: The expected order of the active records.
 * count: The number of active records to sort.
 * total: The total number of supplied records, at most MAX_PARCELS.
 *
 * returns: 1 if every record matches, or 0 with a diagnostic otherwise.
 **************************************************************/
static int check_sort(const char *name, const struct Parcel input[],
                      const struct Parcel expected[], int count, int total)
{
    struct Parcel actual[MAX_PARCELS];
    for (int i = 0; i < total; i++) {
        actual[i] = input[i];
    }
    sort_parcels(actual, count);
    for (int i = 0; i < total; i++) {
        struct Parcel want = i < count ? expected[i] : input[i];
        if (!same_record(actual[i], want)) {
            printf("FAIL %s: record %d got [%s | %s | %d | %d]\n",
                   name, i, actual[i].code, actual[i].recipient,
                   actual[i].priority, actual[i].arrival_order);
            return 0;
        }
    }
    return 1;
}

/**************************************************************
 * Function: main
 * Tests Exercise D ordering keys, complete-record swaps, inactive records,
 * boundary counts, and sorted and reverse input without keyboard input.
 * Prints PASS Exercise D if all cases pass, or failure diagnostics.
 *
 * returns: 0 if all cases pass, or 1 if any case fails.
 **************************************************************/
int main(void)
{
    struct Parcel late = {"AB1234", "Mia Chen", 2, 5};
    struct Parcel early = {"CD5678", "Ava Patel", 2, 1};
    struct Parcel urgent = {"ZX9000", "Leo Wang", 3, 9};
    struct Parcel same_key_a = {"AA0001", "Iya Li", 2, 5};
    struct Parcel same_key_b = {"AB1234", "Nia Li", 2, 5};
    struct Parcel identical_keys = {"AB1234", "Other", 2, 5};
    int passed = 1;
    passed &= check_pair("priority", late, urgent, 1);
    passed &= check_pair("reverse priority", urgent, late, 0);
    passed &= check_pair("arrival", late, early, 1);
    passed &= check_pair("reverse arrival", early, late, 0);
    passed &= check_pair("code", same_key_b, same_key_a, 1);
    passed &= check_pair("reverse code", same_key_a, same_key_b, 0);
    passed &= check_pair("equal keys", late, identical_keys, 0);

    struct Parcel parcels[] = {late, early, urgent, same_key_a, same_key_b};
    struct Parcel expected[] = {urgent, early, same_key_a, late, same_key_b};
    struct Parcel pair[] = {early, late};
    struct Parcel first_three[] = {urgent, early, late};
    passed &= check_sort("zero active records", parcels, parcels, 0, 5);
    passed &= check_sort("one active record", parcels, parcels, 1, 5);
    passed &= check_sort("two active records", parcels, pair, 2, 5);
    passed &= check_sort("partial active range", parcels, first_three, 3, 5);
    passed &= check_sort("five records", parcels, expected, 5, 5);
    passed &= check_sort("already sorted", expected, expected, 5, 5);

    struct Parcel ordered[MAX_PARCELS];
    struct Parcel reverse[MAX_PARCELS];
    for (int i = 0; i < MAX_PARCELS; i++) {
        snprintf(ordered[i].code, sizeof ordered[i].code, "AB%04d", i);
        snprintf(ordered[i].recipient, sizeof ordered[i].recipient,
                 "Recipient %d", i);
        ordered[i].priority = 3 - i / 7;
        ordered[i].arrival_order = (i % 7) / 3;
    }
    for (int i = 0; i < MAX_PARCELS; i++) {
        reverse[i] = ordered[MAX_PARCELS - 1 - i];
    }
    passed &= check_sort("twenty reverse records", reverse, ordered,
                         MAX_PARCELS, MAX_PARCELS);
    passed &= check_sort("twenty sorted records", ordered, ordered,
                         MAX_PARCELS, MAX_PARCELS);
    if (passed) {
        puts("PASS Exercise D");
    }
    return !passed;
}
