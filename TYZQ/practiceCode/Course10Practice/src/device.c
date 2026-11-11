#include "device.h"
#include <stdio.h>
#include <string.h>

int findDeviceById(const struct Device *device, int count, int targetId)
{
  for (int i = 0; i < count; i++)
  {
    if ((device + i)->id == targetId)
    {
      return i;
    }
  }
  return -1;
}

int registerDevice(struct Device *devices, int *count, int id, const char *name)
{
  if (*count >= MAX_DEVICES)
  {
    return -1;
  }
  else if (id <= 0)
  {
    return -2;
  }
  else if (findDeviceById(devices, *count, id) != -1)
  {
    return -3;
  }
  else if (strlen(name) > NAME_SIZE - 1)
  {
    return -4;
  }
  else if (strspn(name, " \t\n\r\v\f") == strlen(name))
  {
    return -5;
  }

  struct Device temp = {0};
  temp.id = id;
  strcpy(temp.name, name);
  temp.readingCount = 0;
  temp.flags = ONLINE;

  devices[*count] = temp;
  (*count)++;

  return 0;
}

void toggleOnline(struct Device *device)
{
  device->flags ^= ONLINE;
}

void setMaintenance(struct Device *device, int enabled)
{
  if (enabled == 1)
  {
    device->flags |= MAINTENANCE;
  }
  else if (enabled == 0)
  {
    device->flags &= (~MAINTENANCE);
  }
}

void printFlags(unsigned int flags)
{
  for (int i = 7; i >= 0; i--)
  {
    printf("%u", (flags >> i) & 1u);
  }
  printf("\n");
}

int addReading(struct Device *device, int value)
{
  if ((device->flags & ONLINE) != ONLINE)
  {
    return -1;
  }
  else if ((device->flags & MAINTENANCE) == MAINTENANCE)
  {
    return -2;
  }
  else if (device->readingCount >= MAX_READINGS)
  {
    return -3;
  }
  else if (value < 0 || value > 100)
  {
    return -4;
  }

  device->readings[device->readingCount] = value;
  device->readingCount++;

  device->flags |= HAS_DATA;
  if (value >= 10 && value <= 90)
  {
    device->flags &= (~ALARM);
  }
  else
  {
    device->flags |= ALARM;
  }

  return 0;
}

struct ReadingStats calculateStats(const struct Device *device)
{
  struct ReadingStats stats = {0};

  if (device->readingCount == 0)
  {
    return stats;
  }

  stats.count = device->readingCount;
  stats.minimum = device->readings[0];
  stats.maximum = device->readings[0];
  stats.sum = device->readings[0];

  for (int i = 1; i < device->readingCount; i++)
  {
    stats.sum += device->readings[i];
    if (stats.maximum < device->readings[i])
    {
      stats.maximum = device->readings[i];
    }
    if (stats.minimum > device->readings[i])
    {
      stats.minimum = device->readings[i];
    }
  }

  stats.average = (double)stats.sum / stats.count;

  return stats;
}

int matchesFlags(const struct Device *device, unsigned int mask, int requireAll)
{
  if (requireAll == 1)
  {
    if ((device->flags & mask) != mask)
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }
  else
  {
    if ((device->flags & mask) == 0)
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }
}

int filterDevices(const struct Device *devices, int count, unsigned int mask,
                  int requireAll, int *matchedIndices)
{
  int matchedCount = 0;

  for (int i = 0; i < count; i++)
  {
    if (matchesFlags((devices + i), mask, requireAll))
    {
      matchedIndices[matchedCount] = i;
      matchedCount++;
    }
  }

  return matchedCount;
}

int compareById(const struct Device *device1, const struct Device *device2)
{
  if (device1->id < device2->id)
  {
    return 0;
  }
  else if (device1->id > device2->id)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int compareByAverage(const struct Device *device1, const struct Device *device2)
{
  if (device1->readingCount != 0 && device2->readingCount == 0)
  {
    return 0;
  }
  else if (device1->readingCount == 0 && device2->readingCount != 0)
  {
    return 1;
  }
  else if (device1->readingCount == 0 && device2->readingCount == 0)
  {
    return compareById(device1, device2);
  }

  struct ReadingStats stats1 = calculateStats(device1);
  struct ReadingStats stats2 = calculateStats(device2);

  if (stats1.average > stats2.average)
  {
    return 0;
  }
  else if (stats1.average < stats2.average)
  {
    return 1;
  }
  else
  {
    return compareById(device1, device2);
  }
}

void sortDevices(struct Device *devices, int count,
                 int (*compare)(const struct Device *, const struct Device *))
{
  for (int i = 0; i < count - 1; i++)
  {
    for (int j = 0; j < count - i - 1; j++)
    {
      if (compare(&devices[j], &devices[j + 1]) > 0)
      {
        struct Device temp = devices[j];
        devices[j] = devices[j + 1];
        devices[j + 1] = temp;
      }
    }
  }
}

void printDevice(const struct Device *device)
{
  printf("ID: %d\n", device->id);
  printf("Name: %s\n", device->name);
  printf("Readings: %d\n", device->readingCount);
  printf("State: ");

  if ((device->flags & ONLINE) == 0)
  {
    printf("OFFLINE");
  }
  else
  {
    printf("ONLINE");
  }

  printf(" | ");

  if ((device->flags & MAINTENANCE) == 0)
  {
    printf("MAINTENANCE_OFF");
  }
  else
  {
    printf("MAINTENANCE_ON");
  }

  printf(" | ");

  if ((device->flags & ALARM) == 0)
  {
    printf("ALARM_OFF");
  }
  else
  {
    printf("ALARM_ON");
  }

  printf(" | ");

  if ((device->flags & HAS_DATA) == 0)
  {
    printf("NO_DATA");
  }
  else
  {
    printf("HAS_DATA");
  }

  printf("\n");

  printf("Flags: ");
  printFlags(device->flags);
  printf("\n");
}

void printAllDevices(const struct Device *devices, int count)
{
  if (count == 0)
  {
    printf("No devices.\n");
    return;
  }

  for (int i = 0; i < count; i++)
  {
    printDevice((devices + i));
  }
}

void printDeviceReport(const struct Device *device)
{
  printDevice(device);

  struct ReadingStats stats = calculateStats(device);

  printf("Sum: %d\n", stats.sum);

  if (stats.count == 0)
  {
    printf("No readings.\n");
    printf("Average: N/A\n");
    printf("Minimum: N/A\n");
    printf("Maximum: N/A\n");
    return;
  }
  else
  {
    for (int i = 0; i < device->readingCount; i++)
    {
      printf("%d ", device->readings[i]);
    }

    printf("\n");

    printf("Average: %.2f\n", stats.average);
    printf("Minimum: %d\n", stats.minimum);
    printf("Maximum: %d\n", stats.maximum);
  }
}
