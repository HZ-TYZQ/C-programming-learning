/* ==================== [Antigravity 生成] 核心数据模型与规则接口 ==================== */
#ifndef GAME_H
#define GAME_H

#define PLANET_COUNT   5
#define GOOD_COUNT     5
#define MAX_DAYS       5
#define TRIPS_PER_DAY  2
#define START_MONEY    80
#define TARGET_MONEY   720
#define PAPER_PRICE    150
#define BASE_CARGO     5
#define EXPANDED_CARGO 7

enum PlanetId
{
    PLANET_BOOK = 0,    /* 书之星 */
    PLANET_FLOWER = 1,  /* 花之星 */
    PLANET_CLOCK = 2,   /* 钟之星 */
    PLANET_MIRROR = 3,  /* 镜之星 */
    PLANET_LUCK = 4     /* 运之星 */
};

enum GoodId
{
    GOOD_FILM = 0,      /* 微缩胶卷 */
    GOOD_TEA = 1,       /* 安神花茶 */
    GOOD_GEAR = 2,      /* 精密齿轮 */
    GOOD_INK = 3,       /* 星光墨水 */
    GOOD_BADGE = 4      /* 幸运徽章 */
};

enum GamePhase
{
    PHASE_TRAVEL = 0,   /* 每日选星与跑商阶段 */
    PHASE_BIRTHDAY = 1  /* 第五天温泉后，待选生日礼物阶段 */
};

enum GiftChoice
{
    GIFT_CHOCOLATE = 1, /* 甜之星巧克力 720 G */
    GIFT_PAPER = 2      /* 纸之星手作纸 150 G */
};

/* 运之星轮盘结算结果 */
enum LuckOutcome
{
    LUCK_DECLINED = 0,  /* 婉拒：+1 G */
    LUCK_WIN = 1,       /* 中奖：净赚 30 G（-50 +80） */
    LUCK_BADGE = 2,     /* 未中奖且未满仓：-50 G，+1 幸运徽章 */
    LUCK_REFUND = 3     /* 未中奖且已满仓：-50 +25 G（净亏 25 G） */
};

/* 10 个状态位统一使用位掩码管理 */
#define FLAG_ITEM_BOOKMARK      (1u << 0)  /* 持有干花书签 */
#define FLAG_ITEM_KEY           (1u << 1)  /* 持有黄铜钥匙 */
#define FLAG_EV_BOOK_DONE       (1u << 2)  /* 0 书之星事件已完成 */
#define FLAG_EV_FLOWER_DONE     (1u << 3)  /* 1 花之星事件已完成 */
#define FLAG_EV_CLOCK_DONE      (1u << 4)  /* 2 钟之星事件已完成 */
#define FLAG_EV_MIRROR_DONE     (1u << 5)  /* 3 镜之星事件已完成（暂缓离开不置位） */
#define FLAG_EV_LUCK_DONE       (1u << 6)  /* 4 运之星事件已完成（50%未触发不置位） */
#define FLAG_TOPIC_BOOKMARK     (1u << 7)  /* 解锁温泉话题：书签背面的花名 */
#define FLAG_TOPIC_STARMAP      (1u << 8)  /* 解锁温泉话题：生日那天的星空 */
#define FLAG_EV_MIRROR_DEFERRED (1u << 9)  /* 3 镜之星曾暂缓离开，重返改播短开场（完成后清除） */
#define FLAG_ALL_VALID          ((1u << 10) - 1u)

struct GameState
{
    int day;                /* 当前天数 1 ~ 5 */
    int phase;              /* PHASE_TRAVEL 或 PHASE_BIRTHDAY */
    int planet;             /* 当前星球 0 ~ 4 */
    int tripsLeft;          /* 今日剩余航程 0 ~ 2 */
    int money;              /* 当前资金（>= 0） */
    int cargoCap;           /* 货舱上限（5 或 7） */
    int cargo[GOOD_COUNT];  /* 5 种普通商品持有数量 */
    unsigned int flags;     /* 信物 / 事件 / 温泉话题位掩码 */
};

