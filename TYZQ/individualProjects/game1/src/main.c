#include "event.h"
#include "game.h"
#include "input.h"
#include "save.h"
#include "story.h"
#include "ui.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ==================== [Antigravity 生成] 提示栏辅助与程序入口骨架
 * ==================== */
struct NoticeState
{
  enum NoticeKind kind;
  char text[256];
};

static void setNotice(struct NoticeState *notice, enum NoticeKind kind, const char *msg)
{
  if (notice == NULL)
  {
    return;
  }
  notice->kind = kind;
  if (msg == NULL)
  {
    notice->text[0] = '\0';
  }
  else
  {
    snprintf(notice->text, sizeof(notice->text), "%s", msg);
  }
}
/* ==================== [Antigravity 生成 结束] ==================== */

/* ==================== [TODO: 请你自己实现] Step 4 主游戏流程控制
 * ==================== */

static int runStartPlanet(struct GameState *state)
{
  int choice;

  drawStartPlanetScreen(NOTICE_INFO, NULL);
  if (readIntInRange(" 请选择起点星球 [1-5]: ", 1, 5, &choice) == 0)
  {
    return 0;
  }

  return initGame(state, choice - 1);
}

static int runMarketLoop(struct GameState *state)
{

  struct NoticeState notice;
  int choice;
  int qty;
  setNotice(&notice, NOTICE_INFO, NULL);
  int buyGoods[GOOD_COUNT];
  int buyCount = getBuyGoodsAt(state->planet, buyGoods);

  while (1)
  {
    drawMarketScreen(state, notice.kind, notice.text);
    if (!readIntInRange("请选择 [0-9]: ", 0, 9, &choice))
    {
      return 0;
    }

    if (choice == 0)
    {
      int cargoUsed = getCargoUsed(state);
      if (state->day == MAX_DAYS && state->tripsLeft == 0 && cargoUsed != 0)
      {
        char prompt[256] = "未售货物不计入购礼资金, 确认离开市场吗? [y/N]";
        int isYes;

        int goodCanSell = getSellGoodAt(state->planet);
        if (goodCanSell >= 0 && state->cargo[goodCanSell] != 0)
        {
          int moneyCanGet = state->cargo[goodCanSell] * getSellPrice(state->planet, goodCanSell);

          snprintf(
            prompt,
            sizeof(prompt),
            C_RED "本站可卖出%s, 获得 +%d G\n"
                  "未售货物不计入购礼资金, 确认离开市场吗? [y/N]" C_RESET,
            getGoodName(goodCanSell),
            moneyCanGet);
        }

        if (!confirmAction(prompt, &isYes))
        {
          return 0;
        }

        if (!isYes)
        {
          continue;
        }
      }

      return 1;
    }
    else if (choice == 1)
    {
      int sellGoodId = getSellGoodAt(state->planet);

      if (sellGoodId < 0 || state->cargo[sellGoodId] <= 0)
      {
        setNotice(&notice, NOTICE_WARN, "当前未持有该商品呀!");
      }
      else
      {
        if (!readQuantityDefaultMax("卖出多少呢: ", state->cargo[sellGoodId], &qty))
        {
          return 0;
        }

        if (qty == 0)
        {
          continue;
        }
        else if (qty > 0)
        {
          if (!sellGood(state, sellGoodId, qty))
          {
            setNotice(&notice, NOTICE_WARN, "卖出失败!");
            continue;
          }

          setNotice(&notice, NOTICE_INFO, "卖出成功!");
        }
      }
    }
    else if (choice >= 2 && choice < 2 + buyCount)
    {
      int good = buyGoods[choice - 2];
      setNotice(&notice, NOTICE_INFO, getGoodName(good));

      int price = getBuyPrice(state->planet, good);
      int cargoRemain = state->cargoCap - getCargoUsed(state);
      int maxBuy = cargoRemain > (state->money / price) ? state->money / price : cargoRemain;
      if (maxBuy == 0)
      {
        setNotice(&notice, NOTICE_WARN, "仓库满了或者星币不足哟!");
        continue;
      }

      if (!readQuantityDefaultMax("买入多少呢: ", maxBuy, &qty))
      {
        return 0;
      }

      if (qty == 0)
      {
        continue;
      }
      else if (qty > 0)
      {
        if (!buyGood(state, good, qty))
        {
          setNotice(&notice, NOTICE_WARN, "买入失败啦!");
          continue;
        }
        else
        {
          setNotice(&notice, NOTICE_INFO, "买入成功啦!");
        }
      }
    }
    else if (choice == 9)
    {
      drawStarMap(state);
      continue;
    }
    else
    {
      setNotice(&notice, NOTICE_WARN, "无效选项");
      continue;
    }
  }
  (void)state;
  return 0;
}

