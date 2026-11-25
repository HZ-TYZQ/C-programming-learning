/*--------------- <generated with GPT-6> ------------------*/
#include "save.h"
#include "game.h"

#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ==================== [Antigravity 生成] 严格逐行文本解析辅助函数
 * ==================== */
/* 说明：这里处理了几个 C 语言里容易踩雷的细节：
 * 1. fgets 行超长截断检测与 \r\n 清理；
 * 2. strtol / strtoul 的 errno == ERANGE 溢出检测与行尾多余字符拦截；
 * 3. strtoul 默认接受负号 '-' 的冷门特性（显式拒绝负号）。
 * 你的 loadGame() 可以直接调用下面这 4 个 static 辅助函数。
 */

static int readExactLine(FILE *fp, char *buf, size_t size)
{
  if (fp == NULL || buf == NULL || size < 2)
  {
    return 0;
  }

  /* 填入非零字节，便于从尾部找到 fgets 添加的字符串终止符。 */
  memset(buf, 1, size);
  if (fgets(buf, (int)size, fp) == NULL)
  {
    return 0;
  }

  size_t len = size - 1;
  while (buf[len] != '\0')
  {
    len--;
  }
  if (memchr(buf, '\0', len) != NULL)
  {
    return 0;
  }

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

  /* 未读到换行符时，只有在刚好到达文件末尾才算完整行，否则说明单行超长 */
  return feof(fp) != 0;
}
/*------------------------ <END> -------------------------*/

static int parseKeyInt(const char *line, const char *prefix, int *outVal)
{
  size_t prefixLen = 0;
  const char *numStr = NULL;
  char *endPtr = NULL;
  long val = 0;

  if (line == NULL || prefix == NULL || outVal == NULL)
  {
    return 0;
  }
  prefixLen = strlen(prefix);
  if (strncmp(line, prefix, prefixLen) != 0)
  {
    return 0;
  }

  numStr = line + prefixLen;
  if (*numStr == '\0' || *numStr == ' ' || *numStr == '\t')
  {
    return 0;
  }

  errno = 0;
  val = strtol(numStr, &endPtr, 10);
  if (errno == ERANGE || endPtr == numStr || *endPtr != '\0')
  {
    return 0;
  }
  if (val < INT_MIN || val > INT_MAX)
  {
    return 0;
  }

  *outVal = (int)val;
  return 1;
}

static int parseKeyUint(const char *line, const char *prefix, unsigned int *outVal)
{
  size_t prefixLen = 0;
  const char *numStr = NULL;
  char *endPtr = NULL;
  unsigned long val = 0;

  if (line == NULL || prefix == NULL || outVal == NULL)
  {
    return 0;
  }
  prefixLen = strlen(prefix);
  if (strncmp(line, prefix, prefixLen) != 0)
  {
    return 0;
  }

  numStr = line + prefixLen;
  /* 显式拒绝负号与前导空白，避免 strtoul 将 "-1" 静默回绕为超大无符号数 */
  if (*numStr == '\0' || *numStr == '-' || *numStr == '+' || *numStr == ' ' || *numStr == '\t')
  {
    return 0;
  }

  errno = 0;
  val = strtoul(numStr, &endPtr, 10);
  if (errno == ERANGE || endPtr == numStr || *endPtr != '\0')
  {
    return 0;
  }
  if (val > UINT_MAX)
  {
    return 0;
  }

  *outVal = (unsigned int)val;
  return 1;
}

static int parseCargoLine(const char *line, int outCargo[GOOD_COUNT])
{
  const char *prefix = "cargo ";
  size_t prefixLen = strlen(prefix);
  const char *p = NULL;
  int i = 0;

  if (line == NULL || outCargo == NULL || strncmp(line, prefix, prefixLen) != 0)
  {
    return 0;
  }

  p = line + prefixLen;
  for (i = 0; i < GOOD_COUNT; i++)
  {
    char *endPtr = NULL;
    long val = 0;

    if (*p == '\0' || *p == ' ' || *p == '\t')
    {
      return 0;
    }
    errno = 0;
    val = strtol(p, &endPtr, 10);
    if (errno == ERANGE || endPtr == p || val < INT_MIN || val > INT_MAX)
    {
      return 0;
    }
    outCargo[i] = (int)val;

    if (i < GOOD_COUNT - 1)
    {
      if (*endPtr != ' ')
      {
        return 0;
      }
      p = endPtr + 1;
    }
    else
    {
      if (*endPtr != '\0')
      {
        return 0;
      }
    }
  }
  return 1;
}
/* ==================== [Antigravity 生成 结束] ==================== */

/* ==================== [TODO: 请你自己实现] Step 2 Course 12 文件 I/O 实战
 * ==================== */

