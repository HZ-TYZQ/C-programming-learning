---
tags:
  - C
  - UESTC1005
  - IntroductoryProgramming
---

# C 语言基础整合笔记 — Lecture 1 & Lecture 2

> [!info]
> UESTC 1005 — Introductory Programming  
> 范围：Lecture 1 + Lecture 2  
> 额外包含：整数除法、类型转换、`scanf`、全局/局部变量等已学拓展内容

---

# 0. 整体学习主线

写程序时先不要急着敲代码。

基本思路：

```text
Input
  ↓
Problem / Algorithm
  ↓
Output
```

也就是：

1. 明确输入
2. 明确输出
3. 设计解决步骤
4. 再写代码
5. 编译、运行、测试
6. 修正错误

> [!important]
> First, solve the problem. Then, write the code.

---

# 1. 什么是程序

计算机程序本质上是：

```text
一系列按照特定顺序执行的指令
```

计算机最终只能理解机器语言。

语言层级可以粗略理解为：

```text
High-Level Language
        ↓
Assembly Language
        ↓
Machine Language
        ↓
Hardware
```

C 属于高级编程语言，需要通过编译器转换。

---

# 2. C 程序的基本结构

一个简单程序：

```c
#include <stdio.h>

int main(void)
{
    printf("Hello World\n");

    return 0;
}
```

可以拆成：

```text
#include <stdio.h>   -> 头部 / 预处理
main                 -> 程序入口
{ }                  -> 代码块
printf               -> 输出
;                    -> 语句结束
return 0             -> main 正常结束
```

---

# 3. Header 与 Body

C 程序可以大致分成：

```text
Header
+
Body
```

## Header

通常包括：

```c
#include <stdio.h>
```

以及其他预处理指令。

## Body

主要由函数组成：

```c
int main(void)
{
    ...
}
```

程序从：

```c
main
```

开始执行。

---

# 4. 预处理指令

预处理指令以：

```text
#
```

开头。

常见：

```c
#include
#define
#undef

#ifdef
#ifndef

#if
#else
#elif
#endif
```

它们会在正式编译之前由预处理器处理。

---

## `#include`

例如：

```c
#include <stdio.h>
```

用于包含头文件。

`stdio.h` 中提供标准输入输出相关功能，例如：

```c
printf
scanf
```

---

## 系统头文件

通常：

```c
#include <stdio.h>
```

---

## 自定义头文件

通常：

```c
#include "my_header.h"
```

---

## `#define`

例如：

```c
#define PI 3.14159
```

之后可以：

```c
double area = PI * 2 * 2;
```

现阶段可以理解成：

```text
给预处理器定义一个名字
```

---

# 5. 注释 Comments

注释不会作为普通程序语句执行。

## 单行注释

```c
// This is a comment
```

## 多行注释

```c
/*
This is
a comment.
*/
```

作用：

- 解释代码
- 增强可读性
- 方便自己以后阅读
- 方便别人理解程序

---

# 6. `main` 函数

基本结构：

```c
int main(void)
{
    return 0;
}
```

## `int`

表示：

```text
main 的返回类型是 int
```

## `{ }`

表示：

```text
code block
代码块
```

## `return 0`

通常表示：

```text
程序正常结束
```

---

# 7. Statement — 语句

C 中普通语句通常以：

```c
;
```

结束。

例如：

```c
int x = 10;
printf("%d\n", x);
return 0;
```

> [!warning]
> 分号位置非常重要。

例如：

```c
if (x > 0);
{
    printf("positive\n");
}
```

`if` 后面的 `;` 会改变原本的程序逻辑。

---

# 8. 编译过程

C 程序大致经历：

```text
Source Code
    ↓
Preprocessor
    ↓
Compiler
    ↓
Object File
    ↓
Linker
    ↓
Executable
    ↓
Run
    ↓
Output
```

也就是：

```text
源代码
↓
预处理
↓
编译
↓
目标文件
↓
链接
↓
可执行程序
```

---

# 9. GCC 基本使用

使用 Neovim 编辑：

```bash
nvim main.c
```

编译：

```bash
gcc main.c -o main
```

运行：

```bash
./main
```

学习阶段推荐：

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o main
```

其中：

```text
-std=c11     使用 C11 标准
-Wall        开启常见警告
-Wextra      开启额外警告
-pedantic    更严格检查标准 C
```

---

# 10. Variables — 变量

程序运行过程中需要保存数据。

例如：

```c
int age;
double voltage;
char grade;
```

变量可以理解成：

> 一个有名字的内存位置。

大致：

```text
变量名
  ↓