/* ---------- 静态世界数据查询（由 Antigravity 在 game.c 中实现） ---------- */
const char *getPlanetName(int planet);
const char *getPlanetIntro(int planet);
const char *getGoodName(int good);
int getBuyPrice(int planet, int good);
int getSellPrice(int planet, int good);
int canTravel(int fromPlanet, int toPlanet);
int getSellPlanetForGood(int good);

/* ---------- 核心规则与状态机（由你在 game.c 中实现） ---------- */

/* 初始化新开局状态（startPlanet 有效返回 1，否则返回 0） */
int initGame(struct GameState *state, int startPlanet);

/* 返回当前已占用货舱总件数 */
int getCargoUsed(const struct GameState *state);

/* 将 planet 的所有直达邻星写入 outNeighbors（容量至少 PLANET_COUNT），返回邻星个数 */
int getNeighbors(int planet, int outNeighbors[PLANET_COUNT]);

/* 返回 planet 收购的唯一商品编号，若无返回 -1 */
int getSellGoodAt(int planet);

/* 将 planet 出售的商品编号写入 outGoods（容量至少 GOOD_COUNT），返回出售商品种类数 */
int getBuyGoodsAt(int planet, int outGoods[GOOD_COUNT]);

/* 在当前星球买入 qty 件 good；成功扣款加货返回 1，非法（不可买/缺钱/超仓/qty<=0）返回 0 */
int buyGood(struct GameState *state, int good, int qty);

/* 在当前星球卖出 qty 件 good；成功减货加款返回 1，非法（不可卖/持货不足/qty<=0）返回 0 */
int sellGood(struct GameState *state, int good, int qty);

/* 消耗 1 次航程飞往 destPlanet；成功返回 1，非法返回 0 */
int travelToPlanet(struct GameState *state, int destPlanet);

/* 结束当日并推进状态：Day 1~4 -> 次日 PHASE_TRAVEL(tripsLeft=2)；Day 5 -> PHASE_BIRTHDAY(tripsLeft=0) */
int finishDay(struct GameState *state);

/* 结算生日礼物：先将扣前余额写入 outMoneyBefore，校验合法后扣款返回 1；不合法返回 0 */
int settleBirthdayGift(struct GameState *state, int choice, int *outMoneyBefore);

/* 判断当前所在星球是否具备触发抵达事件的确定条件（运之星 50% 概率不在此掷骰，只要未完成即返回 1） */
int canTriggerArrivalEvent(const struct GameState *state);

/* 0 书之星事件结算：giveTea=0 整理书页(+5G)；giveTea=1 交1花茶(+55G)；均赠书签并置完成 */
int applyBookEvent(struct GameState *state, int giveTea);

/* 1 花之星事件结算：giveBookmark=1 赠书签(+15G,扩仓7)；giveBookmark=0 保留(+10G,解锁花名话题) */
int applyFlowerEvent(struct GameState *state, int giveBookmark);

/* 2 钟之星事件结算：giveInk=0 擦发条(+5G)；giveInk=1 交1墨水(+70G)；均赠钥匙并置完成 */
int applyClockEvent(struct GameState *state, int giveInk);

/* 3 镜之星事件结算：option=1 常规(+15G)；option=2 留星图(-1胶卷,+80G,解锁星图)；option=3 暂缓(需无胶卷) */
int applyMirrorEvent(struct GameState *state, int option);

/* 4 运之星事件结算：gamble=0 婉拒(+1G)；gamble=1 转轮盘(-50G，按 rollWin!=0 判中奖/徽章/满仓折现25G)
 * 成功返回 1 并通过 outOutcome 输出结果枚举；资金不足或已完成返回 0 */
int applyLuckEvent(struct GameState *state, int gamble, int rollWin, enum LuckOutcome *outOutcome);

/* 完整语义合法性校验（存档读入与单元测试共用）：合法返回 1，非法返回 0 */
int validateGameState(const struct GameState *state);

#endif
/* ==================== [Antigravity 生成 结束] ==================== */
