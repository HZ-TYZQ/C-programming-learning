/* ==================== [Antigravity 生成] 16 份定稿剧情只读数组与播放拼接
 * ==================== */
/* 说明：完整转录自 docs/ 下全部 16 份定稿文案，保留半角标点与人物语气，
 * 并通过流式 StoryContext 支持多段条件剧本无缝拼接。
 */

#include "story.h"

#include "input.h"

#include <stddef.h>

#define ARRAY_LEN(arr) ((int)(sizeof(arr) / sizeof((arr)[0])))

/* ---------- 1. 开场剧情 (docs/beginning.md) ---------- */
static const struct StoryLine STORY_BEGINNING[] = {
    {LINE_RIDLEY, NULL, "\"糟糕, 怎么又忘了!\""},
    {LINE_NARRATION, NULL, "蕾德莉坐在床边, 扶着额头, 眉毛扭成麻花."},
    {LINE_THOUGHT, NULL,
     "(五天之后就是渡里的生日了, 但是蕾德莉的零花钱已经所剩无几.)"},
    {LINE_WATARI, NULL, "\"蕾德莉? 你还好吗?\""},
    {LINE_NARRATION, NULL, "渡里轻轻捧起蕾德莉的脸."},
    {LINE_RIDLEY, NULL, "\"没... 没事...\""},
    {LINE_NARRATION, NULL, "蕾德莉尴尬地笑了笑."},
    {LINE_THOUGHT, NULL, "(因为太忙忘记渡里生日什么的... 绝对不能让她知道!)"},
    {LINE_NARRATION, NULL, "渡里虽然很困惑, 不过也没有多问."},
    {LINE_WATARI, NULL, "\"...这样吗.\""},
    {LINE_NARRATION, NULL, "蕾德莉看着渡里失望的表情, 心中阵阵隐痛."},
    {LINE_THOUGHT, NULL,
     "(虽然很对不起渡里, 但是抱歉, 这件事果然不能让渡里知道呢.)"},
    {LINE_BREAK, NULL, NULL},
    {LINE_NARRATION, NULL, "待渡里离开, 蕾德莉起身开始收拾背包."},
    {LINE_RIDLEY, NULL,
     "\"OK, 上次生日的时候没有给渡里买到那家巧克力, 这一次我一定...\""},
    {LINE_NARRATION, NULL, "蕾德莉瞅了一眼钱袋, 只有 80 G."},
    {LINE_RIDLEY, NULL, "\"呜... 看来还要攒好久.\""},
    {LINE_NARRATION, NULL,
     "蕾德莉环顾周围, 确认渡里不在, 背上背包, 蹑手蹑脚走到了飞船出口."},
    {LINE_RIDLEY, NULL,
     "\"好. 那准备开始为渡里的生日巧克力攒钱吧! 我看看, 从哪里开始呢...\""}};

/* ---------- 2. 第 1~4 天晚间日常 (docs/day1.md ~ day4.md) ---------- */
static const struct StoryLine STORY_DAY1[] = {
    {LINE_NARRATION, NULL, "傍晚, 蕾德莉回到起居室, 飞快地把账本塞进枕头底下."},
    {LINE_RIDLEY, NULL, "\"呼... 第一天总算混过去了.\""},
    {LINE_NARRATION, NULL, "话音刚落, 门口就传来轻轻的脚步声."},
    {LINE_NARRATION, NULL, "渡里端着两杯热水站在那里, 静静地看着她."},
    {LINE_WATARI, NULL, "\"蕾德莉, 欢迎回来.\""},
    {LINE_RIDLEY, NULL, "\"呜哇?! 渡, 渡里! 你怎么站在那儿不出声啊?!\""},
    {LINE_NARRATION, NULL, "蕾德莉吓得差点跳起来."},
    {LINE_THOUGHT, NULL, "(糟了, 刚才自言自语没有被她听见吧?!)"},
    {LINE_NARRATION, NULL, "渡里没有追问, 走过来把其中一杯水递给蕾德莉."},
    {LINE_WATARI, NULL, "\"在等蕾德莉. 今天一个人忙了这么久, 是在做什么?\""},
    {LINE_RIDLEY, NULL,
     "\"啊, 那个... 接了点临时的跑腿工作! 很顺利, 哈哈...\""},
    {LINE_NARRATION, NULL, "蕾德莉慌忙接过水杯喝了一口, 差点被烫到舌头."},
    {LINE_NARRATION, NULL, "渡里静静看着她, 伸手轻轻碰了碰她的手背."},
    {LINE_WATARI, NULL, "\"...烫的话, 要吹一吹. 早点休息.\""}};

static const struct StoryLine STORY_DAY2[] = {
    {LINE_NARRATION, NULL,
     "夜里, 船舱的夜灯已经调暗. 蕾德莉躲在角落里, "
     "借着微弱的灯光小声核对着账本."},
    {LINE_RIDLEY, NULL, "\"这边的货款, 加上下一站的差价...\""},
    {LINE_NARRATION, NULL,
     "她一边对照航线和货单, 一边在纸上涂涂改改, 眉头拧成了一个结."},
    {LINE_NARRATION, NULL, "就在这时, 一件外套忽然从头顶罩了下来."},
    {LINE_RIDLEY, NULL, "\"呜哇, 怎么突然天黑了?!\""},
    {LINE_NARRATION, NULL, "蕾德莉掀开外套, 看见渡里正蹲在面前, 静静地盯着她."},
    {LINE_RIDLEY, NULL, "\"渡, 渡里?!\""},
    {LINE_NARRATION, NULL, "渡里伸手扯住蕾德莉的衣角, 轻轻晃了晃."},
    {LINE_WATARI, NULL, "\"蕾德莉这两天, 总是神神秘秘的, 也不带我一起.\""},
    {LINE_RIDLEY, NULL, "\"呃, 这个嘛... 因为是很重要的秘密任务!\""},
    {LINE_NARRATION, NULL, "蕾德莉竖起一根手指, 努力摆出严肃的表情."},
    {LINE_NARRATION, NULL, "渡里歪了歪头, 沉默了一会儿."},
    {LINE_WATARI, NULL, "\"...平时都是两个人一起的. 不能带我吗?\""},
    {LINE_NARRATION, NULL,
     "看着渡里认真又有点委屈的样子, 蕾德莉心里一下子软了下来."},
    {LINE_THOUGHT, NULL, "(呜... 被渡里这么盯着看, 差点就要说漏嘴了!)"},
    {LINE_RIDLEY, NULL,
     "\"再, 再等四天! 四天之后, 我一定第一个告诉你, 保证!\""},
    {LINE_NARRATION, NULL, "蕾德莉竖起四根手指发誓."},
    {LINE_NARRATION, NULL,
     "渡里盯着她的手指看了看, 伸出自己的小指, 轻轻勾了一下."},
    {LINE_WATARI, NULL, "\"...说好了. 拉钩.\""}};

