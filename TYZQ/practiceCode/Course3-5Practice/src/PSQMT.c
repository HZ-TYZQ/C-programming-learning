#include <stdio.h>

void print_menu(void)
{
  printf("===== Voltage QC System =====\n1. Start new test\n2. Show last "
         "report\n0. Exit\nSelect:");
}

int determine_voltage_level(float voltage)
{
  if (voltage == -1.0f)
  { // 强制结束samples输入"-1"（-1 可精确表示，等值比较安全）
    return 4;
  }
  else if (voltage < 0.0f || voltage > 5.0f)
  {
    return 0;
  }
  else if (voltage < 3.10f)
  { // 用 float 字面量，避免 float 提升为 double
    // 后 3.10f < 3.10 误判
    return 1;
  }
  else if (voltage <= 3.50f)
  {
    return 2;
  }
  else
  {
    return 3;
  }
}

int main(void)
{

  char menu_choice;
  int samples = 0;
  float voltage = 0;
  int lowCount = 0;
  int normalCount = 0;
  int highCount = 0;
  int invalidCount = 0;
  int validCount = 0;
  int hasData = 0;

  float sum = 0;
  float minVoltage;
  float maxVoltage;
  float averge = 0.0f;

  do
  {

    print_menu();               // 显示菜单
    scanf(" %c", &menu_choice); // 读取选项

    switch (menu_choice)
    {
    case '1': // 选择1, 开始测试, 初始化数据
      samples = 0;
      voltage = 0;
      lowCount = 0;
      normalCount = 0;
      highCount = 0;
      invalidCount = 0;
      validCount = 0;
      sum = 0;
      averge = 0;
      printf("How many samples?");

      do
      {
        scanf("%d", &samples);

        if (samples < 1 || samples > 20)
        {
          printf("Invalid number. Enter again:");
        }

      } while (samples < 1 || samples > 20);

      for (int i = 0; i < samples; i++)
      {
        printf("Sample %d: ", i + 1);
        scanf("%f", &voltage);

        int level = determine_voltage_level(voltage);

        if (level == 4)
        {
          printf("Test stopped.\n");
          break; // 跳出for循环
        }

        switch (level)
        {
        case 1:
          printf("LOW\n");
          lowCount++;
          break;

        case 2:
          printf("NORMAL\n");
          normalCount++;
          break;

        case 3:
          printf("HIGH\n");
          highCount++;
          break;

        default:
          printf("INVALID - ignored\n");
          invalidCount++;
          continue;
        }
        if (validCount == 0)
        {
          maxVoltage = voltage;
          minVoltage = voltage;
        }
        else
        {

          if (maxVoltage < voltage)
          {
            maxVoltage = voltage;
          }
          if (minVoltage > voltage)
          {
            minVoltage = voltage;
          }
        }

        validCount++;
        sum += voltage;
      }

      if (validCount == 0)
      {
        printf("No valid voltage, can not calculate average.\n");
      }
      else
      {
        averge = sum / validCount;
      }

      hasData++;
      break;

    case '2': // 选择2, 读取上次读数并打印

      if (hasData)
      {
        printf("===== Last Test Report =====\n");
        printf("%-15s: %6d\n", "Valid samples", validCount);
        printf("%-15s: %6d\n\n", "Invalid", invalidCount);
        printf("%-15s: %6d\n", "Low", lowCount);
        printf("%-15s: %6d\n", "Normal", normalCount);
        printf("%-15s: %6d\n\n", "High", highCount);
        if (validCount > 0)
        {
          printf("%-15s: %6.2f\n", "Average", averge);
          printf("%-15s: %6.2f\n", "Minimum", minVoltage);
          printf("%-15s: %6.2f\n", "Maximum", maxVoltage);
        }
        else
        {
          printf("No valid voltage data.\n");
        }
        int isPass = (validCount > 0 && lowCount == 0 && highCount == 0 &&
                      invalidCount == 0);
        printf("%-15s: %s\n", "Result", isPass ? "PASS" : "WARN");

        for (int i = 0; i < 4; i++)
        {
          int count = 0;

          switch (i)
          {
          case 0:
            count = lowCount;
            printf("%-8s: ", "LOW");
            break;

          case 1:
            count = normalCount;
            printf("%-8s: ", "NORMAL");
            break;

          case 2:
            count = highCount;
            printf("%-8s: ", "HIGH");
            break;

          case 3:
            count = invalidCount;
            printf("%-8s: ", "INVALID");
            break;
          }

          for (int j = 0; j < count; j++)
          {
            printf("*");
          }

          printf("\n");
        }
      }

      else
      {
        printf("No test data available.\n");
      }
      break;

    case '0':
      break;

    default:
      printf("Invalid option.\n");
      break;
    }
  } while (menu_choice != '0');
}
