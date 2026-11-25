#define _POSIX_C_SOURCE 200809L
/*--------------- <generated with GPT-6> ------------------*/
/* 结算卡根据当前可用的生日存档显示提示。 */
/*------------------------ <END> -------------------------*/
/* ==================== [Antigravity 生成] 终端渲染、UTF-8 打字机与界面面板 ==================== */
/* 说明：本文件包含超纲底层封装（nanosleep / UTF-8 多字节解析与物理列宽折行）
 * 以及大量重复的终端排版 printf 代码，已按《UI设计.md》完整实现。
 */

#include "ui.h"

#include "input.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

/* 语速档位：0 = 正常，1 = 快速，2 = 即时 */
static int g_speedMode = 0;

/* 物理行翻页阈值（适配标准 80x24 终端） */
#define PAGE_MAX_PHYSICAL_LINES 13
#define WRAP_COLUMNS            70

void clearScreen(void)
{
    printf("\x1b[2J\x1b[H");
    fflush(stdout);
}

void sleepMs(int ms)
{
    struct timespec req;

    if (ms <= 0)
    {
        return;
    }
    req.tv_sec = ms / 1000;
    req.tv_nsec = (long)(ms % 1000) * 1000000L;
    nanosleep(&req, NULL);
}

int getSpeedMode(void)
{
    return g_speedMode;
}

void cycleSpeedMode(void)
{
    g_speedMode = (g_speedMode + 1) % 3;
}

const char *getSpeedName(void)
{
    if (g_speedMode == 0)
    {
        return "正常";
    }
    if (g_speedMode == 1)
    {
        return "快速";
    }
    return "即时";
}

/* 判断 UTF-8 字符是否为全角标点并计算额外停顿毫秒数 */
static int getUtf8PauseMs(const char *s, size_t len)
{
    if (len == 3)
    {
        if (strncmp(s, "，", 3) == 0)
        {
            return 120;
        }
        if (strncmp(s, "。", 3) == 0 ||
            strncmp(s, "！", 3) == 0 ||
            strncmp(s, "？", 3) == 0)
        {
            return 170;
        }
        if (strncmp(s, "—", 3) == 0)
        {
            return 45;
        }
    }
    return 0;
}

void typePrint(const char *text, int instant)
{
    size_t i = 0;

    if (text == NULL)
    {
        return;
    }

    if (instant || g_speedMode == 2)
    {
        printf("%s", text);
        fflush(stdout);
        return;
    }

    while (text[i] != '\0')
    {
        unsigned char first = (unsigned char)text[i];
        size_t start = i;
        size_t charLen = 1;
        int delay = 0;

        /* 输出首字节及所有 UTF-8 续字节（10xxxxxx） */
        putchar(first);
        i++;
        while (text[i] != '\0' && (((unsigned char)text[i] & 0xC0u) == 0x80u))
        {
            putchar((unsigned char)text[i]);
            i++;
            charLen++;
        }
        fflush(stdout);

        delay = (charLen > 1) ? 25 : 18;

        if (charLen == 1)
        {
            if (first == ',')
            {
                delay += 120;
            }
            else if (first == '!' || first == '?')
            {
                delay += 170;
            }
            else if (first == '.')
            {
                /* 区分省略号 "..." 与单句号 "." */
                int prevDot = (start > 0 && text[start - 1] == '.');
                int nextDot = (text[i] == '.');
                delay += (prevDot || nextDot) ? 70 : 170;
            }
            else if (first == '-')
            {
                /* 半角破折号 "--" 停顿 */
                int prevDash = (start > 0 && text[start - 1] == '-');
                int nextDash = (text[i] == '-');
                if (prevDash || nextDash)
                {
                    delay += 45;
                }
            }
        }
        else
        {
            delay += getUtf8PauseMs(text + start, charLen);
        }

        if (g_speedMode == 1)
        {
            delay /= 3;
            if (delay < 4)
            {
                delay = 4;
            }
        }
        sleepMs(delay);
    }
}

/* 估算字符串在终端上的显示列宽（ASCII 计 1 列，多字节 UTF-8 计 2 列） */
static int estimateDisplayColumns(const char *s)
{
    size_t i = 0;
    int cols = 0;

    if (s == NULL)
    {
        return 0;
    }
    while (s[i] != '\0')
    {
        unsigned char c = (unsigned char)s[i];
        if ((c & 0x80u) == 0u)
        {
            cols += 1;
            i++;
        }
        else
        {
            cols += 2;
            i++;
            while (s[i] != '\0' && (((unsigned char)s[i] & 0xC0u) == 0x80u))
            {
                i++;
            }
        }
    }
    return cols;
}

