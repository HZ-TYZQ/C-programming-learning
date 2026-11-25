#include "game.h"

#include <complex.h>
#include <limits.h>
#include <stddef.h>

/* ==================== [Antigravity 生成] 世界静态数据表与基础只读查询
 * ==================== */
static const char *const PLANET_NAMES[PLANET_COUNT] = {
    "书之星", "花之星", "钟之星", "镜之星", "运之星"};

static const char *const PLANET_INTROS[PLANET_COUNT] = {
    "图书馆高耸入云, 馆员低价出售胶卷与墨水, 高价收购安神花茶.",
    "空中花海四季不败, 低价出售安神花茶, 高价收购幸运徽章.",
    "巨型钟楼滴答作响, 低价出售精密齿轮, 高价收购星光墨水.",
    "群山架满观测反射镜, 低价出售星光墨水, 高价收购微缩胶卷.",
    "霓虹与骰子塔林立, 低价出售幸运徽章, 高价收购精密齿轮."};

static const char *const GOOD_NAMES[GOOD_COUNT] = {
    "微缩胶卷", "安神花茶", "精密齿轮", "星光墨水", "幸运徽章"};

/* 玩家向当地商店购入单价（0 表示不出售） */
static const int BUY_PRICE[PLANET_COUNT][GOOD_COUNT] = {
    /* 胶卷  花茶  齿轮  墨水  徽章 */
    {20, 0, 0, 30, 0}, /* 0 书之星 */
    {0, 20, 0, 0, 0},  /* 1 花之星 */
    {0, 0, 25, 0, 0},  /* 2 钟之星 */
    {0, 0, 0, 25, 0},  /* 3 镜之星 */
    {0, 0, 0, 0, 30}   /* 4 运之星 */
};

/* 玩家向当地商店卖出单价（0 表示不收购） */
static const int SELL_PRICE[PLANET_COUNT][GOOD_COUNT] = {
    /* 胶卷  花茶  齿轮  墨水  徽章 */
    {0, 45, 0, 0, 0}, /* 0 书之星 */
    {0, 0, 0, 0, 55}, /* 1 花之星 */
    {0, 0, 0, 50, 0}, /* 2 钟之星 */
    {45, 0, 0, 0, 0}, /* 3 镜之星 */
    {0, 0, 50, 0, 0}  /* 4 运之星 */
};

/* 6 条双向航线：主环 0-3-2-4-1-0 + 捷径 0-2 */
static const int ADJACENCY[PLANET_COUNT][PLANET_COUNT] = {
    /* 书 花 钟 镜 运 */
    {0, 1, 1, 1, 0}, /* 0 书之星 */
    {1, 0, 0, 0, 1}, /* 1 花之星 */
    {1, 0, 0, 1, 1}, /* 2 钟之星 */
    {1, 0, 1, 0, 0}, /* 3 镜之星 */
    {0, 1, 1, 0, 0}  /* 4 运之星 */
};

const char *getPlanetName(int planet)
{
  if (planet < 0 || planet >= PLANET_COUNT)
  {
    return "未知星球";
  }
  return PLANET_NAMES[planet];
}

const char *getPlanetIntro(int planet)
{
  if (planet < 0 || planet >= PLANET_COUNT)
  {
    return "";
  }
  return PLANET_INTROS[planet];
}

const char *getGoodName(int good)
{
  if (good < 0 || good >= GOOD_COUNT)
  {
    return "未知商品";
  }
  return GOOD_NAMES[good];
}

int getBuyPrice(int planet, int good)
{
  if (planet < 0 || planet >= PLANET_COUNT || good < 0 || good >= GOOD_COUNT)
  {
    return 0;
  }
  return BUY_PRICE[planet][good];
}

int getSellPrice(int planet, int good)
{
  if (planet < 0 || planet >= PLANET_COUNT || good < 0 || good >= GOOD_COUNT)
  {
    return 0;
  }
  return SELL_PRICE[planet][good];
}

int canTravel(int fromPlanet, int toPlanet)
{
  if (fromPlanet < 0 || fromPlanet >= PLANET_COUNT || toPlanet < 0 ||
      toPlanet >= PLANET_COUNT)
  {
    return 0;
  }
  return ADJACENCY[fromPlanet][toPlanet];
}

int getSellPlanetForGood(int good)
{
  int p = 0;

  if (good < 0 || good >= GOOD_COUNT)
  {
    return -1;
  }
  for (p = 0; p < PLANET_COUNT; p++)
  {
    if (SELL_PRICE[p][good] > 0)
    {
      return p;
    }
  }
  return -1;
}
/* ==================== [Antigravity 生成 结束] ==================== */

/* ==================== [TODO: 请你自己实现] Step 1 核心游戏逻辑
 * ==================== */

