#include "device.h"
#include "input.h"
#include <stdio.h>

static void printMenu(void)
{
  printf("========== Lab Device Monitor ==========\n1. Register device\n2. "
         "Display all devices\n3. Change device state\n4. Add reading\n5. View "
         "device report\n6. Filter devices by flags\n7. Sort devices\n0. "
         "Exit\n========================================\n");
}

int main(void)
{
  // Initialization
  int choice;
  struct Device devices[MAX_DEVICES] = {0};
  int deviceCount = 0;
  while (1)
  {
    printMenu();

    if (!readInt("Enter choice: ", &choice))
    {
      return 0;
    }

    switch (choice)
    {
    case 1:
    {
      int id;
      char name[NAME_SIZE];

      if (!readInt("Enter ID: ", &id))
      {
        return 0;
      }

      if (readString("Enter name: ", name, NAME_SIZE) == NULL)
      {
        return 0;
      }

      int result = registerDevice(devices, &deviceCount, id, name);

      if (result == -1)
      {
        printf("The maximum number of devices has been reached.\n");
      }
      else if (result == -2)
      {
        printf("Invalid ID.\n");
      }
      else if (result == -3)
      {
        printf("ID already exists.\n");
      }
      else if (result == -4)
      {
        printf("Name is too long.\n");
      }
      else if (result == -5)
      {
        printf("Name cannot be empty or whitespace-only.\n");
      }
      else if (result == 0)
      {
        printf("Registration successful.\n");
      }
      break;
    }
    case 2:
    {
      printAllDevices(devices, deviceCount);
      break;
    }
    case 3:
    {
      int targetId;
      if (!readInt("Target ID: ", &targetId))
      {
        return 0;
      }

      int targetIndex = findDeviceById(devices, deviceCount, targetId);

      if (targetIndex == -1)
      {
        printf("Device not found.\n");
        break;
      }

      int actionChoice;
      printf("========== Actions ==========\n");
      printf("1. Toggle online mode.\n");
      printf("2. Turn on maintenance mode.\n");
      printf("3. Turn off maintenance mode.\n");
      printf("=============================\n");

      if (!readInt("Choice: ", &actionChoice))
      {
        return 0;
      }

      if (actionChoice == 1)
      {
        toggleOnline(&devices[targetIndex]);
      }
      else if (actionChoice == 2)
      {
        setMaintenance(&devices[targetIndex], 1);
      }
      else if (actionChoice == 3)
      {
        setMaintenance(&devices[targetIndex], 0);
      }
      else
      {
        printf("Invalid choice.\n");
        break;
      }

      break;
    }
    case 4:
    {
      int targetId;

      if (!readInt("Target ID: ", &targetId))
      {
        return 0;
      }

      int targetIndex = findDeviceById(devices, deviceCount, targetId);

      if (targetIndex == -1)
      {
        printf("Device not found.\n");
        break;
      }

      int newReading;
      if (!readInt("Reading: ", &newReading))
      {
        return 0;
      }

      int result = addReading(&devices[targetIndex], newReading);

      if (result == -1)
      {
        printf("Device is offline.\n");
      }
      else if (result == -2)
      {
        printf("Device is under maintenance.\n");
      }
      else if (result == -3)
      {
        printf("Reading capacity is full.\n");
      }
      else if (result == -4)
      {
        printf("The reading should be between 0~100\n");
      }
      else if (result == 0)
      {
        printf("Add reading successfully.\n");
      }

      break;
    }
    case 5:
    {
      int targetId;

      if (!readInt("Target ID: ", &targetId))
      {
        return 0;
      }

      int targetIndex = findDeviceById(devices, deviceCount, targetId);

      if (targetIndex == -1)
      {
        printf("Device not found.\n");
        break;
      }

      printDeviceReport(&devices[targetIndex]);

      break;
    }
    case 6:
    {
      if (deviceCount == 0)
      {
        printf("No devices.\n");
        break;
      }

      int mask;
      if (!readInt("Enter mask: ", &mask))
      {
        return 0;
      }

      if (mask < 1 || mask > 15)
      {
        printf("Invalid mask.\n");
        break;
      }

      int matchingModeChoice;

      printf("=== Matching Mode ===\n");
      printf("1. Any\n");
      printf("2. All\n");
      printf("=====================\n");

      if (!readInt("Enter choice: ", &matchingModeChoice))
      {
        return 0;
      }

      if (matchingModeChoice != 1 && matchingModeChoice != 2)
      {
        printf("Invalid choice.\n");
        break;
      }

      int requireAll = matchingModeChoice - 1;

      int matchedIndices[MAX_DEVICES];

      int matchedCount =
          filterDevices(devices, deviceCount, mask, requireAll, matchedIndices);

      if (matchedCount == 0)
      {
        printf("No matched devices.\n");
        break;
      }

      for (int i = 0; i < matchedCount; i++)
      {
        printDevice(&devices[matchedIndices[i]]);
      }

      break;
    }
    case 7:
    {
      if (deviceCount == 0)
      {
        printf("No devices.\n");
        break;
      }

      int choice;

      printf("=== Sort Choice ===\n");
      printf("1. ID ascending\n");
      printf("2. Average descending\n");
      printf("===================\n");

      if (!readInt("Enter choice: ", &choice))
      {
        return 0;
      }

      if (choice != 1 && choice != 2)
      {
        printf("Invalid choice.\n");
        break;
      }

      if (choice == 1)
      {
        sortDevices(devices, deviceCount, compareById);
      }
      else if (choice == 2)
      {
        sortDevices(devices, deviceCount, compareByAverage);
      }

      printAllDevices(devices, deviceCount);
      break;
    }

    case 0:
      printf("Goodbye.\n");
      return 0;

    default:
      printf("Invalid choice.\n");
      break;
    }
  }
}
