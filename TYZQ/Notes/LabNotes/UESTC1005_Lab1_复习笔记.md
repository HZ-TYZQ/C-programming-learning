# UESTC1005 · Lab 1 复习笔记

**课程**：Introductory Programming（2026–2027 S1）  
**主题**：Lab 1 — Number Property Explorer  
**资料依据**：`lab 1 learning guide.pdf`、`lab 1 exercise sheet.pdf`（2026–2027 版），以及本次学习中使用的官方 `.c` Base Code。  
**完成情况**：Exercise A CodeGrade 12/12；Exercise B 本地测试 7/7；Exercise C CodeGrade 12/12。

---

## 0. 学习地图

| Learning Guide | Check Point | 应用 |
|---|---|---|
| §1 Variables and Operations | CP01 Arithmetic；CP02 Digit Extraction | Exercise A — Three-Digit Number Analyzer |
| §2 Branches | CP03 Logical Operators；CP04 if；CP05 switch | 输入判断和分支 |
| §3 Functions | 函数定义、参数、返回值和声明 | Exercise B — Armstrong Number Function |
| §4 Loops | CP06 while；CP07 for | Exercise C — Armstrong Number Explorer |

**贯穿三题的主线**：整数数位提取 → 判断 Armstrong Number → 在一段范围内重复判断并统计结果。

## 1. Variables and Operations

### 1.1 数据类型与输入输出

| 类型 | 作用 | `printf` | `scanf` |
|---|---|---|---|
| `int` | 整数 | `%d` | `%d` |
| `float` | 单精度浮点数 | `%f` | `%f` |
| `double` | 双精度浮点数 | `%f` | `%lf` |
| `char` | 单字符 | `%c` | `%c` |
| 文本（讲义列为 *string*） | 字符序列 | `%s` | `%s` |

> **补充澄清**：讲义在入门表格中列出了 *string*；严格来说，标准 C 没有内建的 `string` 基本类型，通常用 `char` 数组处理字符串。本 Lab 只需认识 `%s`。

```c
int number;
printf("Enter a three-digit number: ");
scanf("%d", &number);       // &number：传入变量地址
printf("Number: %d\n", number);
```

### 1.2 运算符：`+ - * / % ++ --`

- 整数之间的 `/`：执行整数除法，丢弃小数部分（本实验均为非负整数）。
- `%`：得到整数除法的余数。
- `++`、`--`：加一、减一。
- 乘除取余优先于加减；复杂表达式使用括号明确分组。

| 表达式（CP01） | 结果 | 类型 |
|---|---:|---|
| `23 / 10` | `2` | `int` |
| `23 % 10` | `3` | `int` |
| `23 / 5` | `4` | `int` |
| `23.0 / 5.0` | `4.6` | `double` |

```c
double wrong = 11 / 3;        // 3.0：右边先进行整数除法
double right = 11 / 3.0;      // 3.666...：浮点除法
```

`printf("%.2f\n", right);` 可将结果显示为两位小数。

### 1.3 提取三位整数的数位（CP02）

```c
int hundreds = number / 100;
int tens = (number / 10) % 10;
int ones = number % 10;
```

当 `number = 371`：百位 `3`、十位 `7`、个位 `1`。

**右到左逐位提取通法**：

```c
while (number > 0) {
    int digit = number % 10; // 当前个位
    // 处理 digit
    number = number / 10;    // 删除个位
}
```

## 2. Exercise A — Three-Digit Number Analyzer

**任务**：输入一个三位正整数，计算百十个位、各位和、各位积、反转后的整数和数位平均值。讲义规定输入为 100–999，不要求输入验证；不得随意修改给定的输入输出语句。

```c
hundreds = number / 100;
tens = (number / 10) % 10;
ones = number % 10;

digit_sum = hundreds + tens + ones;
digit_product = hundreds * tens * ones;
reversed = ones * 100 + tens * 10 + hundreds;
average = digit_sum / 3.0;
```

