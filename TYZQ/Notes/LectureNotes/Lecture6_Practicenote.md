# UESTC1005 · Lecture 1–6 综合实战学习笔记

> **项目名称**：LECVS — Component Vending System（电子元件自助售货系统）  
> **项目源文件**：`LECVS.c`  
> **学习范围**：Lecture 1–6；暂不涉及 Lecture 7 的数组传参和排序算法  
> **笔记结构**：项目目标 → 功能与思路 → 核心代码 → 知识点 → 易错点 → 测试复盘 → 总结

---

## 一、项目目标与功能要求

实现一个通过命令行交互的电子元件售货系统。程序应在用户主动选择退出前持续运行，并记住最新库存与销售统计。

```text
===== Component Vending System =====
1. View Products
2. Buy Components
3. Random Restock
4. Sales Report
5. Inventory Chart
0. Exit
====================================
```

| 选项 | 功能 | 核心知识点 |
|---|---|---|
| 1 | 商品信息显示 | 一维数组、`for`、函数调用、格式化输出 |
| 2 | 购买商品、付款、找零、更新统计 | `if`、`switch`、数组、状态管理、递归 |
| 3 | 随机补货，库存上限 20 | `rand()`、`srand()`、`for`、条件判断 |
| 4 | 销售报告及访问次数 | 累加、`static` 局部变量 |
| 5 | 用 `*` 绘制当前库存 | 嵌套 `for` 循环 |
| 0 | 结束程序 | `do-while` 循环条件 |

初始商品数据：

| ID | 名称 | 单价（cents） | 初始库存 |
|---|---|---:|---:|
| 1 | Resistor | 150 | 5 |
| 2 | Capacitor | 200 | 4 |
| 3 | LED | 350 | 6 |
| 4 | Diode | 500 | 3 |
| 5 | Transistor | 800 | 2 |

**设计约定**：价格使用整数 cents（分）表示；商品 ID 为 `1`～`5`，数组下标为 `0`～`4`。本项目不处理文件保存，退出后运行时数据不会自动保留。

---

## 二、程序结构与功能分解

### 2.1 头文件与宏

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ITEM_COUNT 5
```

- `<stdio.h>`：`printf()`、`scanf()`。
- `<stdlib.h>`：`rand()`、`srand()`。
- `<time.h>`：`time(NULL)`。
- `#define ITEM_COUNT 5`：商品种类数。遍历数组、检查商品编号时统一使用宏，而非硬编码 `5`。

### 2.2 函数原型与定义

```c
void print_menu(void);
void print_product_name(int id);
int count_change_coins(int change);
```

- `print_menu()`：只负责打印主菜单，无参数、无返回值。
- `print_product_name(int id)`：根据 ID 输出商品名称，`switch` 中的 `case` 对应不同商品。
- `count_change_coins(int change)`：递归计算按最大面额优先找零的硬币数，返回 `int`。

**复习：**函数原型放在 `main()` 之前，函数定义可以放在 `main()` 之后。调用者只需先看到合法的声明。

### 2.3 总体控制流程

```text
启动
  ↓
初始化价格、库存、销量、收入、交易次数及随机种子
  ↓
显示菜单 → 读取 choice
  ↓
switch(choice)
  ├── 1: 查看商品
  ├── 2: 购买、付款、提交交易
  ├── 3: 随机补货
  ├── 4: 销售报告
  ├── 5: 库存图
  ├── 0: 退出
  └── 其他: Invalid choice!
  ↓
choice != 0 ? 是 → 返回菜单；否 → 结束
```

采用 `do-while`，因为菜单必须至少显示一次：

```c
do
{
    print_menu();

    if (scanf("%d", &choice) != 1)
    {
        printf("Input error.\n");
        return 1;
    }

    switch (choice)
    {
        // Individual cases...
    }

} while (choice != 0);
```

**重要区别**：`case` 中的 `break` 结束当前 `switch`，但不会直接跳出外层 `do-while`；因此执行正常菜单操作后还能再次显示菜单。

---

## 三、核心数据设计：状态管理（State Management）

在 `main()` 中、主菜单循环外声明：

```c
const int price[ITEM_COUNT] = {150, 200, 350, 500, 800};
int stock[ITEM_COUNT] = {5, 4, 6, 3, 2};
int sold[ITEM_COUNT] = {0, 0, 0, 0, 0};

int revenue = 0;
int transactions = 0;
```

