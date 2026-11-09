/************************************************************
 ** COPYRIGHT (c) 2026 Glasgow College Hainan, UESTC.
 **
 ** NAME:        test_print_image.c
 **
 ** DESCRIPTION: UESTCHN1005 - Lab 2 Exercise A Output Test
 **
 ** AUTHOR:      Wang, Ziyang
 **              Xie, Shuangyang
 **
 ** DATE:        2026-10-08
 **
 ************************************************************/

#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#define fileno _fileno
#define dup _dup
#define dup2 _dup2
#define close _close
#else
#include <unistd.h>
#endif
#include "image.h"

static int check_output(const int image[][MAX_SIZE], int rows, int cols,
                        const char *expected)
{
    FILE *capture = tmpfile();
    if (capture == NULL) {
        fputs("FAIL: cannot create a temporary file\n", stderr);
        return 0;
    }

    fflush(stdout);
    int saved_stdout = dup(fileno(stdout));
    if (saved_stdout < 0 || dup2(fileno(capture), fileno(stdout)) < 0) {
        fputs("FAIL: cannot capture output\n", stderr);
        if (saved_stdout >= 0) {
            close(saved_stdout);
        }
        fclose(capture);
        return 0;
    }

#ifdef _WIN32
    int old_mode = _setmode(fileno(stdout), _O_BINARY);
    if (old_mode < 0) {
        fputs("FAIL: cannot set binary output mode\n", stderr);
        dup2(saved_stdout, fileno(stdout));
        close(saved_stdout);
        fclose(capture);
        return 0;
    }
#endif
    print_image(image, rows, cols);
    fflush(stdout);
    int restored = dup2(saved_stdout, fileno(stdout));
    close(saved_stdout);
#ifdef _WIN32
    _setmode(fileno(stdout), old_mode);
#endif
    if (restored < 0 || fseek(capture, 0, SEEK_SET) != 0) {
        fputs("FAIL: cannot read captured output\n", stderr);
        fclose(capture);
        return 0;
    }

    size_t expected_length = strlen(expected);
    for (size_t i = 0; i < expected_length; i++) {
        int actual = fgetc(capture);
        if (actual != (unsigned char)expected[i]) {
            if (expected[i] == '\n' && actual == EOF) {
                fputs("FAIL: missing newline at the end of a row\n", stderr);
            } else if (expected[i] == '\n' && actual == ' ') {
                fputs("FAIL: extra space at the end of a row\n", stderr);
            } else {
                fprintf(stderr, "FAIL: output differs at byte %zu "
                        "(expected %d, got %d)\n",
                        i + 1, (unsigned char)expected[i], actual);
            }
            fclose(capture);
            return 0;
        }
    }
    if (fgetc(capture) != EOF) {
        fputs("FAIL: extra output after the final newline\n", stderr);
        fclose(capture);
        return 0;
    }
    fclose(capture);
    return 1;
}

int main(void)
{
    int image[MAX_SIZE][MAX_SIZE] = {{10, 20, 30}, {40, 50, 60}};
    if (!check_output(image, 2, 3, "10 20 30\n40 50 60\n") ||
        !check_output(image, 1, 1, "10\n") ||
        !check_output(image, 2, 1, "10\n40\n")) {
        return 1;
    }
    puts("PASS");
    return 0;
}
