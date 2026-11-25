/* ==================== [Antigravity 生成] 剧情播放接口 ==================== */
#ifndef STORY_H
#define STORY_H

#include "game.h"
#include "ui.h"

/* 主线与日常剧情播放：正常播放完毕返回 1，遇到 EOF 返回 0 */
int playBeginning(void);
int playDayNight(int day);
int playHotSpring(const struct GameState *state);
int playEnding(int choice, int moneyBeforeGift, int moneyAfterGift, unsigned int flags);

/* 5 个星球抵达事件的分段剧本播放（共享调用方传入的 StoryContext）：正常返回 1，EOF 返回 0 */
int playBookEventIntro(struct StoryContext *ctx);
int playBookEventBranch(struct StoryContext *ctx, int giveTea);

int playFlowerEventIntro(struct StoryContext *ctx);
int playFlowerEventBranch(struct StoryContext *ctx, int giveBookmark);

int playClockEventIntro(struct StoryContext *ctx);
int playClockEventBranch(struct StoryContext *ctx, int giveInk);

int playMirrorEventIntro(struct StoryContext *ctx, int isRevisit);
int playMirrorEventBranch(struct StoryContext *ctx, int option);

int playLuckEventIntro(struct StoryContext *ctx);
int playLuckEventDecline(struct StoryContext *ctx);
int playLuckEventSpinIntro(struct StoryContext *ctx);
int playLuckEventSpinOutcome(struct StoryContext *ctx, enum LuckOutcome outcome);

#endif
/* ==================== [Antigravity 生成 结束] ==================== */