内存中的某个位置
  ↓
保存数据
```

---

# 11. 内存地址

计算机内存被划分成许多区域。

每一个位置都有对应的：

```text
memory address
内存地址
```

例如可以想象：

```text
Address     Data

0000        ...
0001        ...
0002        ...
0003        ...
```

变量让我们不用直接记忆地址。

例如：

```c
int age = 20;
```

我们可以使用：

```text
age
```

访问对应的数据。

以后学习指针时，会真正开始操作：

```text
内存地址
```

---

# 12. 变量声明、赋值、初始化

## 声明 Declaration

```c
int x;
```

表示创建一个：

```text
int 类型变量 x
```

---

## 赋值 Assignment

```c
x = 5;
```

表示：

```text
把 5 存进 x
```

---

## 初始化 Initialization

```c
int x = 5;
```

表示：

```text
声明变量的同时给初值
```

---

# 13. Identifier — 标识符

变量名属于标识符。

基本规则：

- 可以包含字母
- 可以包含数字
- 可以包含 `_`
- 不能以数字开头
- 区分大小写
- 最好使用有意义的名字

例如：

```text
variable      ✅
Variable      ✅
rivers4_      ✅

4rivers       ❌
v@riable      ❌
```

---

## 大小写敏感

```c
int number;
int Number;
```

这是两个不同变量。

---

# 14. 基本数据类型

目前重点：

```c
char
int
float
double
```

---

## `int`

保存整数：

```c
int age = 20;
```

---

## `float`

保存单精度浮点数：

```c
float voltage = 3.3f;
```

---

## `double`

保存更高精度浮点数：

```c
double pi = 3.141592653589793;
```

---

## `char`

保存字符：

```c
char grade = 'A';
```

> [!important]
> 单个字符使用单引号：

```c
'A'
```

而：

```c
"A"
```

是字符串，不是单个 `char`。

---

# 15. 数据类型与数值

## `int` 会丢掉小数部分

例如：

```c
int x = 10.93;
```

结果相当于：

```text
10
```

不是四舍五入。

---

例如：

```c
int x = -2.75;
```

结果：

```text
-2
```

即小数部分被截掉。

---

# 16. `float` 与 `double`

两者都可以表示实数。

区别主要在：

```text
精度
```

通常：

```text
float
精度较低

double
精度较高
```

---

# 17. `printf` 输出

需要：

```c
#include <stdio.h>
```

例如：

```c
printf("Hello\n");
```

---

## `\n`

表示：

```text
newline
换行
```

例如：

```c
printf("A\n");
printf("B\n");
```

输出：

```text
A
B
```

而：

```c
printf("A");
printf("B");
```

输出：

```text
AB
```

> [!important]
> `printf` 不会自动换行。

---

# 18. 输出变量

## `int`

```c
int age = 20;

printf("%d\n", age);
```

---

## `char`

```c
char grade = 'A';

printf("%c\n", grade);
```

---

## 浮点数

```c
double voltage = 3.3;

printf("%f\n", voltage);
```

输出类似：

```text
3.300000
```

---

## 控制小数位

```c
printf("%.2f\n", voltage);
```

输出：

```text
3.30
```

其中：

```text
.2
```

表示保留两位小数。

---

# 19. `scanf` 输入【已提前学习】

> [!note]
> `scanf` 的详细内容属于后续输入输出部分，但目前已经提前使用。

例如：

```c
int age;

scanf("%d", &age);
```

---

## 为什么有 `&`

```c
&age
```

表示：

```text
age 的内存地址
```

`scanf` 需要知道：

```text
应该把输入写到哪里
```

所以需要把变量地址交给它。

以后指针章节会详细解释。

---

## 常见格式

```c
int x;
float y;
double z;
char c;

