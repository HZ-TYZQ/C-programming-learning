#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ITEM_COUNT 5

// Function prototypes
void print_menu(void);
// Step 2.2:
// Add an array to store the items' names.
void print_product_name(int id);

// More function prototypes will be added later.

int main(void)
{
  int choice = -1;

  // Step 2:
  // Declare arrays for prices, stock and sales.
  const int price[ITEM_COUNT] = {150, 200, 350, 500, 800};
  int stock[ITEM_COUNT] = {5, 4, 6, 3, 2};
  int sold[ITEM_COUNT] = {0, 0, 0, 0, 0};
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
      printf("===== Products List =====\n");
      printf("ID    Price(cents)    Stock     Name\n");

      for (int i = 0; i < ITEM_COUNT; i++)
      {
        printf("%-6d %-16d %-10d", i + 1, price[i], stock[i]);
        print_product_name(i + 1);
      }

      break;

    case 2:
      // TODO: Buy components
      printf("Under construction\n");
      break;

    case 3:
      // TODO: Random restock
      printf("Under construction\n");
      break;

    case 4:
      // TODO: Sales report
      printf("Under construction\n");
      break;

    case 5:
      // TODO: Inventory chart
      printf("Under construction\n");
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
// TODO: Display the menu
{
  printf("===== Component Vending System =====\n");
  printf("1. View Products\n");
  printf("2. Buy Components\n");
  printf("3. Random Restock\n");
  printf("4. Sales Report\n");
  printf("5. Inventory Chart\n");
  printf("0. Exit\n");
  printf("================================\n");
  printf("Enter your choice:\n");
}

void print_product_name(int id)
{
  switch (id)
  {
  case 1:
    printf("%s\n", "Resistor");
    break;

  case 2:
    printf("%s\n", "Capacitor");
    break;

  case 3:
    printf("%s\n", "LED");
    break;

  case 4:
    printf("%s\n", "Diode");
    break;

  case 5:
    printf("%s\n", "Transistor");
    break;
  }
}