static const struct StoryLine STORY_DAY3[] = {
    {LINE_NARRATION, NULL,
     "对着账本和星图忙了许久, 蕾德莉趴在桌子上, 眼皮直打架."},
    {LINE_RIDLEY, NULL, "\"星币...\""},
    {LINE_NARRATION, NULL, "她迷迷糊糊地嘟囔着."},
    {LINE_THOUGHT, NULL, "(藏在哪里... 渡里才不会发现...)"},
    {LINE_NARRATION, NULL,
     "渡里端着牛奶走过来, 看见趴在桌上的蕾德莉, 停住了脚步."},
    {LINE_NARRATION, NULL, "她把杯子轻轻放下, 绕到蕾德莉身边看了一会儿."},
    {LINE_NARRATION, NULL,
     "然后, 渡里伸出双手, 轻轻捧住蕾德莉的脸, 往中间挤了挤."},
    {LINE_RIDLEY, NULL, "\"唔... 渡里... 还差一点...\""},
    {LINE_NARRATION, NULL, "蕾德莉半梦半醒地念叨了一句, 顺势蹭了蹭渡里的掌心."},
    {LINE_NARRATION, NULL, "渡里动作一顿, 耳尖微微泛起一点红."},
    {LINE_WATARI, NULL, "\"...在说梦话.\""},
    {LINE_NARRATION, NULL,
     "她拿来一条薄毯盖在蕾德莉身上, 接着在旁边坐下, 轻轻靠在了她的肩膀上."},
    {LINE_WATARI, NULL, "\"...既然不让跟着, 那就在这里看着好了.\""}};

static const struct StoryLine STORY_DAY4[] = {
    {LINE_NARRATION, NULL, "蕾德莉把钱袋倒在床上, 仔细清点着里面的星币."},
    {LINE_RIDLEY, NULL, "\"明天就是最后一天了...\""},
    {LINE_NARRATION, NULL, "她收起钱袋, 深吸了一口气."},
    {LINE_THOUGHT, NULL,
     "(不管明天能攒到多少, 总之先全力以赴! 等收工之后, "
     "还要带渡里去温泉之星好好放松一下.)"},
    {LINE_NARRATION, NULL, "门被轻轻敲了两下, 渡里推门走了进来."},
    {LINE_WATARI, NULL, "\"蕾德莉, 今晚我来守夜.\""},
    {LINE_RIDLEY, NULL,
     "\"呃, 在船上不用守夜啦! 渡里, 明天等我忙完最后一点事, "
     "我们一起去温泉之星吧?\""},
    {LINE_NARRATION, NULL, "渡里微微一愣, 眨了眨眼."},
    {LINE_WATARI, NULL, "\"...温泉之星? 之前说过的那个?\""},
    {LINE_RIDLEY, NULL,
     "\"对! 这几天光顾着忙自己的事, 都没好好陪你, 真是抱歉.\""},
    {LINE_NARRATION, NULL, "蕾德莉不好意思地挠了挠头, 拍了拍身边的空位."},
    {LINE_NARRATION, NULL,
     "渡里走过来挨着她坐下, 沉默了一会儿, 轻轻把头靠在了蕾德莉肩上."},
    {LINE_WATARI, NULL, "\"...嗯. 很期待.\""},
    {LINE_THOUGHT, NULL,
     "(渡里这几天也忍耐很久了吧... 明天, 一定要画上一个完美的句号!)"}};

/* ---------- 3. 第 5 天温泉日常 (docs/day5_1.md ~ day5_4.md) ---------- */
static const struct StoryLine STORY_DAY5_1[] = {
    {LINE_NARRATION, NULL,
     "池边并排搁着两双鞋. 蕾德莉把脚伸进热水里, 听了一会儿泉声, "
     "脑子里却还在下意识算这几天的货价."},
    {LINE_RIDLEY, NULL, "\"买入二十五, 卖出五十... 啊不对, 我在想什么啊!\""},
    {LINE_NARRATION, NULL, "蕾德莉拍了拍脸颊, 往池沿一靠, 忍不住笑了出来."},
    {LINE_NARRATION, NULL,
     "一旁的渡里把半张脸埋在水面下, 只露出一双眼睛看着她, "
     "嘴里慢慢吐出一串水泡."},
    {LINE_WATARI, NULL, "\"咕噜... 咕噜噜...\""},
    {LINE_RIDLEY, NULL, "\"噗, 渡里别在水里吹泡泡啦, 呛到了怎么办!\""},
    {LINE_NARRATION, NULL,
     "蕾德莉伸手把她往池边拉了拉. 渡里顺势游过来, 安静地靠在了她手臂旁."},
    {LINE_THOUGHT, NULL, "(这五天的奔波, 好像在这一刻全都值了呢.)"}};

static const struct StoryLine STORY_DAY5_2[] = {
    {LINE_NARRATION, NULL, "渡里望向岸边, 抬手指向石缝里开着的几朵淡紫色小花."},
    {LINE_WATARI, NULL, "\"蕾德莉, 看那边. 紫色的.\""},
    {LINE_RIDLEY, NULL, "\"嗯? 那个花的名字我刚好知道哦!\""},
    {LINE_NARRATION, NULL,
     "蕾德莉有点得意地扬起下巴, "
     "把植物学家写在书签背面的花名一字不差地念了出来."},
    {LINE_NARRATION, NULL, "渡里眨了眨眼, 跟着小声念了一遍, 念到一半卡住了."},
    {LINE_WATARI, NULL, "\"...好长. 但是很好听.\""},
    {LINE_NARRATION, NULL,
     "两人隔着水汽凑在一起, 肩并着肩, 慢慢数起那几朵小花的花瓣."}};

