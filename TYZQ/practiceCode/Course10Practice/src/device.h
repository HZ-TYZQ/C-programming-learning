/* LDM device data model */
#ifndef DEVICE_H
#define DEVICE_H

#define MAX_DEVICES 10
#define NAME_SIZE 24
#define MAX_READINGS 10

#define HAS_DATA (1u << 3)
#define ALARM (1u << 2)
#define MAINTENANCE (1u << 1)
#define ONLINE (1u << 0)

/* Data Model */
struct Device
{
  int id;
  char name[NAME_SIZE];
  int readings[MAX_READINGS];
  int readingCount;
  unsigned int flags;
};

struct ReadingStats
{
  int count;
  int sum;
  int maximum;
  int minimum;
  double average;
};

/* Search */
int findDeviceById(const struct Device devices[], int count, int targetId);

int registerDevice(struct Device devices[], int *count, int id,
                   const char *name);

void toggleOnline(struct Device *device);

void setMaintenance(struct Device *device, int enabled);

void printFlags(unsigned int flags);

int addReading(struct Device *device, int value);

struct ReadingStats calculateStats(const struct Device *device);

#endif /* DEVICE_H */
