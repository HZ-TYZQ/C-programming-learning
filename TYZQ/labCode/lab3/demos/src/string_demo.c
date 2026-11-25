#include <stdio.h>
#include <string.h>

int main(void)
{
  char text[] = "Hi\n";

  printf("Text: [%s]\n", text);
  printf("Length: %zu\n", strlen(text));
  printf("Size: %zu\n", sizeof(text));

  for (int i = 0; i < sizeof(text); i++)
  {
    printf("text[%d] = %d\n", i, (int)text[i]);
  }

  return 0;
}