static int estimateLinePhysicalHeight(const struct StoryLine *line)
{
    int cols = 0;
    int rows = 1;

    if (line == NULL || line->type == LINE_BREAK)
    {
        return 2;
    }

    cols = estimateDisplayColumns(line->text);
    if (line->type == LINE_RIDLEY || line->type == LINE_WATARI)
    {
        cols += 10; /* "蕾德莉 | " / "  渡里 | " */
    }
    else if (line->type == LINE_NPC)
    {
        cols += estimateDisplayColumns(line->speaker) + 5;
    }
    else
    {
        cols += 4;
    }

    rows = (cols + WRAP_COLUMNS - 1) / WRAP_COLUMNS;
    if (rows < 1)
    {
        rows = 1;
    }
    return rows;
}

static void drawStoryHeader(const char *title)
{
    clearScreen();
    printf(C_GRAY "%s\n" C_RESET, LINE_STRONG);
    printf(" " C_BOLD C_CYAN "%s" C_RESET
           "  " C_GRAY "[语速: %s | Enter 下一句 | f 切语速 | s 本段显完]\n" C_RESET,
           title != NULL ? title : "剧情",
           getSpeedName());
    printf(C_GRAY "%s\n" C_RESET, LINE_STRONG);
    printf(C_GRAY " (打字期间请勿连按 Enter, 觉得慢可按 f+Enter 切至 [快速/即时])\n\n" C_RESET);
}

void storyBegin(struct StoryContext *ctx, const char *title)
{
    if (ctx == NULL)
    {
        return;
    }
    ctx->title = title;
    ctx->physicalLines = 0;
    ctx->skipChunk = 0;
    drawStoryHeader(title);
}

int storyPlayChunk(struct StoryContext *ctx, const struct StoryLine *lines, int count)
{
    int i = 0;

    if (ctx == NULL || lines == NULL || count <= 0)
    {
        return 1;
    }
    ctx->skipChunk = 0;

    for (i = 0; i < count; i++)
    {
        const struct StoryLine *ln = &lines[i];
        int height = estimateLinePhysicalHeight(ln);
        int instant = (ctx->skipChunk != 0);

        /* 物理行即将溢出，或页面已过半且遇场景分割时翻页 */
        if (ctx->physicalLines > 0 &&
            (ctx->physicalLines + height > PAGE_MAX_PHYSICAL_LINES ||
             (ln->type == LINE_BREAK && ctx->physicalLines >= PAGE_MAX_PHYSICAL_LINES / 2)))
        {
            drawStoryHeader(ctx->title);
            ctx->physicalLines = 0;
        }

        if (ln->type == LINE_BREAK)
        {
            printf("\n" C_GRAY "                         .  .  .\n\n" C_RESET);
            fflush(stdout);
            ctx->physicalLines += 2;
            if (!instant && g_speedMode != 2)
            {
                sleepMs(280);
            }
            continue;
        }

        switch (ln->type)
        {
            case LINE_NARRATION:
                printf("  " C_GRAY C_ITALIC);
                typePrint(ln->text, instant);
                printf(C_RESET);
                break;

            case LINE_RIDLEY:
                printf("  " C_BOLD C_YELLOW "蕾德莉" C_RESET C_GRAY " | " C_RESET C_WHITE);
                typePrint(ln->text, instant);
                printf(C_RESET);
                break;

            case LINE_WATARI:
                printf("  " C_BOLD C_CYAN "  渡里" C_RESET C_GRAY " | " C_RESET C_WHITE);
                typePrint(ln->text, instant);
                printf(C_RESET);
                break;

            case LINE_NPC:
                printf("  " C_BOLD C_GREEN "%s" C_RESET C_GRAY " | " C_RESET C_WHITE,
                       ln->speaker != NULL ? ln->speaker : "旅人");
                typePrint(ln->text, instant);
                printf(C_RESET);
                break;

            case LINE_THOUGHT:
                printf("  " C_MAGENTA);
                typePrint(ln->text, instant);
                printf(C_RESET);
                break;

            case LINE_BREAK:
                break;
        }

        ctx->physicalLines += height;

        if (ctx->skipChunk)
        {
            printf("\n");
            fflush(stdout);
            continue;
        }

        /* 句末轻提示，等待玩家步进 */
        while (1)
        {
            enum StoryStep step;
            printf(" " C_GRAY "v" C_RESET);
            fflush(stdout);
            step = waitStoryStep();

            if (step == STEP_EOF)
            {
                printf("\n");
                return 0;
            }
            if (step == STEP_SPEED)
            {
                cycleSpeedMode();
                printf(C_GRAY "  [语速已切换为: %s, 按 Enter 继续]" C_RESET, getSpeedName());
                ctx->physicalLines += 1;
                continue;
            }
            if (step == STEP_SKIP_CHUNK)
            {
                ctx->skipChunk = 1;
                break;
            }
            break;
        }
    }

    return 1;
}