static int runTravelDay(struct GameState *state, int *outBackToMenu)
{
  struct NoticeState notice = {0};
  int neighbors[PLANET_COUNT];
  int choice;
  int destination;

  while (state->tripsLeft > 0)
  {
    int neighborCount = getNeighbors(state->planet, neighbors);

    drawTravelScreen(state, notice.kind, notice.text);

    if (!readIntInRange("请输入选项: ", 0, 9, &choice))
    {
      return 0;
    }

    if (outBackToMenu != NULL)
    {
      *outBackToMenu = 0;
    }

    if (choice == 0)
    {
      char prompt[256] = "确认结束今日吗? [y/n]";

      if (state->day == MAX_DAYS && getCargoUsed(state) > 0)
      {
        int cargoUsed = getCargoUsed(state);

        snprintf(
          prompt,
          sizeof(prompt),
          C_RED "今天是最后一天, 舱内还有 %d 件货物未卖出."
                "未售货物不计入购礼资金, 确认结束今日吗? [y/N] " C_RESET,
          cargoUsed);
      }

      int isYes;
      if (!confirmAction(prompt, &isYes))
      {
        return 0;
      }

      if (isYes)
      {
        break;
      }
      else
      {
        continue;
      }
    }
    else if (choice == 4)
    {
      drawStarMap(state);
      continue;
    }
    else if (choice == 9)
    {
      int isYes = 0;
      if (!confirmAction("今日进度不会保存, 确认返回主菜单吗?[y/n]", &isYes))
      {
        return 0;
      }

      if (!isYes)
      {
        continue;
      }

      *outBackToMenu = 1;
      return 1;
    }
    if (choice > neighborCount)
    {
      setNotice(&notice, NOTICE_WARN, "无效选项");
      continue;
    }

    destination = neighbors[choice - 1];
    if (!travelToPlanet(state, destination) || !runArrivalEvent(state))
    {
      return 0;
    }
    if (!runMarketLoop(state))
    {
      return 0;
    }
  }

  if (state->day == 5)
  {
    if (!playHotSpring(state))
    {
      return 0;
    }
  }
  else
  {
    if (!playDayNight(state->day))
    {
      return 0;
    }
  }

  if (!finishDay(state))
  {
    return 0;
  }

  if (saveGame(DEFAULT_SAVE_PATH, state))
  {
    printf(C_GREEN "已自动存档.\n" C_RESET);
  }
  else
  {
    printf(C_RED "自动存档失败,\n" C_RESET);
  }

  return waitEnter("按Enter继续...");
}

static int runBirthdayPhase(struct GameState *state)
{
  struct NoticeState notice;
  int choice;
  int moneyBefore;
  setNotice(&notice, NOTICE_INFO, NULL);

  while (1)
  {
    drawBirthdayScreen(state, notice.kind, notice.text);

    if (!readIntInRange("请输入选项: ", 1, 2, &choice))
    {
      return 0;
    }

    if (!settleBirthdayGift(state, choice, &moneyBefore))
    {
      setNotice(&notice, NOTICE_WARN, "钱没攒够啦!");
      continue;
    }

    return playEnding(choice, moneyBefore, state->money, state->flags);
  }
  return 0;
}

static int runGameSession(struct GameState *state, int isNewGame)
{
  int outBackToMenu = 0;

  if (isNewGame)
  {
    if (!playBeginning())
    {
      return 0;
    };
    if (!runStartPlanet(state))
    {
      return 0;
    }
    if (!runMarketLoop(state))
    {
      return 0;
    }
  }

  while (state->phase == PHASE_TRAVEL)
  {
    if (!runTravelDay(state, &outBackToMenu))
    {
      return 0;
    }

    if (outBackToMenu)
    {
      return 1;
    }
  }

  return runBirthdayPhase(state);
}

/* ==================== [Antigravity 生成] 程序入口与主菜单循环骨架
 * ==================== */
int main(void)
{
  struct NoticeState notice;
  int running = 1;

  /* 启动时初始化一次随机数种子（供运之星 50% 概率与轮盘使用） */
  srand((unsigned int)time(NULL));
  setNotice(&notice, NOTICE_INFO, "欢迎来到 <下一站, 生日>.");

  while (running)
  {
    struct SaveSummary summary;
    int hasSave = peekSaveSummary(DEFAULT_SAVE_PATH, &summary);
    int choice = 1;

    drawTitleScreen(hasSave, hasSave ? &summary : NULL, notice.kind, notice.text);
    if (!readIntInRange("请选择 [0-3]: ", 0, 3, &choice) || choice == 0)
    {
      break;
    }

    if (choice == 1)
    {
      struct GameState state;
      int isNewGame = 1;
      int isYes;

      if (hasSave)
      {
        if (!confirmAction("确认开始新游戏吗?(将会覆盖旧存档)", &isYes))
        {
          return 0;
        }
        if (!isYes)
        {
          continue;
        }
      }

      if (!runGameSession(&state, isNewGame))
      {
        return 0;
      }

      continue;
    }
    else if (choice == 2)
    {
      struct GameState state;
      if (!loadGame(DEFAULT_SAVE_PATH, &state))
      {
        setNotice(&notice, NOTICE_WARN, "暂无有效存档");
        continue;
      }

      if (!runGameSession(&state, 0))
      {
        return 0;
      }

      continue;
    }
    else if (choice == 3)
    {
      cycleSpeedMode();
      setNotice(&notice, NOTICE_INFO, getSpeedName());
      continue;
    }
    printf(
      " " C_YELLOW "[骨架模式] 请先完成 Step 1~4 的 TODO "
      "实现, 再运行完整游戏.\n" C_RESET);
    running = 0;
  }

  return 0;
}
/* ==================== [Antigravity 生成 结束] ==================== */