static const struct StoryLine STORY_DAY5_3[] = {
    {LINE_NARRATION, NULL,
     "蕾德莉抬头看了眼夜空, 又低头望向池中. "
     "平静的温泉水面清晰地映出了几颗星星."},
    {LINE_NARRATION, NULL,
     "她一眼就认出了星图上印着的那一对, 立刻伸手指给渡里看."},
    {LINE_RIDLEY, NULL,
     "\"渡里你看, 那两颗挨在一起的星星, 是不是很像我们两个?\""},
    {LINE_NARRATION, NULL,
     "渡里顺着她指的方向看去, 盯着水面看了好一会儿, 轻轻点了点头."},
    {LINE_WATARI, NULL, "\"...嗯. 靠得很近.\""},
    {LINE_RIDLEY, NULL,
     "\"嘿嘿, 至于我为什么这么熟悉这片星空... 还是留到明天再告诉你吧!\""},
    {LINE_NARRATION, NULL,
     "渡里没有追问, 只是在水面下悄悄勾住了蕾德莉的手指."}};

static const struct StoryLine STORY_DAY5_4[] = {
    {LINE_BREAK, NULL, NULL},
    {LINE_NARRATION, NULL,
     "泡完温泉回到马车飞船, 蕾德莉趁渡里去擦头发的空档, "
     "悄悄拿出已经晾干的星图."},
    {LINE_NARRATION, NULL,
     "她沿着折痕把星图仔细折好, 再将那枚带着淡紫花瓣的干花书签轻轻夹了进去."}};

/* ---------- 4. 五颗星抵达事件 (planet0 / special1 / planet2 / special2 /
 * planet4) ---------- */
static const struct StoryLine EV_BOOK_INTRO[] = {
    {LINE_NARRATION, NULL,
     "一阵穿堂风灌进长廊, 吹散了馆员怀里泛黄的旧地球档案."},
    {LINE_NARRATION, NULL,
     "蕾德莉连忙上前按住几张纸页, 一枚带着淡紫花瓣的干花书签从里面滑了出来."},
    {LINE_NPC, "馆员", "\"哎呀, 熬夜赶工昏了头, 连窗户都忘了关...\""},
    {LINE_NARRATION, NULL, "馆员揉着太阳穴, 看着满地纸页直叹气."}};

static const struct StoryLine EV_BOOK_OPT1[] = {
    {LINE_RIDLEY, NULL, "\"我来帮你一起理吧!\""},
    {LINE_NARRATION, NULL,
     "蕾德莉按编号麻利地把档案码齐. 馆员松了口气, 递来 5 G, 又指了指那枚书签."},
    {LINE_NPC, "馆员", "\"这书签不在目录里, 算作谢礼送给你吧.\""},
    {LINE_THOUGHT, NULL,
     "(虽然只有 5 G, 不过这朵淡紫小花真好看, 回去给渡里看看.)"}};

static const struct StoryLine EV_BOOK_OPT2[] = {
    {LINE_RIDLEY, NULL, "\"纸页我来收, 这罐安神花茶你先拿去歇歇吧!\""},
    {LINE_NARRATION, NULL,
     "馆员闻了闻茶香, 神色一下子放松了不少, 爽快地付了 55 G, "
     "还把干花书签递给了蕾德莉."},
    {LINE_NPC, "馆员", "\"太及时了! 这书签不在馆藏里, 就当纪念留给你吧.\""},
    {LINE_THOUGHT, NULL, "(帮了大忙又赚了一笔, 这朵淡紫小花也收好吧!)"}};

static const struct StoryLine EV_FLOWER_INTRO[] = {
    {LINE_NARRATION, NULL,
     "路过植物研究所时, 蕾德莉正翻看着那枚干花书签, "
     "一位女植物学家突然叫住了她, 翻开怀里的旧地球图谱."},
    {LINE_NPC, "植物学家",
     "\"这页线稿缺了花色, 你书签上的花居然还留着一抹淡紫!\""},
    {LINE_NARRATION, NULL, "她迎光细看, 忽然低呼一声."},
    {LINE_NPC, "植物学家", "\"果荚里竟然还封着一粒完好的种子!\""}};

static const struct StoryLine EV_FLOWER_GIVE[] = {
    {LINE_RIDLEY, NULL,
     "\"如果它能在花之星重新发芽... 还是留给你更有意义吧!\""},
    {LINE_NARRATION, NULL,
     "植物学家如获至宝, 付了 15 G 科研酬金, "
     "还叫人替马车飞船装上了两层折叠货架."},
    {LINE_NARRATION, NULL, "货舱空间一下子从 5 格扩到了 7 格."},
    {LINE_THOUGHT, NULL,
     "(多了两个货位, 一定能更快攒够巧克力钱! 希望种子顺利发芽吧.)"}};

static const struct StoryLine EV_FLOWER_KEEP[] = {
    {LINE_RIDLEY, NULL,
     "\"抱歉, 这枚书签我想留给很重要的人看... 不过可以等你把颜色补完!\""},
    {LINE_NARRATION, NULL,
     "植物学家温和地笑了笑. 补完图谱花色后, 她付了 10 G 测绘费, "
     "又在书签背面写下一行花名还给蕾德莉."},
    {LINE_NPC, "植物学家", "\"这是它在旧地球时的名字. 祝你那位重要的人开心.\""},
    {LINE_THOUGHT, NULL, "(记住了! 等忙完这几天, 一定要念给渡里听.)"}};

static const struct StoryLine EV_CLOCK_INTRO[] = {
    {LINE_NARRATION, NULL,
     "老钟表匠刚撬开一座古董星象钟的表壳, 一把黄铜钥匙叮当滚落桌面."},
    {LINE_NARRATION, NULL,
     "蕾德莉凑近一看, 停摆的齿缝和星象盘上都沾着早已干涸的星光墨水."},
    {LINE_NPC, "老钟表匠",
     "\"发条积满灰了, 星象盘上的夜光刻度也全褪色了, "
     "偏偏铺里刚好断了星光墨水...\""}};