int storyWaitEnd(void)
{
    printf("\n" C_GRAY "%s\n" C_RESET, LINE_THIN);
    return waitEnter(C_GRAY " [本段剧情结束, 按 Enter 继续] " C_RESET);
}

static const char *getNoticeColor(enum NoticeKind kind)
{
    switch (kind)
    {
        case NOTICE_OK:
            return C_GREEN;
        case NOTICE_WARN:
            return C_YELLOW;
        case NOTICE_ERR:
            return C_RED;
        case NOTICE_INFO:
        default:
            return C_WHITE;
    }
}

static void printTokensAndMemories(unsigned int flags)
{
    int printed = 0;

    if ((flags & FLAG_ITEM_BOOKMARK) && (flags & FLAG_TOPIC_BOOKMARK))
    {
        printf(C_MAGENTA "[干花书签-花名]" C_RESET);
        printed = 1;
    }
    else if (flags & FLAG_ITEM_BOOKMARK)
    {
        printf(C_MAGENTA "[干花书签]" C_RESET);
        printed = 1;
    }

    if (flags & FLAG_ITEM_KEY)
    {
        if (printed)
        {
            printf(" ");
        }
        printf(C_MAGENTA "[黄铜钥匙]" C_RESET);
        printed = 1;
    }
    else if (flags & FLAG_TOPIC_STARMAP)
    {
        if (printed)
        {
            printf(" ");
        }
        printf(C_MAGENTA "[生日星图]" C_RESET);
        printed = 1;
    }

    if (!printed)
    {
        printf(C_GRAY "无" C_RESET);
    }
}

void drawStatusHeader(const struct GameState *state,
                      const char *screenName,
                      enum NoticeKind noticeKind,
                      const char *noticeText)
{
    int used = getCargoUsed(state);

    clearScreen();
    printf(C_GRAY "%s\n" C_RESET, LINE_STRONG);
    printf(" " C_BOLD C_CYAN "Day %d / %d" C_RESET
           "  " C_GRAY "|" C_RESET "  " C_BOLD C_WHITE "%s" C_RESET
           "  " C_GRAY "|" C_RESET "  今日余程: " C_YELLOW "%d/%d\n" C_RESET,
           state->day, MAX_DAYS,
           screenName != NULL ? screenName : "",
           state->tripsLeft, TRIPS_PER_DAY);

    printf(" 资金: %s%d" C_RESET " / %d G"
           "   货舱: " C_WHITE "%d/%d" C_RESET
           "   信物/回忆: ",
           state->money >= TARGET_MONEY ? C_BOLD C_GREEN : C_BOLD C_YELLOW,
           state->money, TARGET_MONEY,
           used, state->cargoCap);
    printTokensAndMemories(state->flags);
    printf("\n");

    printf(C_GRAY "%s\n" C_RESET, LINE_THIN);
    if (noticeText != NULL && noticeText[0] != '\0')
    {
        printf(" %s%s" C_RESET "\n", getNoticeColor(noticeKind), noticeText);
    }
    else
    {
        printf(" " C_GRAY "准备就绪.\n" C_RESET);
    }
    printf(C_GRAY "%s\n" C_RESET, LINE_STRONG);
}

