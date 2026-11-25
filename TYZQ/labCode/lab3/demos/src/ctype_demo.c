#include <ctype.h>
#include <stdio.h>

int main(void)
{
  printf("isdigit('5'): %d\n", isdigit('5'));
  printf("isdigit(5):   %d\n", isdigit(5));
  printf("isdigit('A'): %d\n", isdigit('A'));

  char ch = 'b';

  toupper(ch);
  printf("Before assignment: %c\n", ch);

  ch = toupper(ch);
  printf("After assignment: %c\n", ch);

  printf("toupper('7'): %c\n", toupper('7'));

  return 0;
}
