#include <stdio.h>

int get_status(double error_rate, double valid_rate) {
  if (error_rate <= 0.05 && valid_rate >= 0.95) {
    return 1;
  }
  if (error_rate <= 0.10 && valid_rate >= 0.90) {
    return 2;

  } else {
    return 0;
  }
}

double get_absolute_value(double nominal_voltage, double measured_voltage) {
  double differences = measured_voltage - nominal_voltage;
  if (differences >= 0)
    return differences;
  if (differences < 0)
    return -differences;
  else
    return 0;
}

int main(void) {

  int device_number;
  double nominal_voltage;
  double measured_voltage;
  int total_samples;
  int error_samples;

  scanf("%d %lf %lf %d %d", &device_number, &nominal_voltage, &measured_voltage,
        &total_samples, &error_samples);

  if (total_samples <= 0 || error_samples < 0 ||
      error_samples > total_samples) {
    printf("Invalid sample data");
    return 0;
  }

  double absolute_error = get_absolute_value(nominal_voltage, measured_voltage);
  double error_rate = absolute_error / nominal_voltage;

  int valid_samples = total_samples - error_samples;
  double valid_rate = (double)valid_samples / total_samples;

  int status = get_status(error_rate, valid_rate);

  printf("Device ID: %d\nNominal voltage: %.2lfV\nMeasured voltage: "
         "%.2lfV\nAbsolute error: %.2lf\nError rate: %.2lf%%\nValid samples: "
         "%d\nValid rate: %.2lf%%\n",
         device_number, nominal_voltage, measured_voltage, absolute_error,
         error_rate * 100, valid_samples, valid_rate * 100);

  if (status == 1)
    printf("PASS\n");

  else if (status == 2)
    printf("WARNING\n");

  else
    printf("FAIL\n");
}