static const struct StoryLine EV_CLOCK_OPT1[] = {
    {LINE_RIDLEY, NULL, "\"清理发条我拿手, 交给我吧!\""},
    {LINE_NARRATION, NULL,
     "蕾德莉很快把表壳里的灰尘和旧墨渍擦得干干净净. 老钟表匠笑着递来 5 G, "
     "又推过那把钥匙."},
    {LINE_NPC, "老钟表匠",
     "\"这钥匙对不上锁孔, 倒像镜之星天文台的旧物件, 送你玩吧.\""},
    {LINE_THOUGHT, NULL,
     "(镜之星天文台的旧钥匙... 下次去镜之星时顺路看看吧.)"}};

static const struct StoryLine EV_CLOCK_OPT2[] = {
    {LINE_RIDLEY, NULL,
     "\"我船上正好带着星光墨水! 清理完发条, 顺手帮你把星象盘补描一下吧.\""},
    {LINE_NARRATION, NULL,
     "蕾德莉擦净齿缝, 沿着旧刻痕仔细填上新的星光墨水. 咔哒一声, "
     "星象钟重新走起节奏, 表盘泛起柔和的微光."},
    {LINE_NPC, "老钟表匠",
     "\"手艺真不赖! 这 70 G 是墨水钱和修表费, "
     "多出来的钥匙看着像镜之星天文台的, 一并送你吧.\""},
    {LINE_THOUGHT, NULL,
     "(嘿嘿, 科学家修个钟不在话下! 这把天文台钥匙... "
     "下次去镜之星时顺路看看吧.)"}};

static const struct StoryLine EV_MIRROR_INTRO_FIRST[] = {
    {LINE_NARRATION, NULL,
     "在天文台前, 巡夜的值夜人认出了蕾德莉手里的黄铜钥匙, "
     "便带她来到一台旧星轨仪前."},
    {LINE_NARRATION, NULL,
     "得到首肯后, 蕾德莉把钥匙探进锁孔轻轻一拧. 铜壳里响起两个清澈的音符, "
     "值夜人默契地熄了灯."},
    {LINE_NPC, "值夜人",
     "\"这台旧地球星轨仪失声几十年了... "
     "可惜用来留影的微缩胶卷槽早就空着了.\""}};

static const struct StoryLine EV_MIRROR_INTRO_REVISIT[] = {
    {LINE_NARRATION, NULL,
     "值夜人认出了再次归来的蕾德莉, 微笑着引她回到那台旧星轨仪前."},
    {LINE_NPC, "值夜人",
     "\"欢迎回来. 这次准备好启动星轨仪, 还是带了微缩胶卷来?\""}};

static const struct StoryLine EV_MIRROR_OPT1[] = {
    {LINE_RIDLEY, NULL, "\"钥匙本来就属于这里, 那就物归原主吧!\""},
    {LINE_NARRATION, NULL,
     "蕾德莉上紧发条. 星环缓缓转过一周, 断了数十年的八音盒终于奏完了整首曲子."},
    {LINE_NARRATION, NULL, "值夜人收下钥匙妥善保管, 鞠躬递来 15 G 谢礼."},
    {LINE_THOUGHT, NULL, "(曲子真好听呀... 好, 继续为渡里的生日加油!)"}};

static const struct StoryLine EV_MIRROR_OPT2[] = {
    {LINE_RIDLEY, NULL, "\"缺胶卷的话, 我随船正好带了一卷空白微缩胶卷!\""},
    {LINE_NARRATION, NULL,
     "蕾德莉装进胶卷, 上紧发条, 启动前偷偷把刻度拨到了渡里生日那天."},
    {LINE_NARRATION, NULL,
     "星环缓缓转动, 穹顶映出旧地球的星空, 快门轻响一声, "
     "中央那对紧挨着的星星稳稳留在了底片上."},
    {LINE_NPC, "值夜人", "\"光学留影机构居然完好! 这些旧星象数据太珍贵了!\""},
    {LINE_NARRATION, NULL,
     "值夜人收下钥匙, 郑重付了 80 G 报酬, "
     "又当场帮她把底片显影拓印成一张星图送给了她."},
    {LINE_NARRATION, NULL,
     "刚印好的星图还带着一点药水潮气, 蕾德莉小心卷好, 打算回船彻底晾干."},
    {LINE_THOUGHT, NULL,
     "(不但赚了 80 G, 还印到了渡里生日那天的星空... 到时候一定要指给她看!)"}};

static const struct StoryLine EV_MIRROR_OPT3[] = {
    {LINE_RIDLEY, NULL,
     "\"先别急着启动... 如果能带一卷空白微缩胶卷再来, "
     "说不定连留影机构也能一起醒过来!\""},
    {LINE_NARRATION, NULL, "值夜人点点头, 把黄铜钥匙重新递回她手里."},
    {LINE_NPC, "值夜人",
     "\"那这把钥匙先由你保管, 下次带了微缩胶卷再来找我吧.\""},
    {LINE_THOUGHT, NULL,
     "(太好了, 钥匙还留着! 去书之星带卷微缩胶卷再来试试!)"}};

static const struct StoryLine EV_LUCK_INTRO[] = {
    {LINE_NARRATION, NULL,
     "霓虹灯下, 占卜师朝蕾德莉招招手, 拨了一下金光闪闪的轮盘."},
    {LINE_NPC, "占卜师",
     "\"50 G 转一次. 赢了拿 80 G, 没中也有幸运徽章相赠. 试试手气吗?\""},
    {LINE_THOUGHT, NULL, "(要赌一把吗... 万一亏了, 渡里的巧克力可就悬了...)"}};

static const struct StoryLine EV_LUCK_DECLINE[] = {
    {LINE_RIDLEY, NULL, "\"谢谢好意, 我还是老实跑商吧!\""},
    {LINE_NARRATION, NULL,
     "蕾德莉捂着钱袋刚一转身, 就在石板缝里瞥见了一枚闪亮的 1 G 硬币."},
    {LINE_THOUGHT, NULL, "(不赌反倒白捡 1 G, 今天运气也不赖嘛!)"}};

static const struct StoryLine EV_LUCK_SPIN_INTRO[] = {
    {LINE_RIDLEY, NULL, "\"拼了, 就转这一次!\""},
    {LINE_NARRATION, NULL, "蕾德莉拍出 50 G 拨动轮盘, 紧张得屏住了呼吸."}};

