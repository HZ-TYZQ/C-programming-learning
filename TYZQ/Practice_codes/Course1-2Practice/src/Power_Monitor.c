#include <stdio.h>

int device_id;
double voltage;
double current;
int samples;
int invalid_samples;

int is_safe(double voltage, double current, double valid_sample_rate) {

  if (voltage >= 3.0 && voltage <= 3.6 && current <= 0.50 &&
      valid_sample_rate >= 0.95)
    return 1;
  else
    return 0;
}

int main(void) {

  scanf("%d %lf %lf %d %d", &device_id, &voltage, &current, &samples,
        &invalid_samples);

  double power = voltage * current;
  int valid_samples = samples - invalid_samples;
  double valid_sample_rate = (double)valid_samples / samples;

  printf("Device ID: %d\nVoltage: %.2lf V\nCurrent: %.2lf A\nPower: %.2lf "
         "W\nValid samples: %.2lf%%\n",
         device_id, voltage, current, power, valid_sample_rate * 100);
  if (is_safe(voltage, current, valid_sample_rate))
    printf("Status: SAFE");
  else
    printf("Status: UNSAFE");
}