**例子**：输入 `371` 时，数位和 `11`、积 `21`、反转 `173`、平均值 `3.67`。输入 `100` 时，反转结果是整数 `1` 而不是 `001`：整数不保留前导零。

**典型错误**：`average = digit_sum / 3` 先进行了整数除法；必须使用 `3.0`。平均值按要求用 `%.2f` 显示。

**结果**：CodeGrade AutoTest 12/12。

## 3. Branches — 条件分支

### 3.1 比较与逻辑

| 运算符 | 含义 |
|---|---|
| `<`, `<=`, `>`, `>=` | 大小关系 |
| `==`, `!=` | 相等、不等 |
| `&&` | AND（与） |
| `||` | OR（或） |
| `!` | NOT（非） |

不要混淆 `=`（赋值）与 `==`（比较）。

```c
// 合法：100 到 999（含两端）
number >= 100 && number <= 999

// 非法：不在三位数范围内
number < 100 || number > 999
```

**注意**：数学中的 `100 <= number <= 999` 不能直接作为 C 语言的区间判断；需拆成两个条件，用 `&&` 连接。

### 3.2 优先级与短路（CP03）

讲义列出的优先级高到低：后缀 `++`/`--` → `!` → `* / %` → `+ -` → 大小比较 → 相等比较 → `&&` → `||`。

```c
1 || 0 && 0       // 1；等价于 1 || (0 && 0)
(1 || 0) && 0     // 0
1 || (0 && 0)     // 1

2 + 3 * 4 == 20                  // 0
8 % 3 == 2 && 6 / 2 > 3        // 0
!0 || 4 < 2                    // 1
```

**短路求值（Short-circuit）**：

```c
int x = 0;
int a = 0 && ++x;     // a=0、x=0；右侧不执行

int y = 0;
int b = 1 || ++y;     // b=1、y=0；右侧不执行
```

`&&` 左侧为假时不检查右侧；`||` 左侧为真时不检查右侧。优先级决定表达式分组，不等于普遍的求值顺序。

### 3.3 if / else if / else（CP04）

```c
if (number < 100) {
    printf("The number is too small.\n");
} else if (number > 999) {
    printf("The number is too large.\n");
} else {
    printf("Valid three-digit number.\n");
}
```

同一条 `if` / `else if` / `else` 链从上往下选择第一个匹配分支。

### 3.4 switch / case / break / default（CP05）

```c
switch (choice) {
    case 'A':
        printf("Analyse digits\n");
        break;
    case 'C':
        printf("Check Armstrong number\n");
        break;
    default:
        printf("Unknown choice\n");
        break;
}
```

- `case 'A':`：使用单引号表示字符常量，不能写为 `case "A":`。
- `default:`：所有 `case` 都不匹配时从这里执行。
- `break;`：防止 Fall-through（落入后续分支）。
- 读入单字符时，讲义文件使用 `scanf(" %c", &choice);`，前导空格跳过换行及其他空白字符。

## 4. Functions — 函数（§3）

### 4.1 函数定义、参数、返回值

```c
int is_positive(int value)
{
    return value > 0;
}
```

- `int`：return type（返回类型）。
- `is_positive`：function name（函数名称）。
- `int value`：parameter（形式参数）。
- `return value > 0;`：把比较结果返回给调用者，真为 `1`，假为 `0`。
- 调用 `is_positive(number)` 时，`number` 是 argument（实际参数）。

调用示例：

```c
if (is_positive(number)) {
    printf("Positive\n");
}
```

### 4.2 Prototype（函数原型）与 Definition（函数定义）

如果函数定义写在调用它的 `main` 之后，需要在调用前提供声明：

```c
int is_positive(int value);  // 声明：以分号结束

int main(void) {
    return is_positive(5);
}

int is_positive(int value) {  // 定义：有函数体
    return value > 0;
}
```

多文件开发中，`armstrong.h` 保存 `int is_armstrong_number(int number);` 的声明，`armstrong_checker.c` 保存函数定义，其他源文件通过 `#include "armstrong.h"` 使用声明。

## 5. Exercise B — Armstrong Number Function