static const struct StoryLine EV_LUCK_WIN[] = {
    {LINE_NARRATION, NULL,
     "指针稳稳停在金色星辉上, 占卜师鼓起掌, 推来 80 G 奖金."},
    {LINE_RIDLEY, NULL, "\"太好了! 净赚 30 G!\""},
    {LINE_THOUGHT, NULL, "(心跳差点停拍... 见好就收, 赶紧去市场!)"}};

static const struct StoryLine EV_LUCK_BADGE[] = {
    {LINE_NARRATION, NULL,
     "指针滑过金色格子, 停在四叶草上. 占卜师笑着递来一枚幸运徽章."},
    {LINE_RIDLEY, NULL, "\"呜... 差一点点啊...\""},
    {LINE_THOUGHT, NULL, "(算了, 拿去花之星应该能卖个好价钱!)"}};

static const struct StoryLine EV_LUCK_REFUND[] = {
    {LINE_NARRATION, NULL,
     "指针停在四叶草上. 占卜师瞥了眼她记满的货单, 耸耸肩数出 25 G."},
    {LINE_NPC, "占卜师", "\"货舱满了吧? 徽章就按折旧价换 25 G 现金给你.\""},
    {LINE_RIDLEY, NULL, "\"呜哇, 白亏 25 G!\""},
    {LINE_THOUGHT, NULL,
     "(早知道不贪心了... 对不起渡里, 接下来一定老老实实跑商!)"}};

/* ---------- 5. 结局 1：甜之星 (docs/ending1.md) ---------- */
static const struct StoryLine END1_PART1[] = {
    {LINE_NARRATION, NULL,
     "生日当天一早, 飞船降落在了空气里都飘着可可香气的甜之星."},
    {LINE_NARRATION, NULL,
     "蕾德莉掏出沉甸甸的钱袋, 豪气地付清了 720 G, "
     "把那盒系着丝带的巧克力抱进了怀里."},
    {LINE_RIDLEY, NULL, "\"太好了! 这一次终于买到了!\""},
    {LINE_NARRATION, NULL,
     "她一路小跑回到飞船, 把藏在身后的礼盒递到了刚醒来的渡里面前."},
    {LINE_RIDLEY, NULL, "\"渡里, 生日快乐!\""},
    {LINE_NARRATION, NULL,
     "渡里刚睡醒, 盯着面前的巧克力盒看了好几秒, 眨了眨眼."},
    {LINE_WATARI, NULL, "\"...巧克力?\""},
    {LINE_RIDLEY, NULL,
     "\"对啊! 我记得渡里最喜欢吃巧克力了. 上次生日没能买成, "
     "这次我可是特意攒够钱去买的!\""},
    {LINE_NARRATION, NULL, "蕾德莉得意地叉起腰, 鼻尖上还沾着一点甜之星的糖霜."},
    {LINE_NARRATION, NULL,
     "渡里低头看着礼盒, 沉默了一会儿, 突然把盒子往旁边一放, 伸手抱住了蕾德莉."},
    {LINE_RIDLEY, NULL, "\"呜哇?!\""},
    {LINE_NARRATION, NULL, "蕾德莉差点被扑倒在沙发上, 连忙伸手接住她."},
    {LINE_NARRATION, NULL,
     "渡里把脸埋在蕾德莉的颈窝里, 轻轻蹭了蹭, 声音闷闷的."},
    {LINE_WATARI, NULL, "\"...蕾德莉, 来回跑很累的.\""},
    {LINE_RIDLEY, NULL, "\"嘿嘿, 只要渡里喜欢就不累!\""},
    {LINE_NARRATION, NULL,
     "渡里抬起头, 脸颊微微泛红, 表情还是淡淡的. 她解开了礼盒上的丝带."}};

static const struct StoryLine END1_TOPIC_BOOKMARK[] = {
    {LINE_NARRATION, NULL,
     "一枚带着淡紫花瓣的干花书签从丝带底下滑了出来, 背面写着一行旧地球的花名."},
    {LINE_NARRATION, NULL, "渡里轻轻捏起书签看了看."},
    {LINE_WATARI, NULL, "\"...是昨晚岸边那种花.\""},
    {LINE_RIDLEY, NULL, "\"嗯! 在书之星捡到的, 特意留着想给渡里看看.\""}};

static const struct StoryLine END1_TOPIC_STARMAP[] = {
    {LINE_NARRATION, NULL,
     "一张折好的星图从丝带底下滑进她手里. 渡里沿着折痕展开, "
     "盯着中央那两颗紧挨着的星星."},
    {LINE_WATARI, NULL, "\"...是昨天那两颗.\""},
    {LINE_RIDLEY, NULL,
     "\"嘿嘿, 昨天不是说留到今天告诉你嘛! 那是用天文台的旧星轨仪印出来的, "
     "渡里生日那天的星空.\""},
    {LINE_NARRATION, NULL,
     "渡里抬起眼, 静静看了蕾德莉一会儿, 嘴角轻轻弯了一下."}};

static const struct StoryLine END1_TOPIC_BOTH[] = {
    {LINE_NARRATION, NULL,
     "一张折好的星图从丝带底下滑进她手里. 渡里沿着折痕展开, "
     "那枚淡紫色的干花书签正夹在两颗星星旁边."},
    {LINE_WATARI, NULL, "\"...是昨天那两颗. 还有岸边的小花.\""},
    {LINE_RIDLEY, NULL,
     "\"嘿嘿, 昨天不是说留到今天告诉你嘛! 那是用天文台的旧星轨仪印出来的, "
     "渡里生日那天的星空.\""},
    {LINE_NARRATION, NULL,
     "渡里把书签小心地夹回折痕里, 抬头看了蕾德莉一眼, 嘴角轻轻弯了一下."}};