int initGame(struct GameState *state, int startPlanet)
{
  if (state == NULL || startPlanet < 0 || startPlanet > PLANET_COUNT - 1)
  {
    return 0;
  }

  state->day = 1;
  state->phase = PHASE_TRAVEL;
  state->planet = startPlanet;
  state->tripsLeft = TRIPS_PER_DAY;
  state->money = START_MONEY;
  state->cargoCap = BASE_CARGO;

  for (int i = 0; i < GOOD_COUNT; i++)
  {
    state->cargo[i] = 0;
  }

  state->flags = 0u;

  return 1;
}

int getCargoUsed(const struct GameState *state)
{
  int cargoCount = 0;

  if (state == NULL)
  {
    return 0;
  }

  for (int i = 0; i < GOOD_COUNT; i++)
  {
    cargoCount += state->cargo[i];
  }

  return cargoCount;
}

int getNeighbors(int planet, int outNeighbors[PLANET_COUNT])
{
  int count = 0;

  if (planet < 0 || planet > PLANET_COUNT - 1 || outNeighbors == NULL)
  {
    return 0;
  }

  for (int i = 0; i < PLANET_COUNT; i++)
  {
    if (canTravel(planet, i) == 1)
    {
      outNeighbors[count] = i;
      count++;
    }
  }
  return count;
}

int getSellGoodAt(int planet)
{
  for (int i = 0; i < GOOD_COUNT; i++)
  {
    if (getSellPrice(planet, i) > 0)
    {
      return i;
    }
  }

  return -1;
}

int getBuyGoodsAt(int planet, int outGoods[GOOD_COUNT])
{
  int count = 0;

  if (planet < 0 || planet > PLANET_COUNT - 1 || outGoods == NULL)
  {
    return 0;
  }

  for (int i = 0; i < GOOD_COUNT; i++)
  {
    if (getBuyPrice(planet, i) > 0)
    {
      outGoods[count] = i;
      count++;
    }
  }
  return count;
}

int buyGood(struct GameState *state, int good, int qty)
{
  if (state == NULL || qty <= 0 || state->phase != PHASE_TRAVEL)
  {
    return 0;
  }
  if (getBuyPrice(state->planet, good) <= 0)
  {
    return 0;
  }
  if (qty > state->cargoCap - getCargoUsed(state))
  {
    return 0;
  }
  if (qty > state->money / getBuyPrice(state->planet, good))
  {
    return 0;
  }

  state->money -= getBuyPrice(state->planet, good) * qty;
  state->cargo[good] += qty;

  return 1;
}

int sellGood(struct GameState *state, int good, int qty)
{
  if (state == NULL || qty <= 0 || state->phase != PHASE_TRAVEL || good < 0 ||
      good > GOOD_COUNT - 1)
  {
    return 0;
  }

  int price = getSellPrice(state->planet, good);

  if (price <= 0)
  {
    return 0;
  }

  if (qty > state->cargo[good])
  {
    return 0;
  }

  if (qty > (INT_MAX - state->money) / price)
  {
    return 0;
  }

  state->cargo[good] -= qty;
  state->money += price * qty;

  return 1;
}

int travelToPlanet(struct GameState *state, int destPlanet)
{
  if (state == NULL || state->phase != PHASE_TRAVEL || state->tripsLeft <= 0)
  {
    return 0;
  }
  if (canTravel(state->planet, destPlanet) != 1)
  {
    return 0;
  }

  state->planet = destPlanet;
  state->tripsLeft -= 1;

  return 1;
}

int finishDay(struct GameState *state)
{
  if (state == NULL || state->phase != PHASE_TRAVEL)
  {
    return 0;
  }
  if (state->day < MAX_DAYS)
  {
    state->day += 1;
    state->tripsLeft = TRIPS_PER_DAY;
    state->phase = PHASE_TRAVEL;
  }
  else
  {
    state->tripsLeft = 0;
    state->phase = PHASE_BIRTHDAY;
  }

  return 1;
}

int settleBirthdayGift(struct GameState *state, int choice, int *outMoneyBefore)
{
  int cost;
  if (state == NULL || state->phase != PHASE_BIRTHDAY)
  {
    return 0;
  }

  if (choice == GIFT_CHOCOLATE)
  {
    if (state->money < TARGET_MONEY)
    {
      return 0;
    }
    else
    {
      cost = TARGET_MONEY;
    }

    if (outMoneyBefore != NULL)
    {
      *outMoneyBefore = state->money;
    }
  }
  else if (choice == GIFT_PAPER)
  {
    if (outMoneyBefore != NULL)
    {
      *outMoneyBefore = state->money;
    }

    if (state->money >= PAPER_PRICE)
    {
      cost = PAPER_PRICE;
    }
    else
    {
      cost = state->money;
    }
  }
  else
  {
    return 0;
  }

  state->money -= cost;

  return 1;
}