| 变量 | 数据含义 | 何时修改 |
|---|---|---|
| `price[i]` | 第 `i+1` 种商品的单价 | 项目中不修改，因此使用 `const` |
| `stock[i]` | **当前**剩余库存 | 成功购买时减少，随机补货时增加 |
| `sold[i]` | **累计**卖出的该种商品件数 | 仅成功购买时增加 |
| `revenue` | 所有成功订单的累计销售额 | 仅成功购买时增加订单总价 |
| `transactions` | 成功交易笔数 | 每笔成功交易加 1，与购买件数不同 |

**关键概念：当前状态与历史累计数据不是同一个东西。**

```text
购买 2 件： stock -= 2；sold += 2；revenue += 订单金额；transactions++
补货 3 件： stock += 3；sold、revenue、transactions 不变
查看报告：不改变以上四类销售/库存数据
```

库存守恒关系（无其他库存损耗时）：

`当前库存 = 初始库存 + 累计补货量 - 累计销量`

**为什么变量放在菜单循环外？** 如果每次循环都重新声明并初始化数组和统计变量，会丢失上一笔交易的结果。

---

## 四、功能实现核心知识点

### 4.1 View Products：数组下标、循环和格式化输出

```c
for (int i = 0; i < ITEM_COUNT; i++)
{
    printf("%-6d %-16d %-10d", i + 1, price[i], stock[i]);
    print_product_name(i + 1);
}
```

- `i` 从 `0` 开始，确保满足 `i < ITEM_COUNT`，最后一次访问 `price[4]` 与 `stock[4]`。
- `i + 1` 把数组下标转换成面向用户的商品编号。
- `%-6d` 表示整数**左对齐**，最小字段宽度为 6。
- 第一条 `printf()` 不换行，`print_product_name()` 打印名称时通过 `\n` 完成该行。

> 易错：用户输入 `id = 5` 对应下标 `4`；不能直接用 `stock[id]`。

### 4.2 Buy Components：验证后再提交（Validate → Commit）

购买流程：

1. 输入商品编号并检查 `1 <= id <= ITEM_COUNT`。
2. 将 `id` 转换为 `id_index = id - 1`。
3. 输入数量，要求 `quantity > 0`。
4. 检查 `stock[id_index] >= quantity`。
5. 计算 `total_price = price[id_index] * quantity`。
6. 读取付款 `payment`，要求 `payment >= total_price`。
7. 计算 `change = payment - total_price` 并通过函数计算找零硬币数量。
8. **仅全部检查通过以后**更新库存、销量、收入和交易次数。

核心代码：

```c
if (payment < total_price)
{
    printf("Insufficient payment!\n");
    break;
}

int change = payment - total_price;
int coins = count_change_coins(change);

printf("Payment accepted!\n");
printf("Change: %d cents\n", change);
printf("Coins needed: %d\n", coins);

stock[id_index] -= quantity;
sold[id_index] += quantity;
revenue += total_price;
transactions++;
```

**数据一致性规则**：库存不足、数量不合法或付款不足时，均不得更新这些状态。`revenue` 加的是**订单总价**，不是包括找零在内的顾客付款额。

**为什么 `case 2` 用花括号？**

```c
case 2:
{
    int id;
    int quantity;
    // ...
    break;
}
```

C11 中 `case` 标签之后不能直接跟一个声明，花括号让 `case` 后面紧跟合法的复合语句，同时限制局部变量的作用域。花括号结束**不等于** `switch` 结束，成功处理之后仍须 `break`。

### 4.3 Random Restock：伪随机数与边界检查

```c
srand((unsigned int)time(NULL));  // At startup, once only
```

在 `case 3` 中每件商品依次执行：

```c
const int max_stock = 20;

for (int i = 0; i < ITEM_COUNT; i++)
{
    int replenishment_quantity = rand() % 4;

    if (stock[i] + replenishment_quantity > max_stock)
    {
        replenishment_quantity = max_stock - stock[i];
    }

    stock[i] += replenishment_quantity;
    printf("Product %d: +%d\n", i + 1, replenishment_quantity);
}
```

- `rand() % 4`：生成 `0、1、2、3` 之一（伪随机、取模可能产生轻微分布偏差）。
- `srand()` 为随机数生成器设置种子，在本程序启动时设置一次；每次补货不应重新使用相同种子。
- 输出**实际允许补充的数量**，而非原始随机数。
- `stock[i] == 20` 时实际补货为 0。

### 4.4 Sales Report：数组统计和 `static`