scanf("%d", &x);
scanf("%f", &y);
scanf("%lf", &z);
scanf("%c", &c);
```

> [!important]
> 读取 `double` 时：

```c
scanf("%lf", &z);
```

而使用 `printf` 打印浮点值时通常写：

```c
printf("%f", z);
```

---

# 20. 运算符 Operators

目前主要分类：

```text
算术运算
赋值运算
关系运算
逻辑运算
自增 / 自减
```

---

# 21. 算术运算符

```c
+
-
*
/
%
```

对应：

```text
+   加
-   减
*   乘
/   除
%   取余
```

---

# 22. 整数除法【重要】

如果 `/` 两边都是整数：

```c
7 / 2
```

结果：

```text
3
```

而不是：

```text
3.5
```

因为：

```text
int / int
```

执行整数除法。

---

例如：

```c
double x = 7 / 2;
```

最终：

```text
x = 3.0
```

过程：

```text
7 / 2
↓
3
↓
转成 double
↓
3.0
```

> [!warning]
> 左边变量是 `double`，并不会改变右边已经完成的整数除法。

---

# 23. 浮点除法

只要让参与运算的数据成为浮点类型，例如：

```c
7.0 / 2
```

结果：

```text
3.5
```

也可以：

```c
(double)7 / 2
```

---

# 24. Cast — 类型转换【已提前学习】

显式类型转换：

```c
(double)x
```

例如：

```c
int a = 7;
int b = 2;

double result = (double)a / b;
```

得到：

```text
3.5
```

---

注意：

```c
(double)(a / b)
```

和：

```c
(double)a / b
```

不同。

如果：

```text
a = 7
b = 2
```

那么：

```c
(double)(a / b)
```

先算：

```text
7 / 2 = 3
```

再转换：

```text
3.0
```

而：

```c
(double)a / b
```

先转换：

```text
7.0 / 2
```

得到：

```text
3.5
```

---

# 25. `%` — 取余【已提前学习】

例如：

```c
7 % 3
```

结果：

```text
1
```

因为：

```text
7 = 3 * 2 + 1
```

---

常见用途：

## 判断偶数

```c
x % 2 == 0
```

## 判断奇数

```c
x % 2 != 0
```

## 判断能否整除

```c
x % n == 0
```

---

# 26. 赋值运算符 `=`

```c
x = 10;
```

意思：

```text
把 10 赋值给 x
```

---

# 27. `=` 与 `==`

这是非常重要的区别。

## Assignment

```c
x = 10;
```

表示：

```text
赋值
```

## Comparison

```c
x == 10
```

表示：

```text
判断 x 是否等于 10
```

> [!warning]
> 单个 `=` 和两个 `==` 完全不是一回事。

---

# 28. 关系运算符

```c
==
!=
>
<
>=
<=
```

例如：

```c
x == 10
x != 10

x > 10
x < 10

x >= 10
x <= 10
```

---

# 29. C 中的真假

在条件判断中：

```text
0       -> false
非 0    -> true
```

例如：

```c
printf("%d\n", 5 > 3);
```

结果：

```text
1
```

而：

```c
printf("%d\n", 5 < 3);
```

结果：

```text
0
```

---

# 30. Logical AND — `&&`

表示：

```text
并且
```

例如：

```c
x > 0 && x < 10
```

只有两边都成立，结果才为真。

| A | B | A && B |
|---:|---:|---:|
| 0 | 0 | 0 |
| 非 0 | 0 | 0 |
| 0 | 非 0 | 0 |
| 非 0 | 非 0 | 1 |

---

# 31. Logical OR — `||`

表示：

```text
或者
```

例如：

```c
x < 0 || x > 100
```

只需要一个条件成立。

| A | B | A \|\| B |
|---:|---:|---:|
| 0 | 0 | 0 |
| 非 0 | 0 | 1 |
| 0 | 非 0 | 1 |
| 非 0 | 非 0 | 1 |

---

# 32. Logical NOT — `!`

表示：

```text
逻辑取反
```

例如：

```c
!0
```

得到：

```text
1
```

而：

```c
!5
```

得到：

```text
0
```

---

# 33. 数学表达式与 C 条件

数学中可以写：

```text
3.0 <= voltage <= 3.6
```

但是 C 中不要直接照抄。

应该写：

```c
voltage >= 3.0 && voltage <= 3.6
```

也就是拆成：

```text
voltage >= 3.0
```

以及：

```text
voltage <= 3.6
```

再用：

```c
&&
```

连接。

---

# 34. 运算优先级【实用补充】

现阶段先记：

```text
()
↓
* / %
↓
+ -
↓
< <= > >=
↓
== !=
↓
&&
↓
||
↓
=
```

例如：

```c
2 + 3 * 4
```

结果：

```text
14
```

因为先算：

```text
3 * 4
```

如果：

```c
(2 + 3) * 4
```

结果：

```text
20
```

> [!tip]
> 表达式开始复杂时，主动加括号。

---

# 35. Algorithm — 算法

算法可以理解为：

> 为了解决一个问题而按照特定顺序执行的一系列步骤。

例如：

```text
输入两个数
↓
计算
↓
输出结果
```

---

# 36. Flowchart — 流程图

常见符号：

| 图形 | 含义 |
|---|---|
| 椭圆 | Start / End |
| 矩形 | Action |
| 菱形 | Decision |
| 箭头 | Flow |

例如：

```text
      Start
        ↓
      Input
        ↓
     Decision
     /      \
   Yes      No
    ↓        ↓
 Action   Action
     \      /
        ↓
       End