**定义**：一个三位数满足“数字本身等于百位、十位、个位各自的立方之和”，即 Armstrong Number（水仙花数）。

例如 `371 = 3³ + 7³ + 1³`。三位 Armstrong Numbers 为 `153、370、371、407`。

```c
#include "armstrong.h"

int is_armstrong_number(int number)
{
    int hundreds = number / 100;
    int tens = (number / 10) % 10;
    int ones = number % 10;

    int cube_sum =
        hundreds * hundreds * hundreds
        + tens * tens * tens
        + ones * ones * ones;

    return cube_sum == number;
}
```

**三个要点**：

1. `^` 在 C 里不是乘方，是按位异或。使用 `a*a*a` 求立方。
2. 返回非零代表真，`0` 代表假；比较表达式本身可以直接 `return`。
3. 老师要求只修改 `armstrong_checker.c` 中的函数体；不增加 `main()`、`scanf()`、`printf()`；不改 `armstrong.h` 或 `test_armstrong_checker.c`。

**本地测试**：`100→0`、`153→1`、`352→0`、`370→1`、`371→1`、`407→1`、`999→0`；7/7 PASS。此题无需单独提交 CodeGrade；实现会在 Exercise C 中复用。

## 6. Loops — 循环（§4）

### 6.1 while：条件控制的重复（CP06）

适合重复次数未知的情况，例如输入验证：

```c
printf("Enter a three-digit number: ");
scanf("%d", &number);

while (number < 100 || number > 999) {
    printf("Invalid input. Try again: ");
    scanf("%d", &number);
}
```

`while` 的执行过程：先检查条件 → 真则执行循环体 → 再检查；第一次条件为假则一次也不执行。要在循环体中更新相关变量，否则可能形成无限循环（Infinite Loop）。

### 6.2 for：初始化、条件、更新（CP07）

```c
for (initialisation; condition; update) {
    // 循环体
}
```

- `initialisation` 初始化，只执行一次。
- `condition` 每轮开始前检查。
- `update` 每轮循环体执行结束后运行。

官方示例：

```c
int k = 0;
int i;
for (i = 1; i <= 5; i++) {
    k = k + i;
}
printf("Sum: %d\n", k);
printf("Final i: %d\n", i);
```

| 本轮 `i` | 执行前 `k` | 执行后 `k` | 更新后 `i` |
|---:|---:|---:|---:|
| 1 | 0 | 1 | 2 |
| 2 | 1 | 3 | 3 |
| 3 | 3 | 6 | 4 |
| 4 | 6 | 10 | 5 |
| 5 | 10 | 15 | 6 |

最终输出：

```text
Sum: 15
Final i: 6
```

**为什么最终 `i = 6`？** 第五轮执行完后依然会做 `i++`，之后 `6 <= 5` 为假，循环才退出。

## 7. Exercise C — Armstrong Number Explorer

**任务**：读入三位整数作为上限，拒绝非法值，从 `100` 到 `upper_limit`（含上限）依次调用 Exercise B 的函数，输出符合条件的数字并统计数量。要求输出文字与顺序严格匹配 Sample Runs。

程序结构：

```c
#include <stdio.h>
#include "armstrong.h"

int main(void)
{
    printf("=== Armstrong Number Explorer ===\n");

    int upper_limit;
    int number;
    int count = 0;

    printf("Enter a three-digit upper limit: ");
    scanf("%d", &number);

    while (number < 100 || number > 999) {
        printf("Invalid input: enter a number from 100 to 999.\n");
        printf("Enter a three-digit upper limit: ");
        scanf("%d", &number);
    }
    upper_limit = number;

    printf("\nArmstrong numbers from 100 to %d:\n", upper_limit);

    for (number = 100; number <= upper_limit; number++) {
        if (is_armstrong_number(number)) {
            printf("%d\n", number);
            count++;
        }
    }

    if (count == 0) {
        printf("No Armstrong numbers were found.\n");
    }
    printf("Total found: %d\n", count);
    return 0;
}
```

**正确情景**：

