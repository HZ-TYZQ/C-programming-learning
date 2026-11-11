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