```

程序中的条件判断就是在实现这种：

```text
Decision
```

---

# 37. 拓展：全局变量与局部变量

> [!note]
> 以下内容是我们根据实战代码提前拓展的知识，不属于 Lecture 1–2 的主要讲授内容。

---

## 37.1 Global Variable — 全局变量

写在函数外面的变量：

```c
#include <stdio.h>

int x = 10;

int main(void)
{
    printf("%d\n", x);

    return 0;
}
```

这里：

```c
int x = 10;
```

就是全局变量。

可以粗略理解：

```text
整个文件
│
├── global x
│
├── function A
├── function B
└── main
```

后面的函数在作用域允许的情况下可以访问它。

---

# 38. Local Variable — 局部变量

写在函数或代码块内部：

```c
int main(void)
{
    int x = 10;

    return 0;
}
```

这里：

```c
x
```

属于局部变量。

它主要存在于：

```text
main 的代码块
```

中。

---

# 39. Scope — 作用域

作用域表示：

> 某一个变量名在代码中的哪些位置可以被访问。

例如：

```c
int global_x = 10;

int main(void)
{
    int local_x = 20;
}
```

粗略理解：

```text
global_x
↓
较大的可见范围

local_x
↓
主要只在 main 内可见
```

---

# 40. Shadowing — 遮蔽

例如：

```c
#include <stdio.h>

int x = 10;

int main(void)
{
    int x = 20;

    printf("%d\n", x);

    return 0;
}
```

输出：

```text
20
```

原因：

```c
int x = 20;
```

创建了一个新的局部变量。

这个局部 `x` 把外面的全局 `x` 遮蔽了。

大致：

```text
Global:
x = 10

main:
┌──────────────┐
│ x = 20       │
│              │
│ 当前使用 x   │
│ 得到 20      │
└──────────────┘
```

---

# 41. 声明新变量 vs 修改全局变量

## 情况一

```c
int x = 10;

void test(void)
{
    int x = 30;
}
```

这里：

```c
int x = 30;
```

创建的是：

```text
新的局部变量
```

全局：

```text
x = 10
```

没有被修改。

---

## 情况二

```c
int x = 10;

void test(void)
{
    x = 30;
}
```

这里没有重新声明 `x`。

所以使用的是外面的全局变量。

执行后：

```text
global x = 30
```

---

# 42. 函数参数也是局部变量

例如：

```c
int square(int x)
{
    return x * x;
}
```

这里参数：

```c
x
```

属于这个函数自己的局部变量。

例如：

```c
int a = 5;

square(a);
```

可以先粗略理解成：

```text
main:
a = 5

     ↓ 传入

square:
x = 5
```

`a` 和 `x` 不是同一个变量。

只是值被传了过去。

---

# 43. 全局变量为什么不要滥用

例如：

```c
int score = 100;

void a(void)
{
    score = 50;
}

void b(void)
{
    score = 0;
}
```

很多函数都能修改同一个全局变量时：

```text
程序越大
↓
越难知道是谁修改了数据
↓
越难调试
```

所以现阶段建议：

> [!important]
> 能使用局部变量解决时，优先使用局部变量。

---

# 44. 全局变量 vs 局部变量

| | 全局变量 | 局部变量 |
|---|---|---|
| 声明位置 | 函数外 | 函数 / 代码块内 |
| 作用域 | 通常较大 | 通常较小 |
| 是否容易被多个函数修改 | 是 | 相对不容易 |
| 调试难度 | 容易变复杂 | 更容易控制 |
| 使用原则 | 有明确理由再用 | 默认优先 |

---

# 45. 拓展：变量生命周期

> [!note]
> 这里只建立直觉，后面学函数、`static`、指针时再详细讨论。

普通全局变量通常：

```text
程序开始
↓
变量存在
↓
程序运行
↓
程序结束
```

普通局部变量通常：

```text
进入代码块 / 函数
↓
变量存在
↓
使用
↓
离开代码块 / 函数
↓
生命周期结束
```

---

# 46. 当前推荐代码风格

尽量：

```c
int main(void)
{
    int device_id;
    double voltage;
    double current;

    ...
}
```

而不是没有必要地：

```c
int device_id;
double voltage;
double current;