void drawTitleScreen(int hasSave,
                     const struct SaveSummary *summary,
                     enum NoticeKind noticeKind,
                     const char *noticeText)
{
    clearScreen();
    printf(C_GRAY "%s\n" C_RESET, LINE_STRONG);
    printf("\n");
    printf("                " C_BOLD C_CYAN "< 下 一 站 , 生 日 >\n" C_RESET);
    printf("        " C_GRAY "五天的星间跑商与生日故事 - 少女星间漂流记同人\n" C_RESET);
    printf("\n");
    printf(C_GRAY "%s\n" C_RESET, LINE_STRONG);

    if (noticeText != NULL && noticeText[0] != '\0')
    {
        printf(" %s%s" C_RESET "\n", getNoticeColor(noticeKind), noticeText);
        printf(C_GRAY "%s\n" C_RESET, LINE_THIN);
    }

    printf("\n");
    printf("  " C_BOLD C_CYAN "[1]" C_RESET " 开始新旅程\n");

    if (hasSave && summary != NULL)
    {
        if (summary->phase == PHASE_BIRTHDAY)
        {
            printf("  " C_BOLD C_CYAN "[2]" C_RESET " 继续旅程  "
                   C_GREEN "(Day %d | 生日购礼 | %d G)\n" C_RESET,
                   summary->day, summary->money);
        }
        else
        {
            printf("  " C_BOLD C_CYAN "[2]" C_RESET " 继续旅程  "
                   C_GREEN "(Day %d | %s | %d G)\n" C_RESET,
                   summary->day, getPlanetName(summary->planet), summary->money);
        }
    }
    else
    {
        printf("  " C_GRAY "[2] 继续旅程  (暂无有效存档)\n" C_RESET);
    }

    printf("  " C_BOLD C_CYAN "[3]" C_RESET " 切换打字速度  "
           C_YELLOW "(当前: %s)\n" C_RESET, getSpeedName());
    printf("  " C_GRAY "[0]" C_RESET " 退出游戏\n\n");
    printf(C_GRAY "%s\n" C_RESET, LINE_THIN);
}

void drawStartPlanetScreen(enum NoticeKind noticeKind, const char *noticeText)
{
    int p = 0;

    clearScreen();
    printf(C_GRAY "%s\n" C_RESET, LINE_STRONG);
    printf(" " C_BOLD C_CYAN "选择起点星球" C_RESET "\n");
    printf(" " C_YELLOW "目标: 五天内攒足 %d G 买甜之星巧克力" C_RESET
           " | 资金: %d G | 货舱: %d 格 | 起点不触发抵达事件\n",
           TARGET_MONEY, START_MONEY, BASE_CARGO);
    printf(C_GRAY "%s\n" C_RESET, LINE_STRONG);

    if (noticeText != NULL && noticeText[0] != '\0')
    {
        printf(" %s%s" C_RESET "\n", getNoticeColor(noticeKind), noticeText);
        printf(C_GRAY "%s\n" C_RESET, LINE_THIN);
    }

    for (p = 0; p < PLANET_COUNT; p++)
    {
        int neighbors[PLANET_COUNT];
        int nCount = getNeighbors(p, neighbors);
        int sellGood = getSellGoodAt(p);
        int buyGoods[GOOD_COUNT];
        int bCount = getBuyGoodsAt(p, buyGoods);
        int i = 0;

        printf("  " C_BOLD C_CYAN "[%d]" C_RESET " " C_BOLD C_WHITE "%s" C_RESET "  " C_GRAY "直达: ",
               p + 1, getPlanetName(p));
        for (i = 0; i < nCount; i++)
        {
            printf("%s%s", i > 0 ? " / " : "", getPlanetName(neighbors[i]));
        }
        printf(C_RESET "\n");

        printf("      " C_GREEN "收: " C_RESET);
        if (sellGood >= 0)
        {
            printf("%s %dG", getGoodName(sellGood), getSellPrice(p, sellGood));
        }
        printf("   " C_YELLOW "售: " C_RESET);
        for (i = 0; i < bCount; i++)
        {
            int g = buyGoods[i];
            int dest = getSellPlanetForGood(g);
            printf("%s%s %dG(%s收%dG)",
                   i > 0 ? " / " : "",
                   getGoodName(g),
                   getBuyPrice(p, g),
                   getPlanetName(dest),
                   getSellPrice(dest, g));
        }
        printf("\n");
    }

    printf(C_GRAY "%s\n" C_RESET, LINE_THIN);
}

static void printCargoSummaryLine(const struct GameState *state)
{
    int g = 0;
    int any = 0;

    printf(" 当前货舱: ");
    for (g = 0; g < GOOD_COUNT; g++)
    {
        if (state->cargo[g] > 0)
        {
            printf("%s" C_WHITE "%s x%d" C_RESET, any ? "  " : "", getGoodName(g), state->cargo[g]);
            any = 1;
        }
    }
    if (!any)
    {
        printf(C_GRAY "空舱" C_RESET);
    }
    printf("\n");
}

