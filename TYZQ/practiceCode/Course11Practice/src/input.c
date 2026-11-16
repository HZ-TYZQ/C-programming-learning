#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Static function can only be used in this file.
static void discardLine(void) {

  int ch;

  while ((ch = getchar()) != '\n' && ch != EOF) {
  }

  return;
}

// Safely read user input and covert to int.
int readInt(const char *prompt, int *value) {
  char buffer[64];

  while (1) {

    printf("%s", prompt);
    fflush(stdout);

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
      return 0;
    }

    int parseEnd = 0;

    for (int i = 0; buffer[i] != '\0'; i++) {

      if (buffer[i] == '\n') {

        parseEnd = 1;

        break;
      }
    }

    if (!parseEnd) {

      int ch = getchar();

      if (ch != '\n' && ch != EOF) {
        printf("Too long, please retry.\n");
        discardLine();

        continue;
      }
    }

    char *end;

    errno = 0;

    long number = strtol(buffer, &end, 10);

    if (end == buffer) {

      printf("Invalid input.\n");
      continue;
    }

    if (*end != '\n' && *end != '\0') {

      printf("Invalid input.\n");
      continue;
    }

    if (errno == ERANGE || number < INT_MIN || number > INT_MAX) {

      printf("Integer out of range.\n");
      continue;
    }

    *value = number;

    return 1;
  }
}

char *readString(const char *prompt, char *string, size_t capacity) {

  while (1) {

    printf("%s", prompt);

    fflush(stdout);

    if (fgets(string, capacity, stdin) == NULL) {

      return NULL;
    }

    char *newLinePos = strchr(string, '\n');

    if (newLinePos != NULL) {

      *newLinePos = '\0';
    } else {

      int ch = getchar();

      if (ch != '\n' && ch != EOF) {

        printf("Too long, please retry.\n");
        discardLine();
        continue;
      }
    }

    return string;
  }
}