- 输入 `99 → 1000 → 500`：前两个输入被拒绝；接受 `500`；输出 `153、370、371、407`，最终 `Total found: 4`。
- 输入 `150`：输出 `No Armstrong numbers were found.` 和 `Total found: 0`。
- `number <= upper_limit` 包含上限，不能随意写成 `<`。
- **复用函数**：不要将立方求和计算复制到 `armstrong_explorer.c`；在 `for` 内调用 `is_armstrong_number(number)`。
- **精确输出**：`upper limit` 之间必须是空格；写成 `upper_limit` 可能触发 Full Match 失败。

**结果**：CodeGrade AutoTest 12/12（Compilation 1/1、Correct Output 8/8、Code Structure 3/3）。

## 8. Linux / GCC 编译与测试

从 `base_code/lab1/` 目录执行，包含三个主要文件 `armstrong.h`、`armstrong_checker.c`、`armstrong_explorer.c`。

```bash
# Exercise A
gcc -Wall -Wextra -std=c11 digit_analyzer.c -o digit_analyzer
./digit_analyzer

# Exercise B — 本地测试
gcc -Wall -Wextra -std=c11 armstrong_checker.c test_armstrong_checker.c -o test_armstrong_checker
./test_armstrong_checker

# Exercise C
gcc -Wall -Wextra -std=c11 armstrong_checker.c armstrong_explorer.c -o armstrong_explorer
./armstrong_explorer
```

**常用参数**：`-Wall -Wextra` 开启常见编译警告；`-std=c11` 指定 C11；`-o` 指定输出可执行文件名。

**调试顺序**：保存源文件 → 编译 → 读警告 / 错误 → 运行 → 输入测试数据 → 比较预期输出。源文件修改后需重新编译；不要把生成的二进制文件提交 CodeGrade。

**不要直接 `gcc *.c`**：本实验文件夹中的多个 `.c` 文件拥有不同的 `main()`，一起链接会导致重复定义错误。仅编译对应 Exercise 指定的源文件。

## 9. 容易失分的 10 个细节

1. `=`（赋值）和 `==`（比较）不同。
2. `11 / 3` 是整数除法；平均数写 `11 / 3.0`。
3. `^` 是按位异或，不是乘方。
4. 取数位：`/ 10` 去掉个位、`% 10` 取个位。
5. 三位数有效范围为 `100–999`，无效条件用 `||`。
6. `switch` 记得 `case 'A':` 的单引号和必要的 `break;`。
7. `while` 循环体内必须更新其判断依赖的数据。
8. `for (i = 1; i <= 5; i++)` 结束时 `i` 为 `6`。
9. 函数声明不等于函数实现；跨文件链接要包含定义所在的 `.c`。
10. AutoTest 往往比较精确输出，包括空格、标点、换行和大小写。

## 10. 五题自测（先答再看答案）

1. `23 / 10` 与 `23 % 10` 各是多少？
2. `number=505` 时，百位、十位、个位分别为多少？其反转整数是多少？
3. `int x=0; int r=1 || ++x;` 的 `r`、`x` 是多少？
4. `for (i=1; i<=5; i++)` 执行完后 `i` 等于多少？
5. 为什么 Exercise C 要链接 `armstrong_checker.c`，而不能只编译 `armstrong_explorer.c`？

<details>
<summary>参考答案</summary>

1. `2` 和 `3`。
2. `5、0、5`；反转是 `505`。
3. `r=1`，`x=0`（逻辑 OR 短路）。
4. `6`。
5. 前者包含 `is_armstrong_number` 的实际定义；`armstrong.h` 只提供声明，链接时需要函数实现。

</details>

---

**Lab 1 总结**：本实验不只是写出一个水仙花数搜索器，更重要的是建立了完整的程序结构：**用变量保存数据 → 用算术运算处理数字 → 用分支做判断 → 用函数封装任务 → 用循环批量处理 → 用 GCC 与自动测试验证结果**。

*这份复习笔记为个人学习整理稿，示例根据 2026–2027 版讲义及本次实验源码归纳；额外澄清内容已注明。*
