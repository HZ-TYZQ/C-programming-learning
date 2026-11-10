#include "device.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static void test_register_success(void)
{
  // Arrange
  struct Device devices[MAX_DEVICES] = {0};
  int count = 0;

  // Act
  int result = registerDevice(devices, &count, 101, "Sensor A");

  // Assert
  assert(result == 0);
  assert(count == 1);
  assert(devices[0].id == 101);
  assert(devices[0].readingCount == 0);
  assert(devices[0].flags == ONLINE);
  assert(strcmp(devices[0].name, "Sensor A") == 0);
}

static void test_register_duplicate_id(void)
{
  // Arrange
  struct Device devices[MAX_DEVICES] = {0};
  int count = 0;

  // Act
  int result = registerDevice(devices, &count, 101, "Sensor A");

  // Assert
  assert(result == 0);
  assert(count == 1);
  assert(devices[0].id == 101);
  assert(devices[0].readingCount == 0);
  assert(devices[0].flags == ONLINE);
  assert(strcmp(devices[0].name, "Sensor A") == 0);

  // Act
  result = registerDevice(devices, &count, 101, "Sensor B");

  // Assert
  assert(result == -3);
  assert(count == 1);
  assert(devices[0].id == 101);
  assert(devices[0].readingCount == 0);
  assert(devices[0].flags == ONLINE);
  assert(strcmp(devices[0].name, "Sensor A") == 0);
}

static void test_register_invalid_name(void)
{
  // Arrange
  struct Device devices[MAX_DEVICES] = {0};
  int count = 0;

  // Act
  int result = registerDevice(devices, &count, 101, "Sensor A");

  // Assert
  assert(result == 0);
  assert(count == 1);
  assert(devices[0].id == 101);
  assert(devices[0].readingCount == 0);
  assert(devices[0].flags == ONLINE);
  assert(strcmp(devices[0].name, "Sensor A") == 0);

  // Act
  result = registerDevice(devices, &count, 102, "");

  // Assert
  assert(result == -5);
  assert(count == 1);
  assert(devices[0].id == 101);
  assert(devices[0].readingCount == 0);
  assert(devices[0].flags == ONLINE);
  assert(strcmp(devices[0].name, "Sensor A") == 0);

  // Act
  result = registerDevice(devices, &count, 102, "     ");

  // Assert
  assert(result == -5);
  assert(count == 1);
  assert(devices[0].id == 101);
  assert(devices[0].readingCount == 0);
  assert(devices[0].flags == ONLINE);
  assert(strcmp(devices[0].name, "Sensor A") == 0);

  // Act
  char testName[25] = "";
  for (int i = 0; i < 24; i++)
  {
    strcat(testName, "A");
  }
  result = registerDevice(devices, &count, 102, testName);

  // Assert
  assert(result == -4);
  assert(count == 1);
  assert(devices[0].id == 101);
  assert(devices[0].readingCount == 0);
  assert(devices[0].flags == ONLINE);
  assert(strcmp(devices[0].name, "Sensor A") == 0);
}

static void test_toggle_online(void)
{
  // Arrange
  struct Device devices[MAX_DEVICES] = {0};
  devices[0].flags = ONLINE | MAINTENANCE | HAS_DATA;

  // Act
  toggleOnline(devices);

  // Assert
  assert(devices[0].flags == 10);

  // Act
  toggleOnline(devices);

  // Assert
  assert(devices[0].flags == 11);
}

static void test_set_maintenance(void)
{
  // Arrange
  struct Device devices[MAX_DEVICES] = {0};
  devices[0].flags = ONLINE | HAS_DATA;

  // Act
  setMaintenance(devices, 1);

  // Assert
  assert(devices->flags == (ONLINE | MAINTENANCE | HAS_DATA));

  // Act
  for (int i = 0; i < 3; i++)
  {
    setMaintenance(devices, 1);
  }

  // Assert
  assert(devices->flags == (ONLINE | MAINTENANCE | HAS_DATA));

  // Act
  setMaintenance(devices, 0);

  // Assert
  assert(devices->flags == (ONLINE | HAS_DATA));

  // Act
  for (int i = 0; i < 3; i++)
  {
    setMaintenance(devices, 0);
  }

  // Assert
  assert(devices->flags == (ONLINE | HAS_DATA));
}

static void test_print_flags(void)
{
  // Arrange
  struct Device devices[MAX_DEVICES] = {0};
  devices[0].flags = ONLINE | MAINTENANCE | HAS_DATA;

  // Act
  printf("Expected: 00001011\n");
  printFlags(devices->flags);

  // Arrange
  devices[0].flags = 0x10Bu;

  // Act
  printf("Expected: 00001011\n");
  printFlags(devices->flags);

  // Arrange
  devices[0].flags = 0u;

  // Act
  printf("Expected: 00000000\n");
  printFlags(devices->flags);
}

static void test_add_readings(void)
{
  // Arrange
  struct Device devices[MAX_DEVICES] = {0};
  devices[0].flags = ONLINE;

  // Act
  int result = addReading(devices, 95);

  // Assert
  assert(result == 0);
  assert(devices->readingCount == 1);
  assert(devices->readings[0] == 95);
  assert(devices->flags == (ONLINE | HAS_DATA | ALARM));

  // Act
  result = addReading(devices, 50);

  // Assert
  assert(result == 0);
  assert(devices->readingCount == 2);
  assert(devices->readings[0] == 95);
  assert(devices->readings[1] == 50);
  assert(devices->flags == (ONLINE | HAS_DATA));
}

static void test_add_reading_offline(void)
{
  // Arrange
  struct Device devices[MAX_DEVICES] = {0};
  devices[0].flags = HAS_DATA | ALARM;
  devices[0].readings[0] = 95;
  devices[0].readingCount = 1;

  // Act
  int result = addReading(devices, 50);

  // Assert
  assert(result == -1);
  assert(devices->readingCount == 1);
  assert(devices->readings[0] == 95);
  assert(devices->flags == (HAS_DATA | ALARM));
}

int main(void)
{
  test_register_success();
  test_register_duplicate_id();
  test_register_invalid_name();
  test_toggle_online();
  test_set_maintenance();
  test_print_flags();
  test_add_readings();
  test_add_reading_offline();
}