void drawTravelScreen(const struct GameState *state,
                      enum NoticeKind noticeKind,
                      const char *noticeText)
{
    char title[64];
    int neighbors[PLANET_COUNT];
    int nCount = 0;
    int i = 0;

    snprintf(title, sizeof(title), "%s - 选星出发", getPlanetName(state->planet));
    drawStatusHeader(state, title, noticeKind, noticeText);
    printCargoSummaryLine(state);
    printf(C_GRAY "%s\n" C_RESET, LINE_THIN);

    nCount = getNeighbors(state->planet, neighbors);
    printf(" 可直达的相邻星球:\n");
    for (i = 0; i < nCount; i++)
    {
        int dest = neighbors[i];
        int sellGood = getSellGoodAt(dest);
        int buyGoods[GOOD_COUNT];
        int bCount = getBuyGoodsAt(dest, buyGoods);
        int j = 0;

        printf("  " C_BOLD C_CYAN "[%d]" C_RESET " " C_BOLD C_WHITE "%s" C_RESET "  ",
               i + 1, getPlanetName(dest));

        if (sellGood >= 0)
        {
            printf(C_GREEN "收:%s %dG" C_RESET, getGoodName(sellGood), getSellPrice(dest, sellGood));
            if (state->cargo[sellGood] > 0)
            {
                printf(" " C_BOLD C_GREEN "[可售 x%d]" C_RESET, state->cargo[sellGood]);
            }
        }

        printf("  " C_YELLOW "售:" C_RESET);
        for (j = 0; j < bCount; j++)
        {
            int g = buyGoods[j];
            printf("%s%s %dG", j > 0 ? "/" : "", getGoodName(g), getBuyPrice(dest, g));
        }
        printf("\n");
    }

    printf("\n");
    printf("  " C_BOLD C_CYAN "[4]" C_RESET " 查看星图与完整行情\n");
    printf("  " C_GRAY "[9]" C_RESET " 返回主菜单 " C_GRAY "(本日未完成航程不保存)\n" C_RESET);
    printf("  " C_YELLOW "[0]" C_RESET " 结束今日 " C_GRAY "(跳过今日余程, 进入当晚日常)\n" C_RESET);
    printf(C_GRAY "%s\n" C_RESET, LINE_THIN);
}

void drawStarMap(const struct GameState *state)
{
    int p = 0;

    clearScreen();
    printf(C_GRAY "%s\n" C_RESET, LINE_STRONG);
    printf(" " C_BOLD C_CYAN "星图与完整行情总览" C_RESET
           "  " C_GRAY "(主环顺流每跳单件利润 +25 G | 书->钟捷径 +20 G)\n" C_RESET);
    printf(C_GRAY "%s\n" C_RESET, LINE_STRONG);
    printf(" 主环顺流: " C_YELLOW "花(茶) -> 书(卷) -> 镜(墨) -> 钟(齿) -> 运(徽) -> 花\n" C_RESET);
    printf(" 捷径航线: " C_CYAN "书之星 <-> 钟之星" C_RESET " (书买墨水 30G -> 钟卖 50G)\n");
    printf(C_GRAY "%s\n" C_RESET, LINE_THIN);

    for (p = 0; p < PLANET_COUNT; p++)
    {
        int neighbors[PLANET_COUNT];
        int nCount = getNeighbors(p, neighbors);
        int sellGood = getSellGoodAt(p);
        int buyGoods[GOOD_COUNT];
        int bCount = getBuyGoodsAt(p, buyGoods);
        int i = 0;

        printf(" %s%s%s" C_RESET "  直达: ",
               (state != NULL && state->planet == p) ? C_BOLD C_YELLOW "★ " : "  ",
               getPlanetName(p),
               (state != NULL && state->planet == p) ? " (当前)" : "");
        for (i = 0; i < nCount; i++)
        {
            printf("%s%s", i > 0 ? " / " : "", getPlanetName(neighbors[i]));
        }
        printf("\n");

        printf("     " C_GREEN "收: %s %dG" C_RESET "   " C_YELLOW "售: " C_RESET,
               getGoodName(sellGood), getSellPrice(p, sellGood));
        for (i = 0; i < bCount; i++)
        {
            int g = buyGoods[i];
            printf("%s%s %dG", i > 0 ? " / " : "", getGoodName(g), getBuyPrice(p, g));
        }
        printf("\n");
    }

    printf(C_GRAY "%s\n" C_RESET, LINE_THIN);
    (void)waitEnter(" 按 Enter 返回...");
}

