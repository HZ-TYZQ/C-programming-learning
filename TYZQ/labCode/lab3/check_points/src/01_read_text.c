/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        01_read_text.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 3 Check Point 1
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **              YOUR NAME HERE
 **
 ** DATE:        2026-11-02
 **
 ************************************************************/

#include <stdio.h>
#include <string.h>

/**************************************************************
 * Function: main
 * Reads text without prompts using fgets and scanf for comparison.
 * Provides debugger stops to inspect the strings and their lengths.
 *
 * returns: 0 if all input calls succeed, or 1 if any input call fails.
 **************************************************************/
int main(void)
{
    char line[40];
    char word[40];

    /* Enter the same two-word name on each of two separate lines.
       There are no prompts. Observe where each input call stops. */
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }
    /* Set a breakpoint on the next statement to inspect line's elements. */
    size_t length = strlen(line); /* DEBUG STOP 1: after fgets */
    if (scanf("%39s", word) != 1) {
        return 1;
    }

    /* Set a breakpoint on the next statement to inspect word's elements.
       Use p with indexed elements. Inspect only through the first '\0'. */
    printf("fgets: [%s] (length %zu)\n", line, length); /* DEBUG STOP 2: after scanf */
    printf("scanf: [%s] (length %zu)\n", word, strlen(word));

    if (scanf("%39s", word) != 1) {
        return 1;
    }
    /* Inspect word again at the next statement. What did scanf read?
       Did you need to enter another line? Where is the terminator now? */
    printf("scanf again: [%s] (length %zu)\n", word, strlen(word)); /* DEBUG STOP 3 */
    return 0;
}
