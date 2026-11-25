#include "game.h"
#include "save.h"

#include <complex.h>
#include <stdio.h>

/* ==================== [Antigravity 生成] 轻量单元测试框架与示例用例
 * ==================== */
#define TEST_SAVE_PATH "builds/test_save.txt"

static int g_passed = 0;
static int g_failed = 0;

#define CHECK(cond)                                                            \
  do                                                                           \
  {                                                                            \
    if (cond)                                                                  \
    {                                                                          \
      g_passed++;                                                              \
    }                                                                          \
    else                                                                       \
    {                                                                          \
      g_failed++;                                                              \
      printf("[FAIL] %s:%d: %s\n", __FILE__, __LINE__, #cond);                 \
    }                                                                          \
  } while (0)

/* 示例测试：验证 Antigravity 已写好的静态价格表与星图对称性 */
static void testStaticTables(void)
{
  int p = 0;
  int q = 0;
  int g = 0;
  int edgeCount = 0;

  /* 邻接矩阵必须对称且无自环，总计 6 条无向边 */
  for (p = 0; p < PLANET_COUNT; p++)
  {
    CHECK(canTravel(p, p) == 0);
    for (q = 0; q < PLANET_COUNT; q++)
    {
      CHECK(canTravel(p, q) == canTravel(q, p));
      if (p < q && canTravel(p, q))
      {
        edgeCount++;
      }
    }
  }
  CHECK(edgeCount == 6);

  /* 每站买卖错开：不存在同一站点对同一商品既买又卖 */
  for (p = 0; p < PLANET_COUNT; p++)
  {
    for (g = 0; g < GOOD_COUNT; g++)
    {
      CHECK(!(getBuyPrice(p, g) > 0 && getSellPrice(p, g) > 0));
    }
  }

  /* 校验几个关键价格 */
  CHECK(getBuyPrice(PLANET_BOOK, GOOD_FILM) == 20);
  CHECK(getSellPrice(PLANET_MIRROR, GOOD_FILM) == 45);
  CHECK(getSellPrice(PLANET_FLOWER, GOOD_BADGE) == 55);
  CHECK(getSellPlanetForGood(GOOD_INK) == PLANET_CLOCK);
}
/* ==================== [Antigravity 生成 结束] ==================== */

/* ==================== [TODO: 请你自己实现] Step 1 & Step 2 单元测试用例
 * ==================== */

static void testInitAndEconomy(void)
{
  struct GameState state = {0};
  int outNeighbors[PLANET_COUNT] = {-1, -1};
  int outGoods[GOOD_COUNT] = {0};

  CHECK(initGame(&state, PLANET_FLOWER) == 1);
  CHECK(state.phase == PHASE_TRAVEL);
  CHECK(state.planet == PLANET_FLOWER);

  CHECK(getCargoUsed(&state) == 0);
  state.cargo[GOOD_FILM] = 2;
  state.cargo[GOOD_TEA] = 1;
  CHECK(getCargoUsed(&state) == 3);

  CHECK(getNeighbors(PLANET_FLOWER, outNeighbors) == 2);
  CHECK(outNeighbors[0] == PLANET_BOOK);
  CHECK(outNeighbors[1] == PLANET_LUCK);
  CHECK(getNeighbors(PLANET_COUNT, outNeighbors) == 0);
  CHECK(getNeighbors(PLANET_FLOWER, NULL) == 0);

  CHECK(getSellGoodAt(PLANET_FLOWER) == GOOD_BADGE);
  CHECK(getSellGoodAt(PLANET_MIRROR) == GOOD_FILM);
  CHECK(getSellGoodAt(PLANET_COUNT) == -1);

  CHECK(getBuyGoodsAt(PLANET_MIRROR, outGoods) == 1);
  CHECK(outGoods[0] == GOOD_INK);
  CHECK(getBuyGoodsAt(PLANET_BOOK, outGoods) == 2);
  CHECK(outGoods[0] == GOOD_FILM && outGoods[1] == GOOD_INK);

  CHECK(initGame(&state, PLANET_FLOWER) == 1);

  CHECK(buyGood(&state, GOOD_TEA, 4) == 1);
  CHECK(state.cargo[GOOD_TEA] == 4);
  CHECK(state.money == 0);
  CHECK(buyGood(&state, GOOD_TEA, 1) == 0);
  CHECK(state.cargo[GOOD_TEA] == 4);

  CHECK(initGame(&state, PLANET_FLOWER));
  state.cargo[GOOD_BADGE] = 4;
  state.cargo[GOOD_TEA] = 1;
  CHECK(sellGood(&state, GOOD_TEA, 1) == 0);
  CHECK(state.cargo[GOOD_TEA] == 1);
  CHECK(sellGood(&state, GOOD_BADGE, 5) == 0);
  CHECK(state.cargo[GOOD_BADGE] == 4);
  CHECK(sellGood(&state, GOOD_BADGE, -1) == 0);
  CHECK(state.cargo[GOOD_BADGE] == 4);
  CHECK(buyGood(&state, GOOD_TEA, 1) == 0);
  CHECK(state.cargo[GOOD_TEA] == 1);
  CHECK(state.money == START_MONEY);
  CHECK(sellGood(&state, GOOD_BADGE, 4) == 1);
  CHECK(state.cargo[GOOD_BADGE] == 0);
  CHECK(state.money == 300);
}

static void testTravelAndFinishDay(void)
{
  struct GameState state = {0};
  CHECK(initGame(&state, PLANET_BOOK) == 1);
  CHECK(travelToPlanet(&state, PLANET_LUCK) == 0);
  CHECK(state.planet == PLANET_BOOK);
  CHECK(state.tripsLeft == TRIPS_PER_DAY);
  CHECK(travelToPlanet(&state, PLANET_MIRROR) == 1);
  CHECK(state.planet == PLANET_MIRROR);
  CHECK(state.tripsLeft == TRIPS_PER_DAY - 1);
  CHECK(travelToPlanet(&state, PLANET_CLOCK) == 1);
  CHECK(state.planet == PLANET_CLOCK);
  CHECK(state.tripsLeft == 0);
  CHECK(travelToPlanet(&state, PLANET_LUCK) == 0);
  CHECK(state.planet == PLANET_CLOCK);
  CHECK(finishDay(&state) == 1);
  CHECK(state.tripsLeft == 2);
  CHECK(state.day == 2);

  state.day = MAX_DAYS;
  CHECK(finishDay(&state) == 1);
  CHECK(state.day == 5);
  CHECK(state.tripsLeft == 0);
  CHECK(state.phase == PHASE_BIRTHDAY);

  int moneyBefore = -1;
  state.money = 719;
  CHECK(settleBirthdayGift(&state, GIFT_CHOCOLATE, &moneyBefore) == 0);
  CHECK(state.money == 719);
  CHECK(moneyBefore == -1);
  state.money = 720;
  CHECK(settleBirthdayGift(&state, GIFT_CHOCOLATE, &moneyBefore) == 1);
  CHECK(state.money == 0);
  CHECK(moneyBefore == 720);
  state.money = 200;
  CHECK(settleBirthdayGift(&state, GIFT_PAPER, &moneyBefore) == 1);
  CHECK(state.money == 50);
  CHECK(moneyBefore == 200);
  state.money = 80;
  CHECK(settleBirthdayGift(&state, GIFT_PAPER, &moneyBefore) == 1);
  CHECK(state.money == 0);
  CHECK(moneyBefore == 80);
  state.money = 0;
  CHECK(settleBirthdayGift(&state, GIFT_PAPER, &moneyBefore) == 1);
  CHECK(state.money == 0);
  CHECK(moneyBefore == 0);
}

static void testAllFiveEvents(void)
{
  /* [TODO: 请你自己实现 - Step 1]
   * 测试 5 个事件纯结算函数：
   * - 书之星：无茶(+5G+书签)、有茶(-1茶+55G+书签)、重复触发拒绝；
   * - 花之星：赠书签(+15G+扩仓7+丢书签)、保留书签(+10G+留书签+话题)；
   * - 钟之星：无墨(+5G+钥匙)、有墨(-1墨+70G+钥匙)；
   * - 镜之星：无胶卷暂缓离开(置 DEFERRED 不置 DONE 留钥匙)、有胶卷禁止暂缓、
   *           留星图(-1胶卷+80G+清钥匙与DEFERRED+置DONE与星图话题)；
   * -
   * 运之星：婉拒(+1G+DONE)、钱<50拒绝转盘、中奖(+30净赚)、未中未满仓(+1徽章)、
   *           未中已满仓(折现+25G, 净亏25G)。
   */
  struct GameState state = {0};
  CHECK(initGame(&state, PLANET_BOOK) == 1);
  CHECK(applyBookEvent(&state, 1) == 0);
  CHECK(state.money == 80);
  CHECK((state.flags & FLAG_ITEM_BOOKMARK) == 0u);
  CHECK((state.flags & FLAG_EV_BOOK_DONE) == 0u);
  CHECK(applyBookEvent(&state, 0) == 1);
  CHECK(state.money == 85);
  CHECK((state.flags & FLAG_ITEM_BOOKMARK) != 0u);
  CHECK((state.flags & FLAG_EV_BOOK_DONE) != 0u);
  CHECK(applyBookEvent(&state, 0) == 0);
  CHECK(state.money == 85);

  CHECK(initGame(&state, PLANET_BOOK) == 1);
  state.cargo[GOOD_TEA] = 1;
  CHECK(applyBookEvent(&state, 1) == 1);
  CHECK(state.cargo[GOOD_TEA] == 0);
  CHECK(state.money == 135);
  CHECK((state.flags & FLAG_ITEM_BOOKMARK) != 0u);
  CHECK((state.flags & FLAG_EV_BOOK_DONE) != 0u);

  CHECK(travelToPlanet(&state, PLANET_FLOWER) == 1);
  struct GameState give = state;
  struct GameState keep = state;
  CHECK(applyFlowerEvent(&give, 1) == 1);
  CHECK(give.money == 150);
  CHECK(give.cargoCap == EXPANDED_CARGO);
  CHECK((give.flags & FLAG_ITEM_BOOKMARK) == 0u);
  CHECK((give.flags & FLAG_TOPIC_BOOKMARK) == 0u);

  CHECK(applyFlowerEvent(&keep, 0) == 1);
  CHECK(keep.money == 145);
  CHECK(keep.cargoCap == BASE_CARGO);
  CHECK((keep.flags & FLAG_ITEM_BOOKMARK) != 0u);
  CHECK((keep.flags & FLAG_TOPIC_BOOKMARK) != 0u);
  CHECK((give.flags & FLAG_EV_FLOWER_DONE) != 0u);
  CHECK((keep.flags & FLAG_EV_FLOWER_DONE) != 0u);

  CHECK(initGame(&state, PLANET_CLOCK) == 1);
  give = state;
  give.cargo[GOOD_INK] = 1;
  keep = state;
  CHECK(applyClockEvent(&keep, 1) == 0);
  CHECK(keep.money == 80);
  CHECK((keep.flags & FLAG_ITEM_KEY) == 0u);
  CHECK((keep.flags & FLAG_EV_CLOCK_DONE) == 0u);
  CHECK(applyClockEvent(&keep, 0) == 1);
  CHECK(keep.money == 85);
  CHECK((keep.flags & FLAG_ITEM_KEY) != 0u);
  CHECK((keep.flags & FLAG_EV_CLOCK_DONE) != 0u);
  CHECK(applyClockEvent(&give, 1) == 1);
  CHECK(give.money == 150);
  CHECK((give.flags & FLAG_ITEM_KEY) != 0u);
  CHECK((give.flags & FLAG_EV_CLOCK_DONE) != 0u);
  CHECK(give.cargo[GOOD_INK] == 0);

  CHECK(travelToPlanet(&keep, PLANET_MIRROR) == 1);
  CHECK(applyMirrorEvent(&keep, 3) == 1);
  CHECK((keep.flags & FLAG_ITEM_KEY) != 0u);
  CHECK((keep.flags & FLAG_EV_MIRROR_DONE) == 0u);
  CHECK((keep.flags & FLAG_EV_MIRROR_DEFERRED) != 0u);
  keep.cargo[GOOD_FILM] = 1;
  CHECK(applyMirrorEvent(&keep, 3) == 0);
  CHECK(applyMirrorEvent(&keep, 2) == 1);
  CHECK(keep.money == 165);
  CHECK(keep.cargo[GOOD_FILM] == 0);
  CHECK((keep.flags & FLAG_ITEM_KEY) == 0u);
  CHECK((keep.flags & FLAG_EV_MIRROR_DEFERRED) == 0u);
  CHECK((keep.flags & FLAG_EV_MIRROR_DONE) != 0u);
  CHECK((keep.flags & FLAG_TOPIC_STARMAP) != 0u);

  enum LuckOutcome outcome = LUCK_REFUND;
  CHECK(initGame(&state, PLANET_LUCK) == 1);
  CHECK(applyLuckEvent(&state, 0, 0, &outcome) == 1);
  CHECK(state.money == 81);
  CHECK(outcome == LUCK_DECLINED);
  CHECK((state.flags & FLAG_EV_LUCK_DONE) != 0u);
  CHECK(initGame(&state, PLANET_LUCK) == 1);
  CHECK(applyLuckEvent(&state, 1, 1, &outcome) == 1);
  CHECK(state.money == 110);
  CHECK(outcome == LUCK_WIN);
  CHECK((state.flags & FLAG_EV_LUCK_DONE) != 0u);
  CHECK(initGame(&state, PLANET_LUCK) == 1);
  CHECK(applyLuckEvent(&state, 1, 0, &outcome) == 1);
  CHECK(state.money == 30);
  CHECK(outcome == LUCK_BADGE);
  CHECK(state.cargo[GOOD_BADGE] == 1);
  CHECK((state.flags & FLAG_EV_LUCK_DONE) != 0u);
  CHECK(initGame(&state, PLANET_LUCK) == 1);
  state.cargo[GOOD_FILM] = 5;
  CHECK(applyLuckEvent(&state, 1, 0, &outcome) == 1);
  CHECK(state.money == 55);
  CHECK(outcome == LUCK_REFUND);
  CHECK((state.flags & FLAG_EV_LUCK_DONE) != 0u);
  CHECK(initGame(&state, PLANET_LUCK) == 1);
  state.money = 49;
  CHECK(applyLuckEvent(&state, 1, 0, &outcome) == 0);
  CHECK(outcome == LUCK_REFUND);
  CHECK((state.flags & FLAG_EV_LUCK_DONE) == 0u);
}

static void testValidateGameState(void)
{
  /* [TODO: 请你自己实现 - Step 1]
   * 测试 validateGameState 放行合法状态并拦截全部非法组合：
   * - PHASE_TRAVEL 时 tripsLeft == 0；PHASE_BIRTHDAY 时 day != 5 或 tripsLeft
   * != 0；
   * - cargo 单个超限、总和超限、cargo[0]=2147483647 && cargo[1]=1 防溢出；
   * - 书签链矛盾（未做书之星却有书签、扩仓 7 却同时持有书签或话题）；
   * - 钥匙链矛盾（已完成镜之星却仍持钥匙或仍带
   * DEFERRED、未做钟之星却有星图话题）；
   * - flags 含未知高位 (1u << 10)。
   */
}

static void testSaveAndLoad(void)
{
  /* [TODO: 请你自己实现 - Step 2]
   * 使用 TEST_SAVE_PATH（绝不碰正式 save.txt）：
   * - 测试正常 saveGame -> loadGame 全字段一致（覆盖 PHASE_TRAVEL 与
   * PHASE_BIRTHDAY）；
   * - 测试 peekSaveSummary 与 hasValidSave；
   * - 测试结束调用 remove(TEST_SAVE_PATH) 清理临时文件。
   */
}

static void testCorruptedSaves(void)
{
  /* [TODO: 请你自己实现 - Step 2]
   * 向 TEST_SAVE_PATH 写入各类坏档并验证 loadGame 返回 0 且不污染原 struct
   * GameState：
   * - 错误魔数版本号；缺行；末尾多余第 10 行；
   * - 行尾垃圾（如 "money 100abc"）；负数 flags（"flags -1"）；超大整数溢出；
   * - 语义矛盾档（如 day=1 phase=1 或 扩仓7+保留书签话题）；
   * - 测试结束调用 remove(TEST_SAVE_PATH) 清理。
   */
}

/* ==================== [Antigravity 生成] 测试主入口 ==================== */
int main(void)
{
  testStaticTables();
  testInitAndEconomy();
  testTravelAndFinishDay();
  testAllFiveEvents();
  testValidateGameState();
  testSaveAndLoad();
  testCorruptedSaves();

  printf("========================================\n");
  printf("测试完成: 通过 %d 项, 失败 %d 项\n", g_passed, g_failed);
  printf("========================================\n");
  return g_failed == 0 ? 0 : 1;
}
/* ==================== [Antigravity 生成 结束] ==================== */
