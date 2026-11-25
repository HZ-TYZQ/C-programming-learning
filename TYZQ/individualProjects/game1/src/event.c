/*--------------- <generated with GPT-6> ------------------*/
#include "event.h"

#include "game.h"
#include "input.h"
#include "story.h"
#include "ui.h"

#include <stdio.h>
#include <stdlib.h>

/* ==================== [Antigravity 生成 - 参考示例] 书之星事件交互模板 ==================== */
/* 说明：展示一个完整事件的 4 步交互模板（播开场 -> 显资源与选项并拦截不可选项 ->
 * 调用 game.c 的纯结算函数 -> 续播分支与绿色结算提示）。
 * 其余 4 个事件（花/钟/镜/运）请对照这个模式自己实现。
 */
static int runBookEvent(struct GameState *state)
{
  struct StoryContext ctx;
  int hasTea = (state->cargo[GOOD_TEA] > 0);
  int choice = 0;

  if (!playBookEventIntro(&ctx))
  {
    return 0;
  }

  drawEventStatusBar(state, GOOD_TEA);
  printf("  " C_BOLD C_YELLOW "[1]" C_RESET " 整理书页 (+5 G, 获赠干花书签)\n");
  if (hasTea)
  {
    printf(
      "  " C_BOLD C_YELLOW "[2]" C_RESET " 递上一份安神花茶 (-1 安神花茶, +55 G, 获赠干花书签)\n");
  }
  else
  {
    printf("  " C_GRAY "[2] 递上一份安神花茶 [需安神花茶 x1]\n" C_RESET);
  }

  while (1)
  {
    if (!readIntInRange(
          "\n"
          " 请选择 [1-2]: ",
          1,
          2,
          &choice))
    {
      return 0;
    }
    if (choice == 2 && !hasTea)
    {
      printf(" " C_RED "当前未持有安神花茶, 无法选择该项.\n" C_RESET);
      continue;
    }
    break;
  }

  if (!applyBookEvent(state, choice == 2 ? 1 : 0))
  {
    return 1;
  }

  printf("\n");
  if (!playBookEventBranch(&ctx, choice == 2 ? 1 : 0))
  {
    return 0;
  }

  printf(
    "\n"
    " " C_GREEN "[结算] %s, 获得信物 [干花书签].\n" C_RESET,
    choice == 2 ? "-1 安神花茶, 资金 +55 G" : "资金 +5 G");
  return waitEnter(" 按 Enter 进入当地市场...");
}
/* ==================== [Antigravity 生成 结束] ==================== */
/*------------------------ <END> -------------------------*/

/* ==================== [TODO: 请你自己实现] Step 5 其余 4 个事件与总调度 ==================== */

static int runFlowerEvent(struct GameState *state)
{
  struct StoryContext ctx;
  int choice;

  if (!playFlowerEventIntro(&ctx))
  {
    return 0;
  }

  drawEventStatusBar(state, -1);
  printf("  " C_BOLD C_YELLOW "[1]" C_RESET "赠出干花书签 (+15 G, 货舱 5 格 -> 7 格)\n");
  printf("  " C_BOLD C_YELLOW "[2]" C_RESET "保留干花书签 (+10 G, 解锁温泉话题[书签背面的花名])\n");

  if (!readIntInRange("请选择[1-2]: ", 1, 2, &choice))
  {
    return 0;
  }

  int giveBookmark = (choice == 1);

  if (!applyFlowerEvent(state, giveBookmark))
  {
    return 1;
  }
  if (!playFlowerEventBranch(&ctx, giveBookmark))
  {
    return 0;
  }

  printf(
    "\n"
    " " C_GREEN "[结算] %s.\n" C_RESET,
    choice == 2 ? "资金 +10 G, 解锁温泉话题" : "资金 +15 G, 货舱扩容至7格");

  return waitEnter(" 按 Enter 进入当地市场...");
}

static int runClockEvent(struct GameState *state)
{
  struct StoryContext ctx;
  int hasInk = (state->cargo[GOOD_INK] > 0);
  int choice = 0;

  if (!playClockEventIntro(&ctx))
  {
    return 0;
  }

  drawEventStatusBar(state, GOOD_INK);
  printf("  " C_BOLD C_YELLOW "[1]" C_RESET " 擦拭发条 (+5 G, 获赠黄铜钥匙)\n");
  if (hasInk)
  {
    printf(
      "  " C_BOLD C_YELLOW "[2]" C_RESET
      " 用星光墨水重绘星象盘 (-1 星光墨水, +70 G, 获赠黄铜钥匙)\n");
  }
  else
  {
    printf("  " C_GRAY "[2] 用星光墨水重绘星象盘 [需星光墨水 x1]\n" C_RESET);
  }

  while (1)
  {
    if (!readIntInRange(
          "\n"
          " 请选择 [1-2]: ",
          1,
          2,
          &choice))
    {
      return 0;
    }
    if (choice == 2 && !hasInk)
    {
      printf(" " C_RED "当前未持有星光墨水, 无法选择该项.\n" C_RESET);
      continue;
    }
    break;
  }

  if (!applyClockEvent(state, choice == 2 ? 1 : 0))
  {
    return 1;
  }

  printf("\n");
  if (!playClockEventBranch(&ctx, choice == 2 ? 1 : 0))
  {
    return 0;
  }

  printf(
    "\n"
    " " C_GREEN "[结算] %s, 获得信物 [黄铜钥匙].\n" C_RESET,
    choice == 2 ? "-1 星光墨水, 资金 +70 G" : "资金 +5 G");
  return waitEnter(" 按 Enter 进入当地市场...");
}