```c
case 4:
{
    static int report_views = 0;
    report_views++;

    int total_sold = 0;
    int remaining_stock = 0;

    for (int i = 0; i < ITEM_COUNT; i++)
    {
        total_sold += sold[i];
        remaining_stock += stock[i];
    }

    printf("Total Revenue: %d cents\n", revenue);
    printf("Items Sold: %d\n", total_sold);
    printf("Transactions: %d\n", transactions);
    printf("Remaining Stock: %d\n", remaining_stock);
    printf("Report Viewed: %d times\n", report_views);
    break;
}
```

- `total_sold`、`remaining_stock` 为普通局部变量，每次查看报告时从 `0` 重新统计**最新数组数据**。
- `static int report_views = 0;` 具有静态存储期，只初始化一次，离开 `case 4` 后数值仍保留。
- `report_views` 仍具有所在代码块的局部作用域；**作用域（Scope）和存储期（Storage Duration）不同**。

例：菜单输入 `4 → 4 → 1 → 4 → 0`，查看次数应依次为 `1、2、3`。

### 4.5 Inventory Chart：嵌套循环

```c
for (int i = 0; i < ITEM_COUNT; i++)
{
    printf("Product %d: ", i + 1);

    for (int j = 0; j < stock[i]; j++)
    {
        printf("*");
    }

    printf("\n");
}
```

- 外层 `i`：切换商品，一共遍历 `ITEM_COUNT` 种商品。
- 内层 `j`：按当前 `stock[i]` 数量输出星号。
- `printf("\n")` 必须放在**内层循环后、外层循环内**。
- 库存为 `0` 时内层循环执行零次，但该商品行依然会显示。
- 图表不维护独立副本，而是直接读取最新库存，避免不同模块的数据不同步。

### 4.6 Recursive Change Calculator：递归找零

原文件实现的函数如下（仅统一代码排版）：

```c
int count_change_coins(int change)
{
    if (change == 0)
    {
        return 0;  // Base Case
    }

    if (change >= 100)
    {
        return 1 + count_change_coins(change - 100);
    }
    if (change >= 50)
    {
        return 1 + count_change_coins(change - 50);
    }
    if (change >= 20)
    {
        return 1 + count_change_coins(change - 20);
    }
    if (change >= 10)
    {
        return 1 + count_change_coins(change - 10);
    }
    if (change >= 5)
    {
        return 1 + count_change_coins(change - 5);
    }
    if (change >= 1)
    {
        return 1 + count_change_coins(change - 1);
    }

    return -1;  // Invalid negative input
}
```

- **Base Case**：`change == 0`，无须硬币，直接返回 `0`。
- **Recursive Case**：优先选择当前可用的最大面额硬币，`return 1 + count_change_coins(剩余金额)`。
- 每层都减少 `change`，因此在非负整数输入范围内最终到达基准情形。
- `return -1` 处理负数输入，保证 `int` 函数所有路径均有返回值。
- 这是**最大面额优先策略**，不能将这种思路不加证明地套用到任意硬币面额系统。

**示例：**找零 175 cents。

```text
count_change_coins(175)
= 1 + count_change_coins(75)     // 100
= 1 + 1 + count_change_coins(25) // 50
= 1 + 1 + 1 + count_change_coins(5) // 20
= 1 + 1 + 1 + 1 + count_change_coins(0) // 5
= 4
```

递归的两个阶段：**深入调用**直到遇到基准情形；然后**逐层返回**结果。对于本函数，当找零数额非常大时，深层递归可能耗尽调用栈空间。

---

## 五、开发过程中实际出现的易错点

| 问题 | 触发原因 | 本次解决方法 |
|---|---|---|
| Clang 提示 `Label followed by a declaration is a C23 extension` | 在较旧 C 标准中，`case` 标签后直接写声明 | 在 `case 2:` 后使用 `{ ... }` 复合语句 |
| 成功分支漏掉 `break` 可能执行下一个 `case` | `}` 不会自动结束 `switch` | 每个完整的 `case` 分支都明确处理退出方式 |
| 数组下标越界 | 用户商品 ID 从 1 开始，数组下标从 0 开始 | 先验证 `id`，再使用 `id - 1` |
| `scanf()` 读取失败 | 输入非整数时，读取变量可能未初始化 | 判断 `scanf("%d", &x) != 1`，当前方案报错并退出程序 |
| 付款失败却修改库存 | 将状态更新放在验证前 | **先验证，后提交** |
| `revenue` 错加付款金额 | 忘记找零不属于销售收入 | 只累加 `total_price` |
| 误把补货算作销量 | 混淆当前库存与历史记录 | 补货只修改 `stock[]` |
| `static` 与普通局部变量混淆 | 没区分存储期与作用域 | `report_views` 使用 `static`，每次报告统计用普通变量 |
| `rand()` 每次选择菜单都重新设种子 | 随机数生成器初始化位置错误 | `srand(...)` 只在主菜单循环之前运行一次 |
| 显示格式不整齐 | `printf` 字段宽度和换行位置不统一 | 使用 `%-Nd` 左对齐，名称函数负责结尾换行 |
| 递归函数末尾缺少 `return` | 没有处理负数输入路径 | 在函数末尾 `return -1;` |