int saveGame(const char *path, const struct GameState *state)
{
  if (path == NULL || path[0] == '\0' || validateGameState(state) == 0)
  {
    return 0;
  }

  char temPath[512];
  int length = snprintf(temPath, sizeof(temPath), "%s.tmp", path);

  if (length < 0 || (size_t)length >= sizeof(temPath))
  {
    return 0;
  }

  FILE *fp = fopen(temPath, "w");
  if (fp == NULL)
  {
    return 0;
  }

  int fprintfResult = fprintf(
    fp,
    "NEXT_STOP_BIRTHDAY_V1\n"
    "day %d\n"
    "phase %d\n"
    "planet %d\n"
    "trips_left %d\n"
    "money %d\n"
    "cargo_cap %d\n"
    "cargo %d %d %d %d %d\n"
    "flags %u\n",
    state->day,
    state->phase,
    state->planet,
    state->tripsLeft,
    state->money,
    state->cargoCap,
    state->cargo[0],
    state->cargo[1],
    state->cargo[2],
    state->cargo[3],
    state->cargo[4],
    state->flags);

  int fcloseResult = fclose(fp);

  if (fprintfResult < 0 || fcloseResult == EOF)
  {
    remove(temPath);
    return 0;
  }

  if (rename(temPath, path) != 0)
  {
    remove(temPath);
    return 0;
  }

  return 1;
}

int loadGame(const char *path, struct GameState *outState)
{
  char buf[64];

  if (path == NULL || outState == NULL)
  {
    return 0;
  }

  FILE *fp = fopen(path, "r");
  if (fp == NULL)
  {
    return 0;
  }

  if (!readExactLine(fp, buf, sizeof(buf)) || strcmp(buf, "NEXT_STOP_BIRTHDAY_V1") != 0)
  {
    fclose(fp);
    return 0;
  }

  struct GameState temp = {0};

  if (!readExactLine(fp, buf, sizeof(buf)))
  {
    fclose(fp);
    return 0;
  }
  if (!parseKeyInt(buf, "day ", &temp.day))
  {
    fclose(fp);
    return 0;
  }

  if (!readExactLine(fp, buf, sizeof(buf)))
  {
    fclose(fp);
    return 0;
  }
  if (!parseKeyInt(buf, "phase ", &temp.phase))
  {
    fclose(fp);
    return 0;
  }

  if (!readExactLine(fp, buf, sizeof(buf)))
  {
    fclose(fp);
    return 0;
  }
  if (!parseKeyInt(buf, "planet ", &temp.planet))
  {
    fclose(fp);
    return 0;
  }

  if (!readExactLine(fp, buf, sizeof(buf)))
  {
    fclose(fp);
    return 0;
  }
  if (!parseKeyInt(buf, "trips_left ", &temp.tripsLeft))
  {
    fclose(fp);
    return 0;
  }

  if (!readExactLine(fp, buf, sizeof(buf)))
  {
    fclose(fp);
    return 0;
  }
  if (!parseKeyInt(buf, "money ", &temp.money))
  {
    fclose(fp);
    return 0;
  }

  if (!readExactLine(fp, buf, sizeof(buf)))
  {
    fclose(fp);
    return 0;
  }
  if (!parseKeyInt(buf, "cargo_cap ", &temp.cargoCap))
  {
    fclose(fp);
    return 0;
  }

  if (!readExactLine(fp, buf, sizeof(buf)))
  {
    fclose(fp);
    return 0;
  }
  if (!parseCargoLine(buf, temp.cargo))
  {
    fclose(fp);
    return 0;
  }

  if (!readExactLine(fp, buf, sizeof(buf)))
  {
    fclose(fp);
    return 0;
  }
  if (!parseKeyUint(buf, "flags ", &temp.flags))
  {
    fclose(fp);
    return 0;
  }

  int hasExtra = fgets(buf, sizeof(buf), fp) != NULL;
  int readError = ferror(fp);
  int closeResult = fclose(fp);

  if (hasExtra || readError || closeResult == EOF)
  {
    return 0;
  }

  if (!validateGameState(&temp))
  {
    return 0;
  }

  *outState = temp;

  return 1;
}

int peekSaveSummary(const char *path, struct SaveSummary *outSummary)
{

  struct GameState temp;

  if (outSummary == NULL)
  {
    return 0;
  }
  if (!loadGame(path, &temp))
  {
    return 0;
  }

  outSummary->day = temp.day;
  outSummary->phase = temp.phase;
  outSummary->planet = temp.planet;
  outSummary->money = temp.money;

  return 1;
}

int hasValidSave(const char *path)
{
  struct GameState temp;

  return loadGame(path, &temp);
}