void drawMarketScreen(const struct GameState *state,
                      enum NoticeKind noticeKind,
                      const char *noticeText)
{
    char title[64];
    int sellGood = getSellGoodAt(state->planet);
    int buyGoods[GOOD_COUNT];
    int bCount = getBuyGoodsAt(state->planet, buyGoods);
    int used = getCargoUsed(state);
    int freeSlots = state->cargoCap - used;
    int i = 0;

    snprintf(title, sizeof(title), "%s - 集市交易", getPlanetName(state->planet));
    drawStatusHeader(state, title, noticeKind, noticeText);
    printCargoSummaryLine(state);
    printf(C_GRAY "%s\n" C_RESET, LINE_THIN);

    /* [1] 本站唯一收购项 */
    if (sellGood >= 0)
    {
        int price = getSellPrice(state->planet, sellGood);
        int holding = state->cargo[sellGood];

        if (holding > 0)
        {
            printf("  " C_BOLD C_CYAN "[1]" C_RESET " " C_GREEN "卖出" C_RESET
                   " %-12s  " C_GREEN "%2d G/件" C_RESET "   (持有 %d 件, 最多卖得 +%d G)\n",
                   getGoodName(sellGood), price, holding, price * holding);
        }
        else
        {
            printf("  " C_GRAY "[1] 卖出 %-12s  %2d G/件   (未持有)\n" C_RESET,
                   getGoodName(sellGood), price);
        }
    }

    /* [2..1+bCount] 本站出售项（附注顺流收货星） */
    for (i = 0; i < bCount; i++)
    {
        int g = buyGoods[i];
        int price = getBuyPrice(state->planet, g);
        int dest = getSellPlanetForGood(g);
        int destPrice = getSellPrice(dest, g);
        int maxAfford = (price > 0) ? (state->money / price) : 0;
        int maxBuy = (maxAfford < freeSlots) ? maxAfford : freeSlots;

        if (maxBuy > 0)
        {
            printf("  " C_BOLD C_CYAN "[%d]" C_RESET " " C_YELLOW "买入" C_RESET
                   " %-12s  " C_YELLOW "%2d G/件" C_RESET
                   "   (最多买 %d 件) " C_GRAY "-> %s收 %dG\n" C_RESET,
                   i + 2, getGoodName(g), price, maxBuy, getPlanetName(dest), destPrice);
        }
        else
        {
            const char *reason = (freeSlots <= 0) ? "满仓" : "资金不足";
            printf("  " C_GRAY "[%d] 买入 %-12s  %2d G/件   (%s) -> %s收 %dG\n" C_RESET,
                   i + 2, getGoodName(g), price, reason, getPlanetName(dest), destPrice);
        }
    }

    printf("\n");
    printf("  " C_BOLD C_CYAN "[9]" C_RESET " 查看星图与完整行情 " C_GRAY "(查看后回到本市场)\n" C_RESET);
    printf("  " C_GRAY "[0]" C_RESET " 离开市场\n");
    printf(C_GRAY "%s\n" C_RESET, LINE_THIN);
}

void drawEventStatusBar(const struct GameState *state, int relatedGood)
{
    printf("\n" C_GRAY "%s\n" C_RESET, LINE_THIN);
    printf(" " C_CYAN "当前状态:" C_RESET " 资金 " C_YELLOW "%d G" C_RESET
           "  |  货舱 " C_WHITE "%d/%d" C_RESET,
           state->money, getCargoUsed(state), state->cargoCap);
    if (relatedGood >= 0 && relatedGood < GOOD_COUNT)
    {
        printf("  |  %s: " C_GREEN "%d 件" C_RESET,
               getGoodName(relatedGood), state->cargo[relatedGood]);
    }
    printf("\n" C_GRAY "%s\n" C_RESET, LINE_THIN);
}