int canTriggerArrivalEvent(const struct GameState *state)
{
  if (state == NULL)
  {
    return 0;
  }

  unsigned int flags = state->flags;

  switch (state->planet)
  {
  case PLANET_BOOK:
    if (!(flags & FLAG_EV_BOOK_DONE))
    {
      return 1;
    }
    break;
  case PLANET_CLOCK:
    if (!(flags & FLAG_EV_CLOCK_DONE))
    {
      return 1;
    }
    break;
  case PLANET_LUCK:
    if (!(flags & FLAG_EV_LUCK_DONE))
    {
      return 1;
    }
    break;
  case PLANET_FLOWER:
    if ((flags & FLAG_ITEM_BOOKMARK) && !(flags & FLAG_EV_FLOWER_DONE))
    {
      return 1;
    }
    break;
  case PLANET_MIRROR:
    if ((flags & FLAG_ITEM_KEY) && !(flags & FLAG_EV_MIRROR_DONE))
    {
      return 1;
    }
    break;
  }

  return 0;
}

int applyBookEvent(struct GameState *state, int giveTea)
{
  if (state == NULL || state->planet != PLANET_BOOK ||
      canTriggerArrivalEvent(state) == 0)
  {
    return 0;
  }

  if (giveTea)
  {
    if (state->cargo[GOOD_TEA] >= 1)
    {
      if (state->money > INT_MAX - 55)
      {
        return 0;
      }
      state->cargo[GOOD_TEA] -= 1;
      state->money += 55;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    if (state->money > INT_MAX - 5)
    {
      return 0;
    }
    state->money += 5;
  }

  state->flags |= FLAG_ITEM_BOOKMARK | FLAG_EV_BOOK_DONE;

  return 1;
}

int applyFlowerEvent(struct GameState *state, int giveBookmark)
{
  if (state == NULL || state->planet != PLANET_FLOWER ||
      canTriggerArrivalEvent(state) == 0)
  {
    return 0;
  }

  if (giveBookmark)
  {

    if (state->money > INT_MAX - 15)
    {
      return 0;
    }

    state->money += 15;
    state->flags &= ~FLAG_ITEM_BOOKMARK;
    state->cargoCap = EXPANDED_CARGO;
  }
  else
  {
    if (state->money > INT_MAX - 10)
    {
      return 0;
    }
    state->money += 10;

    state->flags |= FLAG_TOPIC_BOOKMARK;
  }

  state->flags |= FLAG_EV_FLOWER_DONE;

  return 1;
}

int applyClockEvent(struct GameState *state, int giveInk)
{
  if (state == NULL || state->planet != PLANET_CLOCK ||
      canTriggerArrivalEvent(state) == 0)
  {
    return 0;
  }

  if (giveInk)
  {
    if (state->cargo[GOOD_INK] >= 1)
    {
      if (state->money > INT_MAX - 70)
      {
        return 0;
      }
      state->cargo[GOOD_INK] -= 1;
      state->money += 70;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    if (state->money > INT_MAX - 5)
    {
      return 0;
    }
    state->money += 5;
  }

  state->flags |= FLAG_ITEM_KEY | FLAG_EV_CLOCK_DONE;

  return 1;
}

int applyMirrorEvent(struct GameState *state, int option)
{
  if (state == NULL || state->planet != PLANET_MIRROR ||
      canTriggerArrivalEvent(state) == 0)
  {
    return 0;
  }
  if (option == 1)
  {
    if (state->money > INT_MAX - 15)
    {
      return 0;
    }

    state->money += 15;
    state->flags &= ~(FLAG_ITEM_KEY | FLAG_EV_MIRROR_DEFERRED);
    state->flags |= FLAG_EV_MIRROR_DONE;
  }
  else if (option == 2)
  {
    if (state->cargo[GOOD_FILM] < 1)
    {
      return 0;
    }
    if (state->money > INT_MAX - 80)
    {
      return 0;
    }

    state->cargo[GOOD_FILM] -= 1;
    state->money += 80;

    state->flags &= ~(FLAG_ITEM_KEY | FLAG_EV_MIRROR_DEFERRED);
    state->flags |= FLAG_EV_MIRROR_DONE | FLAG_TOPIC_STARMAP;
  }
  else if (option == 3)
  {
    if (state->cargo[GOOD_FILM] != 0)
    {
      return 0;
    }

    state->flags |= FLAG_EV_MIRROR_DEFERRED;
  }
  else
  {
    return 0;
  }

  return 1;
}

int applyLuckEvent(struct GameState *state, int gamble, int rollWin,
                   enum LuckOutcome *outOutcome)
{
  if (state == NULL || state->planet != PLANET_LUCK ||
      canTriggerArrivalEvent(state) == 0 || outOutcome == NULL)
  {
    return 0;
  }

  if (gamble == 0)
  {
    if (state->money > INT_MAX - 1)
    {
      return 0;
    }

    state->money += 1;
    *outOutcome = LUCK_DECLINED;
  }
  else if (gamble != 0)
  {
    if (state->money < 50)
    {
      return 0;
    }

    if (rollWin != 0)
    {
      if (state->money > INT_MAX - 30)
      {
        return 0;
      }

      state->money += 30;
      *outOutcome = LUCK_WIN;
    }
    else if (rollWin == 0 && getCargoUsed(state) < state->cargoCap)
    {
      state->money -= 50;
      state->cargo[GOOD_BADGE] += 1;
      *outOutcome = LUCK_BADGE;
    }
    else
    {
      state->money -= 25;
      *outOutcome = LUCK_REFUND;
    }
  }

  state->flags |= FLAG_EV_LUCK_DONE;
  return 1;
}

int validateGameState(const struct GameState *state)
{
  if (state == NULL)
  {
    return 0;
  }

  if (state->phase == PHASE_TRAVEL)
  {
    if (state->day < 1 || state->day > MAX_DAYS || state->tripsLeft < 1 ||
        state->tripsLeft > TRIPS_PER_DAY)
    {
      return 0;
    }
  }
  else if (state->phase == PHASE_BIRTHDAY)
  {
    if (state->day != MAX_DAYS || state->tripsLeft != 0)
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }

  if (state->planet < 0 || state->planet > PLANET_COUNT - 1 ||
      state->money < 0 ||
      (state->cargoCap != BASE_CARGO && state->cargoCap != EXPANDED_CARGO) ||
      (state->flags & ~FLAG_ALL_VALID) != 0u)
  {
    return 0;
  }

  int used = 0;

  for (int i = 0; i < GOOD_COUNT; i++)
  {
    if (state->cargo[i] < 0 || state->cargo[i] > state->cargoCap - used)
    {
      return 0;
    }

    used += state->cargo[i];
  }

  if (!(state->flags & FLAG_EV_BOOK_DONE))
  {
    if ((state->flags & FLAG_ITEM_BOOKMARK) ||
        (state->flags & FLAG_EV_FLOWER_DONE) ||
        (state->flags & FLAG_TOPIC_BOOKMARK) || (state->cargoCap != BASE_CARGO))
    {
      return 0;
    }
  }
  else if ((state->flags & FLAG_EV_BOOK_DONE) &&
           !(state->flags & FLAG_EV_FLOWER_DONE))
  {
    if (!(state->flags & FLAG_ITEM_BOOKMARK) ||
        (state->flags & FLAG_TOPIC_BOOKMARK) || (state->cargoCap != BASE_CARGO))
    {
      return 0;
    }
  }
  else if ((state->flags & FLAG_EV_BOOK_DONE) &&
           (state->flags & FLAG_EV_FLOWER_DONE) &&
           !(state->flags & FLAG_ITEM_BOOKMARK))
  {
    if ((state->flags & FLAG_ITEM_BOOKMARK) ||
        (state->flags & FLAG_TOPIC_BOOKMARK) ||
        (state->cargoCap != EXPANDED_CARGO))
    {
      return 0;
    }
  }
  else if ((state->flags & FLAG_EV_BOOK_DONE) &&
           (state->flags & FLAG_EV_FLOWER_DONE) &&
           (state->flags & FLAG_ITEM_BOOKMARK))
  {
    if (!(state->flags & FLAG_ITEM_BOOKMARK) ||
        !(state->flags & FLAG_TOPIC_BOOKMARK) ||
        (state->cargoCap != BASE_CARGO))
    {
      return 0;
    }
  }

  if (!(state->flags & FLAG_EV_CLOCK_DONE))
  {
    if ((state->flags & FLAG_EV_MIRROR_DONE) ||
        (state->flags & FLAG_ITEM_KEY) ||
        (state->flags & FLAG_EV_MIRROR_DEFERRED) ||
        (state->flags & FLAG_TOPIC_STARMAP))
    {
      return 0;
    }
  }
  else if ((state->flags & FLAG_EV_CLOCK_DONE) &&
           !(state->flags & FLAG_EV_MIRROR_DONE))
  {
    if (!(state->flags & FLAG_ITEM_KEY) || (state->flags & FLAG_TOPIC_STARMAP))
    {
      return 0;
    }
  }
  else if ((state->flags & FLAG_EV_CLOCK_DONE) &&
           (state->flags & FLAG_EV_MIRROR_DONE))
  {
    if ((state->flags & FLAG_ITEM_KEY) ||
        (state->flags & FLAG_EV_MIRROR_DEFERRED))
    {
      return 0;
    }
  }

  return 1;
}
