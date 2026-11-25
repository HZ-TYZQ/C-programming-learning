#include "input.h"

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ==================== [Antigravity 生成] 底层安全读行与整数解析辅助
 * ==================== */
/* 说明：兼容终端交互、\r\n 换行、无尾换行管道输入与 Ctrl+D EOF。
 * 返回值：1 = 读到一行（若超长则 *outTooLong = 1 且已清空该行剩余字符）；
 *        0 = 遇到 EOF（输入流已关闭）。
 */
static const char *skipSpaces(const char *s)
{
  if (s == NULL)
  {
    return NULL;
  }

  const char *currentChar = &s[0];

  while (*currentChar == ' ' || *currentChar == '\t')
  {
    currentChar += 1;
  }

  return currentChar;
}

static int readLineSafe(char *buf, size_t size, int *outTooLong)
{
  size_t len = 0;

  if (outTooLong != NULL)
  {
    *outTooLong = 0;
  }
  if (buf == NULL || size < 2)
  {
    return 0;
  }

  if (fgets(buf, (int)size, stdin) == NULL)
  {
    return 0;
  }

  len = strlen(buf);
  if (len > 0 && buf[len - 1] == '\n')
  {
    buf[len - 1] = '\0';
    len--;
    if (len > 0 && buf[len - 1] == '\r')
    {
      buf[len - 1] = '\0';
    }
    return 1;
  }

  /* 未读到 '\n'：探测是否刚好到达 EOF，否则丢弃本行多余输入并标记超长 */
  if (!feof(stdin))
  {
    int ch = getchar();
    if (ch != '\n' && ch != EOF)
    {
      if (outTooLong != NULL)
      {
        *outTooLong = 1;
      }
      while (ch != '\n' && ch != EOF)
      {
        ch = getchar();
      }
    }
  }

  if (len > 0 && buf[len - 1] == '\r')
  {
    buf[len - 1] = '\0';
  }
  return 1;
}

/* 跳过字符串前后空白，严格解析整行整数；成功写入 *outVal 返回 1，否则返回 0 */
static int parseStrictIntLine(const char *s, int *outVal)
{
  const char *p = s;
  char *endPtr = NULL;
  long val = 0;

  if (s == NULL || outVal == NULL)
  {
    return 0;
  }
  while (*p == ' ' || *p == '\t')
  {
    p++;
  }
  if (*p == '\0')
  {
    return 0;
  }

  errno = 0;
  val = strtol(p, &endPtr, 10);
  if (errno == ERANGE || endPtr == p || val < INT_MIN || val > INT_MAX)
  {
    return 0;
  }
  while (*endPtr == ' ' || *endPtr == '\t')
  {
    endPtr++;
  }
  if (*endPtr != '\0')
  {
    return 0;
  }

  *outVal = (int)val;
  return 1;
}
/* ==================== [Antigravity 生成 结束] ==================== */

/* ==================== [TODO: 请你自己实现] Step 3 终端安全输入函数
 * ==================== */

int readIntInRange(const char *prompt, int minVal, int maxVal, int *outVal)
{
  char buf[64];
  int tooLong = 0;
  int val;

  if (outVal == NULL || minVal > maxVal)
  {
    return 0;
  }

  while (1)
  {
    if (prompt != NULL)
    {
      printf("%s", prompt);
      fflush(stdout);
    }

    if (readLineSafe(buf, sizeof(buf), &tooLong) == 0)
    {
      return 0;
    }
    if (tooLong)
    {
      printf("数字太大啦!\n");
      continue;
    }

    if (parseStrictIntLine(buf, &val) == 0)
    {
      printf("要输入整数啦!\n");
      continue;
    }

    if (val < minVal || val > maxVal)
    {
      printf("范围不对啦!\n");
      continue;
    }

    break;
  }

  *outVal = val;
  return 1;
}

int readQuantityDefaultMax(const char *prompt, int maxVal, int *outQty)
{
  char buf[64];
  int tooLong = 0;
  int val;

  if (outQty == NULL)
  {
    return 0;
  }

  if (maxVal <= 0)
  {
    *outQty = 0;
    return 1;
  }

  while (1)
  {
    if (prompt != NULL)
    {
      printf("%s", prompt);
      fflush(stdout);
    }

    if (!readLineSafe(buf, sizeof(buf), &tooLong))
    {
      return 0;
    }
    else if (tooLong)
    {
      printf("数字太大啦!\n");
      continue;
    }

    if (*skipSpaces(buf) == '\0')
    {
      *outQty = maxVal;
      return 1;
    }
    else
    {
      if (!parseStrictIntLine(buf, &val))
      {
        printf("要输入整数啦!\n");
        continue;
      }
    }

    if (val > maxVal || val < 0)
    {
      printf("数字要在%d到%d里啦!\n", 0, maxVal);
      continue;
    }

    break;
  }

  *outQty = val;

  return 1;
}

enum StoryStep waitStoryStep(void)
{
  char buf[64];
  int tooLong = 0;

  if (!readLineSafe(buf, sizeof(buf), &tooLong))
  {
    return STEP_EOF;
  }
  if (tooLong)
  {
    return STEP_NEXT;
  }

  const char *p = skipSpaces(buf);

  if (*p == 'f' || *p == 'F')
  {
    return STEP_SPEED;
  }
  else if (*p == 's' || *p == 'S')
  {
    return STEP_SKIP_CHUNK;
  }

  return STEP_NEXT;
}

int waitEnter(const char *prompt)
{
  char buf[64];
  int tooLong = 0;

  if (prompt != NULL)
  {
    printf("%s", prompt);
    fflush(stdout);
  }

  if (!readLineSafe(buf, sizeof(buf), &tooLong))
  {
    return 0;
  }

  return 1;
}

int confirmAction(const char *prompt, int *outYes)
{
  char buf[64];
  int tooLong = 0;

  if (outYes == NULL)
  {
    return 0;
  }

  if (prompt != NULL)
  {
    printf("%s", prompt);
    fflush(stdout);
  }

  if (!readLineSafe(buf, sizeof(buf), &tooLong))
  {
    return 0;
  }
  if (tooLong)
  {
    *outYes = 0;
    return 1;
  }

  const char *p = skipSpaces(buf);

  if ((*p == 'Y' || *p == 'y') && (*skipSpaces(p + 1) == '\0'))
  {
    *outYes = 1;
  }
  else
  {
    *outYes = 0;
  }

  return 1;
}