static const struct StoryLine END1_PART2[] = {
    {LINE_NARRATION, NULL, "她从盒子里拿出一颗巧克力, 递到蕾德莉嘴边."},
    {LINE_WATARI, NULL, "\"...第一颗, 给蕾德莉.\""},
    {LINE_RIDLEY, NULL, "\"啊呜--唔, 好甜!\""},
    {LINE_NARRATION, NULL,
     "渡里自己也咬了一口, 嚼了嚼, 然后一言不发地重新靠回蕾德莉怀里, "
     "双手环住她的腰, 把下巴搁在了她的肩膀上."},
    {LINE_RIDLEY, NULL, "\"呃... 渡里? 巧克力不继续吃了吗?\""},
    {LINE_WATARI, NULL, "\"...等会儿再吃. 先靠一会儿.\""},
    {LINE_NARRATION, NULL,
     "说完, 她又往蕾德莉身边靠紧了一点, 一点松开的意思都没有."},
    {LINE_THOUGHT, NULL,
     "(虽然钱包一下子空了不少, 不过... 看着渡里这个样子, 什么都值了呢.)"}};

/* ---------- 6. 结局 2：纸之星 (docs/ending2.md) ---------- */
static const struct StoryLine END2_OPEN_NORMAL[] = {
    {LINE_NARRATION, NULL, "生日当天一早, 飞船缓缓降落在了静谧的纸之星."},
    {LINE_THOUGHT, NULL,
     "(虽然最后还是没攒够巧克力的钱, 有点不甘心... 不过, "
     "有些平时不好意思说出口的话, 亲手写下来送给渡里, 一定也很珍贵!)"}};

static const struct StoryLine END2_OPEN_RICH[] = {
    {LINE_NARRATION, NULL, "生日当天一早, 飞船缓缓降落在了静谧的纸之星."},
    {LINE_THOUGHT, NULL,
     "(虽然钱其实已经够买巧克力了... 不过, 有些平时不好意思说出口的话, "
     "亲手写下来送给渡里, 一定也很珍贵!)"}};

static const struct StoryLine END2_BUY_FULL[] = {
    {LINE_NARRATION, NULL,
     "蕾德莉付了 150 G, 在工坊里挑了一张带着淡淡植物清香的手作纸, "
     "回到船舱的桌前, 一笔一划认真地写了起来."}};

static const struct StoryLine END2_BUY_LOW[] = {
    {LINE_NARRATION, NULL,
     "蕾德莉掏出钱袋数了数, 离 150 G 还差一截. "
     "工坊老板听说她是给重要的人写生日信, 笑着只收下她手里的零钱, "
     "递来一张带着淡淡植物清香的手作纸."},
    {LINE_NARRATION, NULL,
     "她道过谢, 回到船舱的桌前, 一笔一划认真地写了起来."}};

static const struct StoryLine END2_BUY_ZERO[] = {
    {LINE_NARRATION, NULL,
     "蕾德莉翻开空空如也的钱袋, 局促得说不出话. "
     "工坊老板听说她是给重要的人写生日信, 笑着摆摆手, "
     "直接赠了她一张带着淡淡植物清香的手作纸."},
    {LINE_NARRATION, NULL,
     "她道过谢, 回到船舱的桌前, 一笔一划认真地写了起来."}};

static const struct StoryLine END2_MID[] = {
    {LINE_NARRATION, NULL, "没过多久, 门被轻轻推开, 渡里探进半个身子."},
    {LINE_WATARI, NULL, "\"蕾德莉? 飞船停下来了.\""},
    {LINE_RIDLEY, NULL, "\"啊, 刚好写完! 渡里, 生日快乐!\""},
    {LINE_NARRATION, NULL,
     "蕾德莉有些不好意思地挠了挠脸颊, 把折得工工整整的信纸递了过去."},
    {LINE_RIDLEY, NULL,
     "\"那个... 虽然这次没去买甜之星的巧克力, "
     "不过亲手写的生日信也很有心意吧... 希望渡里喜欢!\""},
    {LINE_NARRATION, NULL, "渡里接过信纸."}};

static const struct StoryLine END2_TOPIC_BOOKMARK[] = {
    {LINE_NARRATION, NULL,
     "信纸里还夹着一枚淡紫色的干花书签, 背面写着一行旧地球的花名."},
    {LINE_NARRATION, NULL, "渡里轻轻捏起书签看了看."},
    {LINE_WATARI, NULL, "\"...是昨晚岸边那种花.\""},
    {LINE_RIDLEY, NULL, "\"嗯! 在书之星捡到的, 特意留着想给渡里看看.\""}};

static const struct StoryLine END2_TOPIC_STARMAP[] = {
    {LINE_NARRATION, NULL,
     "信纸里还夹着一张折好的星图. 渡里把它轻轻展平, "
     "目光停在中央那两颗紧挨着的星星上."},
    {LINE_WATARI, NULL, "\"...是昨天那两颗.\""},
    {LINE_RIDLEY, NULL,
     "\"嘿嘿, 昨天不是说留到今天告诉你嘛! 那是用天文台的旧星轨仪印出来的, "
     "渡里生日那天的星空.\""},
    {LINE_NARRATION, NULL, "渡里轻轻点了点头, 把星图仔细折回原样."}};

static const struct StoryLine END2_TOPIC_BOTH[] = {
    {LINE_NARRATION, NULL,
     "信纸里还夹着一张折好的星图. 渡里把它轻轻展平, "
     "将滑出来的干花书签放回那两颗星星旁边."},
    {LINE_WATARI, NULL, "\"...是昨天那两颗. 还有岸边的小花.\""},
    {LINE_RIDLEY, NULL,
     "\"嘿嘿, 昨天不是说留到今天告诉你嘛! 那是用天文台的旧星轨仪印出来的, "
     "渡里生日那天的星空.\""},
    {LINE_NARRATION, NULL,
     "渡里静静看了蕾德莉一会儿, 把星图和书签一并仔细折好."}};