**补充注意（超出当前作业正常输入范围）**：`total_price = price[id_index] * quantity`、`change = payment - total_price`、`revenue += total_price` 都使用 `int`，极大整数输入存在有符号溢出风险；真实项目需要金额上限、溢出检查和更完整的输入恢复机制。这不是本次代码已经实现的能力。

---

## 六、测试与验收记录

已用 GCC C11 严格选项重新编译原文件：

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror LECVS.c -o LECVS
```

在当前环境中编译通过。实测输入操作序列：

```text
2 → Product ID 1 → Quantity 1 → Payment 325
4 → 4 → 5 → 0
```

得到关键结果：

```text
Total: 150 cents
Change: 175 cents
Coins needed: 4

Total Revenue: 150 cents
Items Sold: 1
Transactions: 1
Remaining Stock: 19
Report Viewed: 1 times

Report Viewed: 2 times

Product 1: ****
Product 2: ****
Product 3: ******
Product 4: ***
Product 5: **
```

测试说明：商品 1 初始库存为 5，成功购买 1 件后库存为 4；总库存由 20 变为 19。商品 1 的销售收入为 150 cents，顾客支付的 325 cents 中有 175 cents 是找零。两次查看报告令 `report_views` 由 1 变为 2。

### 进一步自测清单

- [ ] 无效商品编号 `8`：输出错误，不询问数量。
- [ ] 购买数量 `0` 或负数：拒绝订单。
- [ ] 库存不足：拒绝订单，不询问付款。
- [ ] 付款不足：不改变库存、销量、收入、交易次数。
- [ ] 恰好付款：`change = 0`，`Coins needed = 0`。
- [ ] 成功购买两次：库存连续递减，交易次数累计。
- [ ] 补货多次：每种商品库存始终不超过 20。
- [ ] 库存为 0：库存图只打印商品名称，不打印星号。
- [ ] 多次查看报告：查看次数累计，销售统计不因查看而改变。

---

## 七、最后的知识点速记

| 知识点 | 一句话记忆 |
|---|---|
| `do-while` | 先执行一次循环体，再判断是否继续。 |
| `switch` / `break` | `break` 退出最近的循环或 `switch`；普通 `{}` 不会阻止贯穿执行。 |
| 一维数组 | 同类型连续存储；下标从 0 开始。 |
| `const` | 通过该变量名不允许修改其值。 |
| 形参与实参 | 普通 `int` 参数按值传递，形参是独立副本。 |
| `static` 局部变量 | 作用域仍为局部，但数值能在不同次进入代码块后保持。 |
| `rand()` / `srand()` | 先设置种子，再生成伪随机数；同种子重现相同序列。 |
| 嵌套循环 | 外层控制对象，内层控制每个对象内部的重复工作。 |
| 递归 | 必须有基准情形，并确保每次递归让问题接近基准情形。 |
| 状态更新 | 先全部验证，再修改共享的业务数据。 |

### 自己可以默写的四段核心代码

1. 商品 ID 验证、转换为 `id - 1`，并安全访问数组。
2. 检查付款后更新 `stock`、`sold`、`revenue`、`transactions`。
3. 一个 `for` 循环完成 `total_sold` 与 `remaining_stock` 的累加。
4. 递归找零函数：基准情形 + 最大面额优先的递归情形。

---

## 八、项目总结与下一阶段边界

**本项目完成的能力**：自己维护多个数组中的关联数据；把一个整体需求拆成多个独立菜单模块；保证失败交易不影响系统状态；利用 `static` 保留历史计数；使用循环和递归解决不同类型的重复问题。

**尚未学习或实现**：将数组传入函数、排序算法、结构体表示商品、文件持久化存储、全面的输入异常恢复、真实货币支付与大型金额安全处理。

**学习进度**：Lecture 1–6 综合实战完成；**暂不进入 Lecture 7**。

> 最重要的一句话：程序不仅要计算结果，还要维护正确的状态——**先验证条件，再修改数据；当前状态与历史累计数据必须明确分开。**
