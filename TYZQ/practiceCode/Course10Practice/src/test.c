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

static void test_add_reading_maintenance(void)
{
  // Arrange
  struct Device devices[MAX_DEVICES] = {0};
  devices[0].flags = MAINTENANCE | ONLINE | HAS_DATA | ALARM;
  devices[0].readings[0] = 95;
  devices[0].readingCount = 1;

  // Act
  int result = addReading(devices, 50);

  // Assert
  assert(result == -2);
  assert(devices->readingCount == 1);
  assert(devices->readings[0] == 95);
  assert(devices->flags == (MAINTENANCE | ONLINE | HAS_DATA | ALARM));
}

static void test_add_reading_full(void)
{
  // Arrange
  struct Device devices[MAX_DEVICES] = {0};
  devices[0].flags = ONLINE;
  devices[0].readingCount = 0;

  for (int i = 0; i < MAX_READINGS; i++)
  {
    addReading(devices, i * 10);
  }

  // Act
  int result = addReading(devices, 50);

  // Assert
  assert(result == -3);
  assert(devices->readingCount == 10);
  assert(devices->readings[9] == 90);
  assert(devices->flags == (ONLINE | HAS_DATA));
}

static void test_add_reading_invalid_value(void)
{
  // Arrange
  struct Device devices[MAX_DEVICES] = {0};
  devices[0].flags = HAS_DATA | ONLINE | ALARM;
  devices[0].readings[0] = 95;
  devices[0].readingCount = 1;

  // Act
  int result = addReading(devices, 999);

  // Assert
  assert(result == -4);
  assert(devices->readingCount == 1);
  assert(devices->readings[0] == 95);
  assert(devices->flags == (ONLINE | HAS_DATA | ALARM));

  // Act
  result = addReading(devices, -1);

  // Assert assert(result == -4);
  assert(devices->readingCount == 1);
  assert(devices->readings[0] == 95);
  assert(devices->flags == (ONLINE | HAS_DATA | ALARM));
}

static void test_calculate_stats(void)
{
  // Arrange
  struct Device device[MAX_DEVICES] = {0};
  struct ReadingStats stats[3] = {0};
  device->readings[0] = 80;
  device->readings[1] = 20;
  device->readings[2] = 95;
  device->readings[3] = 50;
  device->readingCount = 4;
  (device + 2)->readings[0] = 80;
  (device + 2)->readingCount = 1;

  // Act
  stats[0] = calculateStats(device);
  stats[1] = calculateStats(device + 1);
  stats[2] = calculateStats(device + 2);

  // Assert
  assert(stats[0].count == 4);
  assert(stats[0].sum == 245);
  assert(stats[0].maximum == 95);
  assert(stats[0].minimum == 20);
  assert(stats[0].average == 61.25);

  assert(stats[1].count == 0);
  assert(stats[1].sum == 0);
  assert(stats[1].maximum == 0);
  assert(stats[1].minimum == 0);
  assert(stats[1].average == 0);

  assert(stats[2].count == 1);
  assert(stats[2].sum == 80);
  assert(stats[2].maximum == 80);
  assert(stats[2].minimum == 80);
  assert(stats[2].average == 80);
}

static void test_matches_flags(void)
{
  // Arrange
  struct Device device[MAX_DEVICES] = {0};
  device->flags = ONLINE | HAS_DATA;

  // Act && Assert: Any
  int result = matchesFlags(device, ONLINE | HAS_DATA | ALARM, 0);

  assert(result == 1);

  result = matchesFlags(device, ALARM, 0);

  assert(result == 0);

  // Act && Assert: All
  result = matchesFlags(device, ONLINE | HAS_DATA | ALARM, 1);

  assert(result == 0);

  result = matchesFlags(device, ONLINE | HAS_DATA, 1);

  assert(result == 1);
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
  test_add_reading_maintenance();
  test_add_reading_full();
  test_add_reading_invalid_value();
  test_calculate_stats();
  test_matches_flags();
}