static const struct StoryLine END2_PART2[] = {
    {LINE_NARRATION, NULL, "她低下头, 非常认真地把信上的每一行字都读了一遍."},
    {LINE_NARRATION, NULL,
     "看完之后, 她把信纸小心翼翼地叠好, 贴身收进了胸前的口袋里, "
     "然后抬头直勾勾地看着蕾德莉."},
    {LINE_WATARI, NULL, "\"蕾德莉, 蹲下来一点.\""},
    {LINE_RIDLEY, NULL, "\"诶? 哦, 好...\""},
    {LINE_NARRATION, NULL,
     "蕾德莉刚一弯腰, 渡里就凑上来, 额头轻轻抵住了她的额头."},
    {LINE_RIDLEY, NULL, "\"唔?!\""},
    {LINE_NARRATION, NULL,
     "渡里的呼吸温温热热的, 脸上依旧没什么表情, 声音却很轻."},
    {LINE_WATARI, NULL, "\"...谢谢. 这个, 我很喜欢.\""},
    {LINE_RIDLEY, NULL, "\"真, 真的吗...\""},
    {LINE_NARRATION, NULL,
     "蕾德莉的脸瞬间红透了, 想往后退一点, 却被渡里伸手扯住了衣领."},
    {LINE_NARRATION, NULL,
     "渡里顺势向前一靠, 把脑袋搭在蕾德莉肩上, 整个人都贴了过来."},
    {LINE_WATARI, NULL, "\"...信上写了 '下次路过甜之星, 一起去买巧克力'.\""},
    {LINE_RIDLEY, NULL, "\"呜哇! 别, 别当面念出来啊!\""},
    {LINE_WATARI, NULL, "\"...嗯. 那我记住了.\""},
    {LINE_NARRATION, NULL,
     "她收紧手臂抱住蕾德莉, 闭上眼睛靠在她身上, 像是打算就这么赖着不走了."},
    {LINE_RIDLEY, NULL, "\"好, 好啦... 随你抱多久都行!\""},
    {LINE_THOUGHT, NULL,
     "(不过... 渡里这个样子, 感觉比送什么礼物都要开心呢!)"}};

/* ---------- 对外播放函数 ---------- */

int playBeginning(void)
{
  struct StoryContext ctx;

  storyBegin(&ctx, "序幕 - 距渡里生日还有五天");
  if (!storyPlayChunk(&ctx, STORY_BEGINNING, ARRAY_LEN(STORY_BEGINNING)))
  {
    return 0;
  }
  return storyWaitEnd();
}

int playDayNight(int day)
{
  struct StoryContext ctx;
  const struct StoryLine *lines = NULL;
  int count = 0;
  const char *title = "船舱夜晚";

  switch (day)
  {
  case 1:
    title = "Day 1 夜晚 - 两杯热水";
    lines = STORY_DAY1;
    count = ARRAY_LEN(STORY_DAY1);
    break;
  case 2:
    title = "Day 2 夜晚 - 拉钩";
    lines = STORY_DAY2;
    count = ARRAY_LEN(STORY_DAY2);
    break;
  case 3:
    title = "Day 3 夜晚 - 梦话与薄毯";
    lines = STORY_DAY3;
    count = ARRAY_LEN(STORY_DAY3);
    break;
  case 4:
    title = "Day 4 夜晚 - 温泉之约";
    lines = STORY_DAY4;
    count = ARRAY_LEN(STORY_DAY4);
    break;
  default:
    return 1;
  }

  storyBegin(&ctx, title);
  if (!storyPlayChunk(&ctx, lines, count))
  {
    return 0;
  }
  return storyWaitEnd();
}

int playHotSpring(const struct GameState *state)
{
  struct StoryContext ctx;
  int hasBookmark =
      (state != NULL) && ((state->flags & FLAG_TOPIC_BOOKMARK) != 0u);
  int hasStarmap =
      (state != NULL) && ((state->flags & FLAG_TOPIC_STARMAP) != 0u);

  storyBegin(&ctx, "Day 5 夜晚 - 温泉之星");
  if (!storyPlayChunk(&ctx, STORY_DAY5_1, ARRAY_LEN(STORY_DAY5_1)))
  {
    return 0;
  }
  if (hasBookmark)
  {
    if (!storyPlayChunk(&ctx, STORY_DAY5_2, ARRAY_LEN(STORY_DAY5_2)))
    {
      return 0;
    }
  }
  if (hasStarmap)
  {
    if (!storyPlayChunk(&ctx, STORY_DAY5_3, ARRAY_LEN(STORY_DAY5_3)))
    {
      return 0;
    }
  }
  if (hasBookmark && hasStarmap)
  {
    if (!storyPlayChunk(&ctx, STORY_DAY5_4, ARRAY_LEN(STORY_DAY5_4)))
    {
      return 0;
    }
  }
  return storyWaitEnd();
}

int playEnding(int choice, int moneyBeforeGift, int moneyAfterGift,
               unsigned int flags)
{
  struct StoryContext ctx;
  int hasBookmark = (flags & FLAG_TOPIC_BOOKMARK) != 0u;
  int hasStarmap = (flags & FLAG_TOPIC_STARMAP) != 0u;

  if (choice == GIFT_CHOCOLATE)
  {
    storyBegin(&ctx, "终章 - 甜之星的巧克力");
    if (!storyPlayChunk(&ctx, END1_PART1, ARRAY_LEN(END1_PART1)))
    {
      return 0;
    }
    if (hasBookmark && hasStarmap)
    {
      if (!storyPlayChunk(&ctx, END1_TOPIC_BOTH, ARRAY_LEN(END1_TOPIC_BOTH)))
      {
        return 0;
      }
    }
    else if (hasBookmark)
    {
      if (!storyPlayChunk(&ctx, END1_TOPIC_BOOKMARK,
                          ARRAY_LEN(END1_TOPIC_BOOKMARK)))
      {
        return 0;
      }
    }
    else if (hasStarmap)
    {
      if (!storyPlayChunk(&ctx, END1_TOPIC_STARMAP,
                          ARRAY_LEN(END1_TOPIC_STARMAP)))
      {
        return 0;
      }
    }
    if (!storyPlayChunk(&ctx, END1_PART2, ARRAY_LEN(END1_PART2)))
    {
      return 0;
    }
  }
  else
  {
    storyBegin(&ctx, "终章 - 纸之星的手作信");
    if (moneyBeforeGift >= TARGET_MONEY)
    {
      if (!storyPlayChunk(&ctx, END2_OPEN_RICH, ARRAY_LEN(END2_OPEN_RICH)))
      {
        return 0;
      }
    }
    else
    {
      if (!storyPlayChunk(&ctx, END2_OPEN_NORMAL, ARRAY_LEN(END2_OPEN_NORMAL)))
      {
        return 0;
      }
    }

    if (moneyBeforeGift >= PAPER_PRICE)
    {
      if (!storyPlayChunk(&ctx, END2_BUY_FULL, ARRAY_LEN(END2_BUY_FULL)))
      {
        return 0;
      }
    }
    else if (moneyBeforeGift > 0)
    {
      if (!storyPlayChunk(&ctx, END2_BUY_LOW, ARRAY_LEN(END2_BUY_LOW)))
      {
        return 0;
      }
    }
    else
    {
      if (!storyPlayChunk(&ctx, END2_BUY_ZERO, ARRAY_LEN(END2_BUY_ZERO)))
      {
        return 0;
      }
    }

    if (!storyPlayChunk(&ctx, END2_MID, ARRAY_LEN(END2_MID)))
    {
      return 0;
    }
    if (hasBookmark && hasStarmap)
    {
      if (!storyPlayChunk(&ctx, END2_TOPIC_BOTH, ARRAY_LEN(END2_TOPIC_BOTH)))
      {
        return 0;
      }
    }
    else if (hasBookmark)
    {
      if (!storyPlayChunk(&ctx, END2_TOPIC_BOOKMARK,
                          ARRAY_LEN(END2_TOPIC_BOOKMARK)))
      {
        return 0;
      }
    }
    else if (hasStarmap)
    {
      if (!storyPlayChunk(&ctx, END2_TOPIC_STARMAP,
                          ARRAY_LEN(END2_TOPIC_STARMAP)))
      {
        return 0;
      }
    }
    if (!storyPlayChunk(&ctx, END2_PART2, ARRAY_LEN(END2_PART2)))
    {
      return 0;
    }
  }

  if (!storyWaitEnd())
  {
    return 0;
  }

  drawEndingSummary(choice, moneyAfterGift, flags);
  return waitEnter(" 按 Enter 返回主菜单...");
}

