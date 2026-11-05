#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>

int readInt(const char *prompt, int *value);
char *readString(const char *prompt, char *string, size_t capacity);

#endif /* INPUT_H */