static int runMirrorEvent(struct GameState *state)
{
  struct StoryContext ctx;
  int isRevisit = state->flags & FLAG_EV_MIRROR_DEFERRED;
  int hasFilm = (state->cargo[GOOD_FILM] > 0);
  int choice;

  if (!playMirrorEventIntro(&ctx, isRevisit))
  {
    return 0;
  }

  drawEventStatusBar(state, GOOD_FILM);

  printf("  " C_BOLD C_YELLOW "[1]" C_RESET " 常规启动(交出黄铜钥匙, +15 G)\n");
  if (hasFilm)
  {
    printf(
      "  " C_BOLD C_YELLOW "[2]" C_RESET
      "留下生日星图(交出钥匙与一卷胶卷, +80G, 解锁话题[生日那天的星空])\n");
  }
  else
  {
    printf("  " C_GRAY "[2] 留下生日星图 [需微缩胶卷 x1]\n" C_RESET);
  }
  if (!hasFilm)
  {
    printf("  " C_BOLD C_YELLOW "[3]" C_RESET "暂缓离开\n");
  }
  else if (hasFilm)
  {
    printf("  " C_GRAY "[3] 暂缓离开(当前已有胶卷, 无法选择)\n" C_RESET);
  }

  while (1)
  {
    if (!readIntInRange(
          "\n"
          " 请选择 [1-3]: ",
          1,
          3,
          &choice))
    {
      return 0;
    }
    if (choice == 2 && !hasFilm)
    {
      printf(" " C_RED "当前未持有微缩胶卷, 无法选择该项.\n" C_RESET);
      continue;
    }
    else if (choice == 3 && hasFilm)
    {
      printf(" " C_RED "已持有微缩胶卷, 无法暂缓离开.\n" C_RESET);
      continue;
    }
    break;
  }

  if (!applyMirrorEvent(state, choice))
  {
    return 1;
  }

  if (!playMirrorEventBranch(&ctx, choice))
  {
    return 0;
  }

  switch (choice)
  {
  case 1:
    printf(C_GREEN "[结算] 交出黄铜钥匙, 资金 +15 G.\n" C_RESET);
    break;
  case 2:
    printf(C_GREEN "[结算] 交出钥匙和 1 卷胶卷, 资金 +80 G, 解锁温泉话题.\n" C_RESET);
    break;
  case 3:
    printf(C_YELLOW "[结算] 保留黄铜钥匙, 带上胶卷后可以再来.\n" C_RESET);
    break;
  }

  return waitEnter(" 按 Enter 进入当地市场...");
}

static int runLuckEvent(struct GameState *state)
{
  struct StoryContext ctx;
  int choice;
  enum LuckOutcome outcome;

  if (!playLuckEventIntro(&ctx))
  {
    return 0;
  }

  drawEventStatusBar(state, GOOD_BADGE);

  printf("  " C_BOLD C_YELLOW "[1]" C_RESET " 婉拒(+1 G)\n");
  if (state->money >= 50)
  {
    printf(
      "  " C_BOLD C_YELLOW "[2]" C_RESET "支付 50 G 转动一次轮盘(仓库已满时商品奖励折现 25 G)\n");
  }
  else
  {
    printf("  " C_GRAY "[2] 转动一次轮盘 [需星币 >= 50 G]\n" C_RESET);
  }

  while (1)
  {
    if (!readIntInRange(
          "\n"
          " 请选择 [1-2]: ",
          1,
          2,
          &choice))
    {
      return 0;
    }
    if (choice == 2 && state->money < 50)
    {
      printf(" " C_RED "当前未持有足够星币, 无法选择该项.\n" C_RESET);
      continue;
    }
    break;
  }
  if (choice == 1)
  {
    if (!applyLuckEvent(state, 0, 0, &outcome))
    {
      return 1;
    }

    if (!playLuckEventDecline(&ctx))
    {
      return 0;
    }
  }
  else
  {
    if (!playLuckEventSpinIntro(&ctx))
    {
      return 0;
    }

    int rollWin = rand() % 2;

    if (!applyLuckEvent(state, 1, rollWin, &outcome))
    {
      return 1;
    }

    if (!playLuckEventSpinOutcome(&ctx, outcome))
    {
      return 0;
    }
  }

  switch (outcome)
  {
  case LUCK_WIN:
    printf(C_GREEN "[结算] 净赚 30 G(资金 +30 G).\n" C_RESET);
    break;
  case LUCK_BADGE:
    printf(C_GREEN "[结算] 获得幸运徽章(资金 -50 G).\n" C_RESET);
    break;
  case LUCK_REFUND:
    printf(C_YELLOW "[结算] 背包已满, 徽章折现 25 G(资金 -25 G).\n" C_RESET);
    break;
  case LUCK_DECLINED:
    printf(C_YELLOW "[结算] 捡到一枚星币(资金 +1 G).\n" C_RESET);
    break;
  }

  return waitEnter(" 按 Enter 进入当地市场...");
}

int runArrivalEvent(struct GameState *state)
{
  if (!canTriggerArrivalEvent(state))
  {
    return 1;
  }

  if (state->planet == PLANET_BOOK)
  {
    return runBookEvent(state);
  }
  else if (state->planet == PLANET_FLOWER)
  {
    return runFlowerEvent(state);
  }
  else if (state->planet == PLANET_CLOCK)
  {
    return runClockEvent(state);
  }
  else if (state->planet == PLANET_MIRROR)
  {
    return runMirrorEvent(state);
  }
  else if (state->planet == PLANET_LUCK)
  {
    if (rand() % 2 == 0)
    {
      return runLuckEvent(state);
    }
    else
    {
      return 1;
    }
  }
  return 1;
}
