/* ==================== [Antigravity 生成] 终端 UI 与流式打字机接口 ==================== */
#ifndef UI_H
#define UI_H

#include "game.h"
#include "save.h"

/* ANSI 颜色与样式宏 */
#define C_RESET    "\x1b[0m"
#define C_BOLD     "\x1b[1m"
#define C_ITALIC   "\x1b[3m"
#define C_GRAY     "\x1b[90m"
#define C_RED      "\x1b[31m"
#define C_GREEN    "\x1b[32m"
#define C_YELLOW   "\x1b[33m"
#define C_CYAN     "\x1b[36m"
#define C_MAGENTA  "\x1b[35m"
#define C_WHITE    "\x1b[97m"

/* 72 列开放式水平分割线 */
#define LINE_STRONG "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
#define LINE_THIN   "────────────────────────────────────────────────────────────────────────"

/* 提示栏颜色级别（与纯文本分离，防截断乱码/串色） */
enum NoticeKind
{
    NOTICE_INFO = 0,
    NOTICE_OK = 1,
    NOTICE_WARN = 2,
    NOTICE_ERR = 3
};

/* 剧情台词样式 */
enum LineType
{
    LINE_NARRATION = 0, /* 旁白叙述 */
    LINE_RIDLEY = 1,    /* 蕾德莉对话 */
    LINE_WATARI = 2,    /* 渡里对话 */
    LINE_NPC = 3,       /* 星球角色对话（需提供 speaker 名称） */
    LINE_THOUGHT = 4,   /* 蕾德莉内心独白 */
    LINE_BREAK = 5      /* 场景过渡 · · · */
};

struct StoryLine
{
    enum LineType type;
    const char *speaker; /* 仅 LINE_NPC 时填写，其余为 NULL */
    const char *text;
};

/* 流式剧情播放上下文：支持多段条件剧本共享同一页，不强清屏 */
struct StoryContext
{
    const char *title;
    int physicalLines;   /* 当前页已累计估算的物理行数 */
    int skipChunk;       /* 当前片段是否开启即时显完（s 键触发） */
};

/* ---------- 基础终端与语速控制 ---------- */
void clearScreen(void);
void sleepMs(int ms);
int getSpeedMode(void);
void cycleSpeedMode(void);
const char *getSpeedName(void);

/* ---------- UTF-8 逐字打字机与流式剧情播放 ---------- */
void typePrint(const char *text, int instant);
void storyBegin(struct StoryContext *ctx, const char *title);
int storyPlayChunk(struct StoryContext *ctx, const struct StoryLine *lines, int count);
int storyWaitEnd(void);

/* ---------- 各类面板绘制 ---------- */
void drawStatusHeader(const struct GameState *state,
                      const char *screenName,
                      enum NoticeKind noticeKind,
                      const char *noticeText);

void drawTitleScreen(int hasSave,
                     const struct SaveSummary *summary,
                     enum NoticeKind noticeKind,
                     const char *noticeText);

void drawStartPlanetScreen(enum NoticeKind noticeKind, const char *noticeText);

void drawTravelScreen(const struct GameState *state,
                      enum NoticeKind noticeKind,
                      const char *noticeText);

void drawStarMap(const struct GameState *state);

void drawMarketScreen(const struct GameState *state,
                      enum NoticeKind noticeKind,
                      const char *noticeText);

/* 事件选项框上方资源摘要条（relatedGood < 0 表示不额外显示单项货物） */
void drawEventStatusBar(const struct GameState *state, int relatedGood);

void drawBirthdayScreen(const struct GameState *state,
                        enum NoticeKind noticeKind,
                        const char *noticeText);

void drawEndingSummary(int choice, int moneyAfterGift, unsigned int flags);

#endif
/* ==================== [Antigravity 生成 结束] ==================== */
