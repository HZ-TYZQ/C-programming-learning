#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ITEM_COUNT 5

// Function prototypes
void print_menu(void);

// More function prototypes will be added later.

int main(void)
{
  int choice = -1;

  // Step 2:
  // Declare arrays for prices, stock and sales.

  // Step 5:
  // Initialise random number generator.

  do
  {
    print_menu();

    if (scanf("%d", &choice) != 1)
    {
      printf("Input error.\n");
      return 1;
    }

    switch (choice)
    {
    case 1:
      // TODO: View products
      break;

    case 2:
      // TODO: Buy components
      break;

    case 3:
      // TODO: Random restock
      break;

    case 4:
      // TODO: Sales report
      break;

    case 5:
      // TODO: Inventory chart
      break;

    case 0:
      printf("Goodbye!\n");
      break;

    default:
      printf("Invalid choice!\n");
      break;
    }

  } while (choice != 0);

  return 0;
}

void print_menu(void)
{
  // TODO: Display the menu.
}
