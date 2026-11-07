#include <stdio.h>

int main(void)
{

  int photo_count = 0;
  int pages = 0;
  int photo_remain = 0;
  int photo_per_page = 0;

  scanf("%d %d", &photo_count, &photo_per_page);

  if (photo_count > 0 && photo_per_page > 0)
  {
    photo_remain = photo_count % photo_per_page;
    pages = photo_count / photo_per_page;

    if (photo_remain != 0)
    {

      pages += 1;
    }

    else
    {

      photo_remain = photo_per_page;
    }
  }

  printf("%d\n%d\n", pages, photo_remain);
}