/* ---------- 5 个星球抵达事件分段播放 ---------- */

int playBookEventIntro(struct StoryContext *ctx)
{
  storyBegin(ctx, "书之星事件 - 散落的旧书页");
  return storyPlayChunk(ctx, EV_BOOK_INTRO, ARRAY_LEN(EV_BOOK_INTRO));
}

int playBookEventBranch(struct StoryContext *ctx, int giveTea)
{
  if (giveTea)
  {
    return storyPlayChunk(ctx, EV_BOOK_OPT2, ARRAY_LEN(EV_BOOK_OPT2));
  }
  return storyPlayChunk(ctx, EV_BOOK_OPT1, ARRAY_LEN(EV_BOOK_OPT1));
}

int playFlowerEventIntro(struct StoryContext *ctx)
{
  storyBegin(ctx, "花之星事件 - 跨星海的标本");
  return storyPlayChunk(ctx, EV_FLOWER_INTRO, ARRAY_LEN(EV_FLOWER_INTRO));
}

int playFlowerEventBranch(struct StoryContext *ctx, int giveBookmark)
{
  if (giveBookmark)
  {
    return storyPlayChunk(ctx, EV_FLOWER_GIVE, ARRAY_LEN(EV_FLOWER_GIVE));
  }
  return storyPlayChunk(ctx, EV_FLOWER_KEEP, ARRAY_LEN(EV_FLOWER_KEEP));
}

int playClockEventIntro(struct StoryContext *ctx)
{
  storyBegin(ctx, "钟之星事件 - 停摆的古董钟");
  return storyPlayChunk(ctx, EV_CLOCK_INTRO, ARRAY_LEN(EV_CLOCK_INTRO));
}

int playClockEventBranch(struct StoryContext *ctx, int giveInk)
{
  if (giveInk)
  {
    return storyPlayChunk(ctx, EV_CLOCK_OPT2, ARRAY_LEN(EV_CLOCK_OPT2));
  }
  return storyPlayChunk(ctx, EV_CLOCK_OPT1, ARRAY_LEN(EV_CLOCK_OPT1));
}

int playMirrorEventIntro(struct StoryContext *ctx, int isRevisit)
{
  storyBegin(ctx, "镜之星事件 - 星轨仪的余音");
  if (isRevisit)
  {
    return storyPlayChunk(ctx, EV_MIRROR_INTRO_REVISIT,
                          ARRAY_LEN(EV_MIRROR_INTRO_REVISIT));
  }
  return storyPlayChunk(ctx, EV_MIRROR_INTRO_FIRST,
                        ARRAY_LEN(EV_MIRROR_INTRO_FIRST));
}

int playMirrorEventBranch(struct StoryContext *ctx, int option)
{
  if (option == 2)
  {
    return storyPlayChunk(ctx, EV_MIRROR_OPT2, ARRAY_LEN(EV_MIRROR_OPT2));
  }
  if (option == 3)
  {
    return storyPlayChunk(ctx, EV_MIRROR_OPT3, ARRAY_LEN(EV_MIRROR_OPT3));
  }
  return storyPlayChunk(ctx, EV_MIRROR_OPT1, ARRAY_LEN(EV_MIRROR_OPT1));
}

int playLuckEventIntro(struct StoryContext *ctx)
{
  storyBegin(ctx, "运之星事件 - 街角的命运轮");
  return storyPlayChunk(ctx, EV_LUCK_INTRO, ARRAY_LEN(EV_LUCK_INTRO));
}

int playLuckEventDecline(struct StoryContext *ctx)
{
  return storyPlayChunk(ctx, EV_LUCK_DECLINE, ARRAY_LEN(EV_LUCK_DECLINE));
}

int playLuckEventSpinIntro(struct StoryContext *ctx)
{
  return storyPlayChunk(ctx, EV_LUCK_SPIN_INTRO, ARRAY_LEN(EV_LUCK_SPIN_INTRO));
}

int playLuckEventSpinOutcome(struct StoryContext *ctx, enum LuckOutcome outcome)
{
  if (outcome == LUCK_WIN)
  {
    return storyPlayChunk(ctx, EV_LUCK_WIN, ARRAY_LEN(EV_LUCK_WIN));
  }
  if (outcome == LUCK_BADGE)
  {
    return storyPlayChunk(ctx, EV_LUCK_BADGE, ARRAY_LEN(EV_LUCK_BADGE));
  }
  return storyPlayChunk(ctx, EV_LUCK_REFUND, ARRAY_LEN(EV_LUCK_REFUND));
}
/* ==================== [Antigravity 生成 结束] ==================== */
