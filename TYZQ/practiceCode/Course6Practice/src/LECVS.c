#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ITEM_COUNT 5

// Function prototypes
void print_menu(void);
// Step 2.2:
// Add an array to store the items' names.
void print_product_name(int id);
// Determine whether scanf reads normally

// More function prototypes will be added later.
int count_change_coins(int change);

int main(void) {
  int choice = -1;

  // Step 2:
  // Declare arrays for prices, stock and sales.
  const int price[ITEM_COUNT] = {150, 200, 350, 500, 800};
  int stock[ITEM_COUNT] = {5, 4, 6, 3, 2};
  int sold[ITEM_COUNT] = {0, 0, 0, 0, 0};
  // Step 3.3:
  int revenue = 0;
  int transactions = 0;
  // Step 5:
  // Initialise random number generator.
  srand((unsigned int)time(NULL));

  do {
    print_menu();

    if (scanf("%d", &choice) != 1) {
      printf("Input error.\n");
      return 1;
    }

    switch (choice) {
    case 1:
      printf("===== Products List =====\n");
      printf("ID    Price(cents)    Stock     Name\n");

      for (int i = 0; i < ITEM_COUNT; i++) {
        printf("%-6d %-16d %-10d", i + 1, price[i], stock[i]);
        print_product_name(i + 1);
      }

      break;

    case 2: {
      int id;
      int quantity;

      printf("Enter Product ID: ");

      if (scanf("%d", &id) != 1) {
        printf("Input error.\n");
        return 1;
      }

      if (id < 1 || id > ITEM_COUNT) {
        printf("Invalid product ID!\n");
        break;
      }

      int id_index = id - 1;

      printf("Enter Quantity: ");

      if (scanf("%d", &quantity) != 1) {
        printf("Input error.\n");
        return 1;
      }

      if (quantity <= 0) {
        printf("Quantity is not positive\n");
        break;
      }

      if (stock[id_index] < quantity) {
        printf("Insufficient stock!\n");
        break;
      }

      printf("Product selected successfully!\n");

      int total_price = price[id_index] * quantity;
      int payment;

      printf("Total: %d cents\n", total_price);

      printf("Enter Payment: ");

      if (scanf("%d", &payment) != 1) {
        printf("Input error.\n");
        return 1;
      }

      if (payment < total_price) {
        printf("Insufficient payment!\n");
        break;
      }

      int change = payment - total_price;
      printf("Payment accepted!\n");
      printf("Change: %d cents\n", change);
      int coins = count_change_coins(change);
      printf("Coins needed: %d\n", coins);

      stock[id_index] -= quantity;
      sold[id_index] += quantity;

      revenue += total_price;
      transactions++;

      break;
    }

    case 3: {
      int max_stock = 20;
      printf("===== Random Restock =====\n");

      for (int i = 0; i < ITEM_COUNT; i++) {
        int replenishment_quantity = rand() % 4;

        if (stock[i] + replenishment_quantity > max_stock) {
          replenishment_quantity = max_stock - stock[i];
        }

        stock[i] += replenishment_quantity;

        printf("Product %d: +%d\n", i + 1, replenishment_quantity);
      }

      printf("Restock completed!\n");

      break;
    }
    case 4: {
      static int report_views = 0;
      report_views++;

      int total_sold = 0;
      int remaining_stock = 0;

      for (int i = 0; i < ITEM_COUNT; i++) {

        total_sold += sold[i];
        remaining_stock += stock[i];
      }

      printf("===== Sales Report =====\n");

      printf("Total Revenue: %d cents\n", revenue);
      printf("Items Sold: %d\n", total_sold);
      printf("Transactions: %d\n", transactions);
      printf("Remaining Stock: %d\n", remaining_stock);
      printf("Report Viewed: %d times\n", report_views);

      printf("========================\n");

      break;
    }
    case 5: {
      printf("===== Inventory Chart =====\n");

      for (int i = 0; i < ITEM_COUNT; i++) {
        printf("Product %d: ", i + 1);
        for (int j = 0; j < stock[i]; j++) {
          printf("*");
        }

        printf("\n");
      }

      printf("===========================\n");

      break;
    }
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

void print_menu(void) {
  printf("===== Component Vending System =====\n");
  printf("1. View Products\n");
  printf("2. Buy Components\n");
  printf("3. Random Restock\n");
  printf("4. Sales Report\n");
  printf("5. Inventory Chart\n");
  printf("0. Exit\n");
  printf("====================================\n");
  printf("Enter your choice:\n");
}

void print_product_name(int id) {
  switch (id) {
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

int count_change_coins(int change) {
  if (change == 0) {
    return 0;
  }

  if (change >= 100) {
    return 1 + count_change_coins(change - 100);
  }

  if (change >= 50) {
    return 1 + count_change_coins(change - 50);
  }

  if (change >= 20) {
    return 1 + count_change_coins(change - 20);
  }

  if (change >= 10) {
    return 1 + count_change_coins(change - 10);
  }

  if (change >= 5) {
    return 1 + count_change_coins(change - 5);
  }

  if (change >= 1) {
    return 1 + count_change_coins(change - 1);
  }

  return -1;
}
