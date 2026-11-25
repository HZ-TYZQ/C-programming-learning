/* ==================== [Antigravity 生成] 终端安全输入接口 ==================== */
#ifndef INPUT_H
#define INPUT_H

enum StoryStep
{
    STEP_NEXT = 0,       /* Enter：继续下一句 */
    STEP_SPEED = 1,      /* f + Enter：切换打字速度 */
    STEP_SKIP_CHUNK = 2, /* s + Enter：本段剩余台词即时显示完 */
    STEP_EOF = 3         /* 输入流关闭（Ctrl+D / 管道结束） */
};

/* 读取 [minVal, maxVal] 范围内的整数；成功写入 *outVal 返回 1，遇到 EOF 返回 0 */
int readIntInRange(const char *prompt, int minVal, int maxVal, int *outVal);

/* 市场数量输入：空回车默认取 maxVal，0 表示取消，[1, maxVal] 为指定数量；
 * 正常读到结果写入 *outQty 返回 1，遇到 EOF 返回 0 */
int readQuantityDefaultMax(const char *prompt, int maxVal, int *outQty);

/* 剧情步进等待：返回 STEP_NEXT / STEP_SPEED / STEP_SKIP_CHUNK / STEP_EOF */
enum StoryStep waitStoryStep(void);

/* 暂停等待玩家按回车继续；成功返回 1，遇到 EOF 返回 0 */
int waitEnter(const char *prompt);

/* 二次确认（y/Y 确认，其余或空回车取消）；
 * 成功写入 *outYes（1=确认, 0=取消）返回 1，遇到 EOF 返回 0 */
int confirmAction(const char *prompt, int *outYes);

#endif
/* ==================== [Antigravity 生成 结束] ==================== */
