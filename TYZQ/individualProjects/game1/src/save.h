/* ==================== [Antigravity 生成] 存档文件 I/O 接口 ==================== */
#ifndef SAVE_H
#define SAVE_H

#include "game.h"

#define DEFAULT_SAVE_PATH "save.txt"

struct SaveSummary
{
    int day;
    int phase;
    int planet;
    int money;
};

/* 原子写入存档文件（先写 "%s.tmp"，再 rename 覆盖 path）；成功返回 1，失败返回 0 */
int saveGame(const char *path, const struct GameState *state);

/* 严格逐行读取并校验 9 行存档文件；成功写入 outState 返回 1，失败返回 0 且不污染 outState */
int loadGame(const char *path, struct GameState *outState);

/* 复用 loadGame 读取存档摘要（供标题菜单展示）；有效返回 1，否则返回 0 */
int peekSaveSummary(const char *path, struct SaveSummary *outSummary);

/* 判断 path 是否存在且为合法存档；有效返回 1，否则返回 0 */
int hasValidSave(const char *path);

#endif
/* ==================== [Antigravity 生成 结束] ==================== */