int main(void)
{
    ...
}
```

原则：

```text
变量放在真正需要它的最小合理作用域中
```

---

# 47. 当前常用程序模板

```c
#include <stdio.h>

int main(void)
{
    int x;
    double y;

    scanf("%d %lf", &x, &y);

    // calculation

    printf("%d %.2f\n", x, y);

    return 0;
}
```

---

# 48. 当前易错点总结

> [!warning] 高频错误

## 1. 忘记分号

```c
int x = 10
```

错误。

应该：

```c
int x = 10;
```

---

## 2. `=` 与 `==` 混淆

```c
x = 5;
```

赋值。

```c
x == 5
```

比较。

---

## 3. 忘记 `scanf` 的 `&`

错误：

```c
scanf("%d", x);
```

正确：

```c
scanf("%d", &x);
```

---

## 4. `double` 输入格式错误

```c
scanf("%lf", &x);
```

---

## 5. 整数除法丢失小数

```c
double x = 7 / 2;
```

结果：

```text
3.0
```

想得到：

```text
3.5
```

可以：

```c
double x = (double)7 / 2;
```

---

## 6. 数学区间直接照搬到 C

不要：

```c
3.0 <= x <= 3.6
```

应该：

```c
x >= 3.0 && x <= 3.6
```

---

## 7. 局部变量遮蔽全局变量

```c
int x = 10;

void test(void)
{
    int x = 20;
}
```

这里两个 `x` 不是同一个变量。

---

## 8. 没必要时使用全局变量

优先：

```c
int main(void)
{
    int x;
}
```

而不是：

```c
int x;

int main(void)
{
}
```

---

# 49. 当前知识关系图

```text
C Program
│
├── Header
│   ├── #include
│   └── #define
│
├── Body
│   └── main()
│
├── Variables
│   ├── int
│   ├── float
│   ├── double
│   └── char
│
├── Input / Output
│   ├── scanf
│   └── printf
│
├── Operators
│   ├── + - * / %
│   ├── =
│   ├── == != < > <= >=
│   └── && || !
│
├── Type Conversion
│   └── (double)x
│
├── Decision Concept
│   ├── true / false
│   ├── relation
│   └── logic
│
└── Variable Scope [拓展]
    ├── global
    ├── local
    ├── scope
    └── shadowing
```

---

# 50. 超短速记

```text
程序入口：
main
```

```text
标准输入输出：
#include <stdio.h>
```

```text
输出：
printf
```

```text
输入：
scanf
```

```text
变量：
int
float
double
char
```

```text
赋值：
=
```

```text
比较：
== != > < >= <=
```

```text
逻辑：
&& || !
```

```text
真假：
0 = false
非 0 = true
```

```text
整数除法：
7 / 2 = 3
```

```text
浮点除法：
(double)7 / 2 = 3.5
```

```text
取余：
7 % 2 = 1
```

```text
作用域：
global = 函数外
local  = 函数 / 代码块内
```

```text
shadowing：
局部同名变量会遮蔽外层同名变量
```

---

# 51. 自检 Checklist

## Lecture 1

- [ ] 我知道程序从 `main` 开始
- [ ] 我知道 `#include <stdio.h>` 的基本作用
- [ ] 我知道什么是预处理
- [ ] 我知道基本编译流程
- [ ] 我会使用 GCC 编译和运行程序
- [ ] 我知道 `printf` 和 `\n`

## Lecture 2

- [ ] 我知道变量和内存之间的基本关系
- [ ] 我知道变量命名规则
- [ ] 我能区分 `int`、`float`、`double`、`char`
- [ ] 我能区分声明、初始化和赋值
- [ ] 我能区分 `=` 和 `==`
- [ ] 我会使用关系运算符
- [ ] 我会使用 `&&`、`||`、`!`
- [ ] 我知道 `0` 为假，非 `0` 为真
- [ ] 我理解算法和流程图的基本概念

## 已学拓展

- [ ] 我会使用 `scanf`
- [ ] 我知道 `scanf` 为什么需要 `&`
- [ ] 我理解整数除法
- [ ] 我会使用 `%`
- [ ] 我会使用 `(double)` 进行显式类型转换
- [ ] 我知道全局变量与局部变量的区别
- [ ] 我理解 scope
- [ ] 我理解 shadowing
- [ ] 我知道一般应优先使用局部变量
