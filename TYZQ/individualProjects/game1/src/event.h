/* ==================== [Antigravity 生成] 抵达事件调度接口 ==================== */
#ifndef EVENT_H
#define EVENT_H

#include "game.h"

/* 执行当前星球的抵达事件（含运之星 50% 概率掷骰与分支交互）；
 * 正常完成（或未触发事件）返回 1，遇到 EOF 返回 0 */
int runArrivalEvent(struct GameState *state);

#endif
/* ==================== [Antigravity 生成 结束] ==================== */