void drawBirthdayScreen(const struct GameState *state,
                        enum NoticeKind noticeKind,
                        const char *noticeText)
{
    clearScreen();
    printf(C_GRAY "%s\n" C_RESET, LINE_STRONG);
    printf(" " C_BOLD C_CYAN "生日当天 - 选择礼物目的地" C_RESET "\n");
    printf(" 当前可用现金: %s%d G" C_RESET "  " C_GRAY "(未售出的货物不计入购礼资金)\n" C_RESET,
           state->money >= TARGET_MONEY ? C_BOLD C_GREEN : C_BOLD C_YELLOW,
           state->money);
    printf(C_GRAY "%s\n" C_RESET, LINE_STRONG);

    if (noticeText != NULL && noticeText[0] != '\0')
    {
        printf(" %s%s" C_RESET "\n", getNoticeColor(noticeKind), noticeText);
        printf(C_GRAY "%s\n" C_RESET, LINE_THIN);
    }

    printf("\n");
    if (state->money >= TARGET_MONEY)
    {
        printf("  " C_BOLD C_CYAN "[1]" C_RESET " " C_BOLD C_GREEN "去甜之星购买巧克力 (%d G)" C_RESET
               "  " C_GRAY "(购后剩余 %d G)\n" C_RESET,
               TARGET_MONEY, state->money - TARGET_MONEY);
    }
    else
    {
        printf("  " C_GRAY "[1] 去甜之星购买巧克力 (%d G)  [余额不足, 还差 %d G]\n" C_RESET,
               TARGET_MONEY, TARGET_MONEY - state->money);
    }

    if (state->money >= PAPER_PRICE)
    {
        printf("  " C_BOLD C_CYAN "[2]" C_RESET " " C_WHITE "去纸之星购买手作纸 (%d G)" C_RESET
               "  " C_GRAY "(购后剩余 %d G)\n" C_RESET,
               PAPER_PRICE, state->money - PAPER_PRICE);
    }
    else
    {
        printf("  " C_BOLD C_CYAN "[2]" C_RESET " " C_WHITE "去纸之星购买手作纸 (%d G)" C_RESET
               "  " C_GRAY "(不足 150 G 仍可选, 工坊老板会收下零钱相赠)\n" C_RESET,
               PAPER_PRICE);
    }

    printf("\n" C_GRAY "%s\n" C_RESET, LINE_THIN);
}

void drawEndingSummary(int choice, int moneyAfterGift, unsigned int flags)
{
    int hasBookmarkTopic = (flags & FLAG_TOPIC_BOOKMARK) != 0u;
    int hasStarmapTopic = (flags & FLAG_TOPIC_STARMAP) != 0u;

    clearScreen();
    printf(C_GRAY "%s\n" C_RESET, LINE_STRONG);
    printf("\n");
    printf("                    " C_BOLD C_CYAN "★ 旅 途 终 章 结 算 ★\n" C_RESET);
    printf("\n");
    printf(C_GRAY "%s\n" C_RESET, LINE_STRONG);

    printf("  达成结局  : " C_BOLD C_YELLOW "%s\n" C_RESET,
           choice == GIFT_CHOCOLATE ? "甜之星 - 渡里最喜欢的巧克力" : "纸之星 - 亲手写下的生日信");
    printf("  剩余零花钱: " C_BOLD C_GREEN "%d G\n" C_RESET, moneyAfterGift);
    printf("  温泉回忆  : ");
    if (hasBookmarkTopic && hasStarmapTopic)
    {
        printf(C_MAGENTA "[书签背面的花名] + [生日那天的星空] (全解锁)\n" C_RESET);
    }
    else if (hasBookmarkTopic)
    {
        printf(C_MAGENTA "[书签背面的花名]\n" C_RESET);
    }
    else if (hasStarmapTopic)
    {
        printf(C_MAGENTA "[生日那天的星空]\n" C_RESET);
    }
    else
    {
        printf(C_GRAY "无\n" C_RESET);
    }

    printf("\n");
    struct SaveSummary summary;
    if (peekSaveSummary(DEFAULT_SAVE_PATH, &summary) && summary.phase == PHASE_BIRTHDAY)
    {
        printf(C_GRAY "  提示: 可在主菜单选 [继续旅程], 从已有生日存档重选礼物.\n" C_RESET);
    }
    else
    {
        printf(C_GRAY "  提示: 暂无可用于重选礼物的生日存档.\n" C_RESET);
    }
    printf(C_GRAY "%s\n" C_RESET, LINE_STRONG);
}
/* ==================== [Antigravity 生成 结束] ==================== */
