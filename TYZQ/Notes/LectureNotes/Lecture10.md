---
title: "Lecture 10 — Structures and Bit Manipulation"
aliases:
  - "Lecture 10"
  - "L10 结构体与位操作"
course: UESTC1005
lecture: 10
date: 2026-11-09
status: 已完成理论学习，实验待核对
tags:
  - C语言
  - UESTC1005
  - Lecture10
  - 结构体
  - 指针
  - 位运算
---

# Lecture 10 — Structures and Bit Manipulation

> [!info] 课程定位与资料来源
> - 课程：UESTC1005 · Introductory Programming
> - 依据：项目资料《UESTC1005 - C语言课件合集.md》中 Lecture 10「结构体与位操作」，结合本次学习讨论、推导题与示例整理。
> - **课件主线**：传值与通过指针修改变量 → 多输出函数与结构体 → 结构体传参 → `const` → 位运算 → XOR 的应用 → 位移 → 位掩码与标志位。
> - **标注约定**：「课件」为原课件主要知识；「课堂拓展」为本次学习增加的例题、解释或 C11 兼容性提醒。个别课件写法有容易误解之处，已单独标注，不把补充说明伪装成课件原文。
> - 本文为 AI 辅助整理的学习笔记，代码示例应自行理解、编译与验证。

## 0. 本讲知识地图

- [[#1. Pass by Value 与通过指针修改调用者变量]]
- [[#2. 多输出函数：输出参数 vs. 返回结构体]]
- [[#3. 为什么要用指针传递结构体？]]
- [[#4. `const` 类型限定符]]
- [[#5. 位运算符：AND、OR、XOR、NOT]]
- [[#6. XOR 的两类经典应用]]
- [[#7. 位移运算 `<<` 与 `>>`]]
- [[#8. Bit Fields / Flags 与位掩码]]
- [[#9. 本次学习中真正弄懂的易错点]]
- [[#10. 考前速查表]]
- [[#11. 自测题与答案]]

---

## 1. Pass by Value 与通过指针修改调用者变量

### 1.1 C 函数参数始终按值传递

```c
// 传入的是数值的副本
void change_value(int x) {
    x = 100;
}

// 传入的是地址的副本，但可通过这个地址修改原变量
void change_through_pointer(int *p) {
    *p = 100;
}
```

```c
int a = 10;
change_value(a);             // a 还是 10
change_through_pointer(&a);  // a 变成 100
```

- `change_value(a)`：`x` 与 `a` 是两个独立的 `int` 对象。
- `change_through_pointer(&a)`：指针 `p` 本身也是副本，**但它保存着 `a` 的地址**；因此 `*p` 操作的就是 `a`。
- 课件使用 *Pass by Reference* 指通过指针实现的“类似引用传递”的效果；严格来说，**C 没有 C++ 那种引用参数，函数传参机制仍然是 pass by value**。

> [!tip] 一句话记忆
> **复制地址 ≠ 复制地址指向的数据。**

### 1.2 课件例子：除以 2

```c
// 不改变调用者的实参
double div2_pass_by_value(double x) {
    return x / 2;
}

// 改变指针指向的对象
double div2_pass_by_reference(double *x_ptr) {
    double x = *x_ptr;
    *x_ptr = x / 2;
    return *x_ptr;
}
```

```c
double a = 20;
double b = div2_pass_by_value(a); // a = 20, b = 10
a = div2_pass_by_reference(&b);  // b = 5, a = 5
```

**区别是修改了哪块内存，不是函数名里有没有 `reference`。**

---

## 2. 多输出函数：输出参数 vs. 返回结构体

### 2.1 问题：如何同时得到最小值和最大值？

C 函数可以有很多输入参数，但一次 `return` 只能直接返回一个值。因此课件给出两种思路：

1. **Output Parameters**：用两个指针参数分别写入 `min`、`max`。
2. **Return a Structure**：把 `min`、`max` 放入一个结构体，返回这个结构体值。

### 2.2 方法一：通过输出参数写回多个值

```c
#include <assert.h>
#include <limits.h>

void min_max_call_by_ref(
    int *min,
    int *max,
    const int *a,
    unsigned length
) {
    assert(length > 0);

    *min = INT_MAX;
    *max = INT_MIN;

    for (unsigned i = 0; i < length; ++i) {
        if (a[i] < *min) *min = a[i];
        if (a[i] > *max) *max = a[i];
    }
}
```

> [!note] 对照课件
> 原课件的数组参数写为 `int *a`；上例采用课件后续改进的 `const int *a`，说明函数只读取数组、不负责修改数组。

```c
int arr[] = {8, 3, 12, 5, 9};
int minimum, maximum;

min_max_call_by_ref(&minimum, &maximum, arr, 5);
// minimum == 3, maximum == 12
```

| 参数 | 作用 | 方向 |
| --- | --- | --- |
| `int *min` | 写入最小值 | 输出 |
| `int *max` | 写入最大值 | 输出 |
| `const int *a` | 读取数组 | 输入 |
| `unsigned length` | 数组元素数量 | 输入 |

初始化 `*min = INT_MAX` 和 `*max = INT_MIN`，确保首个有效元素能分别进入最小值、最大值比较。

> [!warning] 边界条件
> 这里要求 `length > 0`，否则“最小值／最大值”没有定义；`assert` 适合教学与调试，正式接口仍应考虑空数组、空指针和错误返回方式。

### 2.3 方法二：返回结构体

```c
#include <assert.h>
#include <limits.h>

struct MinMax {
    int min;
    int max;
};

struct MinMax min_max_by_struct(const int *a, unsigned length) {
    assert(length > 0);

    struct MinMax result = {INT_MAX, INT_MIN};
    for (unsigned i = 0; i < length; ++i) {
        if (a[i] < result.min) result.min = a[i];
        if (a[i] > result.max) result.max = a[i];
    }
    return result;
}
```

```c
int arr[] = {8, 3, 12, 5, 9};
struct MinMax result = min_max_by_struct(arr, 5);
// result.min == 3
// result.max == 12
```

注意：`return result;` **仍然只返回一个值**，只不过这个值是包含两个成员的结构体。

| 对比 | 输出参数 | 返回结构体 |
| --- | --- | --- |
| 函数返回类型 | 可用 `void` | `struct MinMax` |
| 结果写到哪里 | 调用者的变量 | 返回的结构体值 |
| 调用方式 | `min_max(&min, &max, ...)` | `struct MinMax r = min_max(...)` |
| 适用场景 | 修改已有变量／需要多种输出 | 将多个结果自然组织成一组数据 |

---

## 3. 为什么要用指针传递结构体？

### 3.1 结构体按值传递 = 复制成员值

```c
struct Point {
    int x;
    int y;
};

struct Point move(struct Point p) {
    p.x += 10;
    p.y += 20;
    return p;
}

struct Point a = {1, 2};
struct Point b = move(a);
// a = {1, 2}
// b = {11, 22}
```

`p` 是 `a` 的副本，修改 `p` 不会直接修改 `a`。

**课件强调的成本**：复制大型结构体可能增加数据拷贝与临时存储开销。因此对大型、只需读取的结构体，经常传递指针。

```c
void printStudent(const struct Student *student);
```

> [!important] 不要理解成“所有结构体都必须传指针”
> 小结构体按值传递很正常，返回结构体也很常见。关键取决于是否需要修改原对象、复制成本、接口清晰性与对象生命周期。

### 3.2 课堂拓展：结构体含指针成员时的浅拷贝（Shallow Copy）

```c
struct Data {
    int *ptr;
};

void modify(struct Data d) {
    *d.ptr = 100;
}

int x = 10;
struct Data a = {&x};
modify(a);
// x == 100
```

按值复制 `a` 到 `d` 时，只复制了 `ptr` 里存储的**地址值**，没有自动复制 `x` 这个对象。

```text
a.ptr ──┐
        ├──> x
 d.ptr ─┘
```

因此，通过 `*d.ptr` 仍可修改外部的 `x`。

但是：

```c
void change(struct Data d) {
    int y = 50;
    d.ptr = &y;   // 仅修改副本 d 的指针成员
    *d.ptr = 200; // 修改局部变量 y，而非外部 x
}
```

`a.ptr` 仍指向原来的 `x`；`d.ptr` 改指向 `y`，只在该函数调用期间使用。**不要把局部变量 `y` 的地址返回或存入调用者仍会使用的指针中**：函数结束后 `y` 的生命周期就结束了。

> [!tip] 区分这两个动作
> - `d.ptr = &y;`：改变指针成员保存的地址。
> - `*d.ptr = 200;`：改变当前指针指向的对象。

---

## 4. `const` 类型限定符

### 4.1 普通变量上的 `const`

```c
int x = 10;
const int y = x;

x = 20; // 合法
y = 20; // 编译约束错误：y 不可赋值
```

`const` 是类型限定符，禁止通过该左值修改对象；它不等于“内存物理上绝不可能变化”。

### 4.2 三种常见指针声明

```c
int a = 10;
int b = 20;

const int *p1 = &a;       // 不能通过 p1 改 *p1，但 p1 可重新指向 b
int *const p2 = &a;       // p2 不能改指向，但可以通过 p2 修改 a
const int *const p3 = &a; // 两种限制都有
```

| 声明 | 能通过指针修改数据？ | 能重新给指针赋地址？ |
| --- | --- | --- |
| `const int *p` | ❌ | ✅ |
| `int *const p = &a` | ✅ | ❌ |
| `const int *const p = &a` | ❌ | ❌ |

```c
const int *p = &a;
// *p = 30;   // 不合法
a = 30;       // 合法：a 本身不是 const
p = &b;       // 合法：p 本身不是 const 指针

int *const q = &a;
*q = 40;      // 合法：修改 a
// q = &b;    // 不合法：q 本身不可重新赋值
```

> [!warning] 本节最容易误解的地方
> `const int *p` 并不会把原本普通的 `int a` 永久变成常量；它禁止的是**通过 `p` 这条访问路径**进行写入。若对象本身定义为 `const int`，则不能通过强制转换后写入来绕开限制，否则行为未定义。

### 4.3 为什么常见 `const struct Student *student`？

```c
void displayStudent(const struct Student *student) {
    // 可以读取 student->id、student->name 等成员
    // 不能通过 student 修改它指向的 Student 成员
}
```

它兼顾：

- **效率**：不因函数传参而复制整个大结构体。
- **接口约束**：不允许该函数通过参数指针写入结构体成员。

注意：如果结构体成员中还有指针，`const struct Student *` 不会自动对这些指针指向的其他对象提供递归只读保护。

---

## 5. 位运算符：AND、OR、XOR、NOT

### 5.1 运算规则

| `a` | `b` | `a & b` | `a \| b` | `a ^ b` | `~a`（仅此位） |
| ---: | ---: | ---: | ---: | ---: | ---: |
| 0 | 0 | 0 | 0 | 0 | 1 |
| 0 | 1 | 0 | 1 | 1 | 1 |
| 1 | 0 | 0 | 1 | 1 | 0 |
| 1 | 1 | 1 | 1 | 0 | 0 |

- `&`（AND）：两边都是 `1` 才是 `1`。
- `|`（OR）：至少一个 `1` 就是 `1`。
- `^`（XOR）：不同为 `1`，相同为 `0`。
- `~`（NOT）：逐位取反；真实结果还与整数类型和位宽有关。

### 5.2 课件例子：42 XOR 56

```text
42 = 101010
56 = 111000
     ------
^  = 010010 = 18
```

```c
int x = 42;
int y = 56;
int z = x ^ y; // 18
```

### 5.3 别把位运算符和逻辑运算符混淆

```c
int a = 6;  // 0110
int b = 3;  // 0011

a && b;    // 1：两个值都非零
a & b;     // 2：0110 & 0011 = 0010
```

| 逻辑运算 | 按位运算 |
| --- | --- |
| `&&`、`||`、`!` | `&`、`|`、`^`、`~` |
| 处理整个表达式的真假 | 对每一位独立处理 |
| `&&`、`||` 有短路求值 | `&`、`|` 不因左边真假而短路 |

> [!tip] 一眼判断奇偶
> `x & 1` 只检查最低位：对非负整数，结果为 `1` 是奇数，结果为 `0` 是偶数。在现代常见的二进制补码机器上，负数也符合这一规律；若严格讨论旧版 C 标准允许的不同有符号整数表示，则不要无条件推广。

---

## 6. XOR 的两类经典应用

### 6.1 XOR 性质

$$
A\oplus A=0,\qquad A\oplus 0=A
$$

$$
A\oplus B=B\oplus A
$$

$$
(A\oplus B)\oplus C=A\oplus(B\oplus C)
$$

因此：

$$
(A\oplus B)\oplus B=A
$$

这正是 XOR 的**可逆性**。

### 6.2 数据恢复：奇偶校验（课件 RAID 案例）

```text
X1 = 00001111
X2 = 10101010
X3 = 11010011
P  = 01110110   // X1 ^ X2 ^ X3
```

一旦 `X2` 丢失：

$$
\begin{aligned}
P\oplus X1\oplus X3
&=(X1\oplus X2\oplus X3)\oplus X1\oplus X3\\
&=X2.
\end{aligned}
$$

**课堂练习**：

```text
X1 = 1010
X2 = ????
X3 = 0011
P  = 1100

P ^ X1     = 0110
0110 ^ X3  = 0101
因此 X2    = 0101（5）
```

> [!note] 课件模型与真实 RAID
> 课件用单独的 `P` 盘解释奇偶校验原理；实际 RAID 5 将校验分布在多块盘中。该思路能恢复**一份**缺失数据，不能据此推断任意多盘同时故障都可恢复。

### 6.3 XOR Swap：用三次 XOR 交换两个值

```c
int a = 5, b = 9;
a = a ^ b;
b = a ^ b;
a = a ^ b;
// a == 9, b == 5
```

设原始值 `a = A`、`b = B`，则：

1. `a = A ^ B`
2. `b = (A ^ B) ^ B = A`
3. `a = (A ^ B) ^ A = B`

> [!warning] 课堂拓展：不建议在真实项目中炫技使用 XOR Swap
> 两个指针若指向同一个对象，直接三次 XOR 会把该对象变为 0；课件给出的指针版本用 `if (x == y) return;` 防护。实际工程推荐简单清晰的临时变量交换：
>
> ```c
> int temp = a;
> a = b;
> b = temp;
> ```

---

## 7. 位移运算 `<<` 与 `>>`

### 7.1 左移（Left Shift）

```text
00000011 = 3
00000110 = 3 << 1 = 6
00001100 = 3 << 2 = 12
00011000 = 3 << 3 = 24
```

非负整数且结果能够表示时：

$$
x\ll N=x\times2^N
$$

左移 N 位，空出来的低位补 `0`。

> [!note] 课件原文的记法提醒
> 旧版幻灯片中把 `x << N` 的乘法类比写成 `x * (2 * N)`；正确的数量关系应是 **`x * 2^N`**，不是 `x * 2N`。

### 7.2 右移（Right Shift）

```text
00011000 = 24
00001100 = 24 >> 1 = 12
00000110 = 24 >> 2 = 6
```

对于非负整数：

$$
x\gg N=\left\lfloor\frac{x}{2^N}\right\rfloor
$$

右移会丢弃被移出的低位，因此可能丢失信息：

```text
19        = 00010011
19 >> 2   = 00000100 = 4
4 << 2    = 00010000 = 16   // 无法还原 19
```

### 7.3 为什么不能无条件认为“左移再右移能还原”？

课堂中用 **8-bit 模型**观察：

```text
11000001  (193)
<< 2
00000100  (低 8 位；高位丢失)
>> 2
00000001  (1，不是 193)
```

> [!warning] C11 中的位移边界
> - 位移量不能为负，也不能大于等于左操作数经整数提升后的位宽，否则行为未定义。
> - 对**非负有符号整数**左移，若数学结果不能用结果类型表示，则行为未定义。
> - 对**无符号整数**左移按其类型位宽做模 $2^w$ 运算，可能丢失高位。
> - 对**负有符号整数**右移，在 C11 中结果是实现定义的；初学阶段避免依赖它。
> - 课件举例采用 `0b...`，但该二进制字面量在 **C23** 才成为标准语法；如果使用 `-std=c11`，可写十进制、十六进制或自行按位计算。

### 7.4 课堂题：`(x >> 1) << 1`

```c
unsigned int x = 13;
unsigned int y = (x >> 1) << 1;
// y == 12
```

先去掉最低位，再补一个 `0`，效果是把整数向下调整到最近的偶数：

| x | 结果 |
| ---: | ---: |
| 13 | 12 |
| 12 | 12 |
| 7 | 6 |
| 8 | 8 |

---

## 8. Bit Fields / Flags 与位掩码

### 8.1 课件例子：用一个字节保存 NES 手柄状态

课件将 8 个按钮状态打包为 8 个 bit：

| bit index（从右往左） | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 按钮 | Up | Down | Left | Right | Start | Select | A | B |

```c
unsigned char controller_state = 0x82;
// 10000010：Up = 1，A = 1，其余为 0
```

`0x82` 是十六进制（130），其低 8 位为 `10000010`。

### 8.2 Mask：只选中关注的 bit

```c
unsigned int A_mask = 1u << 1;     // 00000010
unsigned int Start_mask = 1u << 3; // 00001000
unsigned int Left_mask = 1u << 5;  // 00100000
```

#### ① 检查某位是否为 1：AND

```c
if (controller_state & A_mask) {
    // A 被按下
}
```

```text
10000010 & 00000010 = 00000010  -> 非零，A 按下
10000010 & 00001000 = 00000000  -> 为零，Start 未按下
```

#### ② 将某位设置成 1：OR

```c
controller_state |= Left_mask;
// 10000010 | 00100000 = 10100010
```

掩码为 `1` 的位一定变为 `1`，其余位保留。

#### ③ 将某位清除为 0：AND + NOT（课堂拓展）

```c
controller_state &= ~Left_mask;
// 10100010 & 11011111 = 10000010 （只展示低 8 位）
```

掩码取反后，目标位为 `0`、其他位为 `1`；再用 AND 便能只清除目标位。

> [!note] 类型提醒
> `~Left_mask` 作用的是整数提升后的整数位宽，不应把 `11011111` 误认为完整机器整数；它只是上例关注的低 8 位。对于当前 `unsigned char` 状态操作，结果符合预期。

#### ④ 翻转某位：XOR（课堂拓展）

```c
controller_state ^= Left_mask;
// 10000010 ^ 00100000 = 10100010
// 再执行一次得到 10000010
```

**容易犯的错误**：`state ^ 1u ^ Left_mask` 会额外翻转 **bit 0**。`1u` 不是“翻转所有位”，而是只有最低位为 1 的掩码。

### 8.3 合并标志位：OR

```c
unsigned char state1 = 0xA0; // 10100000
unsigned char state2 = 0x06; // 00000110
unsigned char merged = state1 | state2;
// merged = 10100110（二进制）= 166（十进制）
```

为何不能把 OR 随便换成 XOR？当两组状态同一个 bit 都是 `1` 时：

```text
1 | 1 = 1   // 两个按钮状态有一个或两个按下 -> 仍算按下
1 ^ 1 = 0   // 同时按下反而被抵消
```

因此“任意一个来源为真，就合并为真”应该选择 OR。

### 8.4 C 语言中另一种严格意义的 Bit-field 语法（课堂拓展）

> [!info] 和课件术语的区别
> 本讲幻灯片主要把“用一个整数装多个 flags”称为 *Bit Fields*，重点在**位掩码**。而 C 语言还有专门的**结构体位域语法**，形式是 `成员名 : 位数`。这是额外的语法知识，不要与前面的手动掩码混为一谈。

```c
struct Flags {
    unsigned int up    : 1;
    unsigned int down  : 1;
    unsigned int left  : 1;
    unsigned int right : 1;
};
```

该写法让结构体成员使用指定数量的位；但实际布局、打包方式等存在实现相关性，不适合未经约定直接当作跨平台文件或网络协议的固定位布局。

---

## 9. 本次学习中真正弄懂的易错点

> [!success] 本次课堂推理要点
> 1. `move(a)` 如果按值接收结构体参数，修改的是结构体**副本**；返回新结构体也不会自动修改原来的 `a`。
> 2. **浅拷贝**只复制指针成员保存的地址，所以副本 `d.ptr` 可能仍指向主函数的 `x`；修改 `*d.ptr` 就会修改 `x`。
> 3. 但如果 `d.ptr = &y`，只是改变副本的指向，原结构体的 `a.ptr` 保持不变。
> 4. `const int *p`：不能通过 `p` 修改 `*p`；`int *const p`：不能改变 `p` 保存的地址，但可修改 `*p`。
> 5. `(A ^ B) ^ B = A`：用相同 key 异或两次可恢复原值。
> 6. 位移可能丢弃 bit，**先右移再左移通常不是逆操作**；有符号左移也要注意未定义行为。
> 7. **AND 检查、OR 设置、AND+NOT 清除、XOR 翻转**。
> 8. 合并 flags 用 OR；XOR 会把“两边都为 1”的位置变成 0。

---

## 10. 考前速查表

### 10.1 函数与结构体

| 知识 | 一句话 |
| --- | --- |
| `f(x)` 传普通整数 | 函数收到整数值的副本 |
| `f(&x)` 传指针 | 函数收到地址值的副本，可经 `*p` 改原对象 |
| `f(struct_value)` | 结构体成员值被按值传递 |
| `return struct_value;` | 返回一个结构体类型的值 |
| `const T *p` | 不能通过 `p` 修改 `T` 对象 |
| `T *const p` | 不能重新给 `p` 赋地址 |

### 10.2 位运算

| 需求 | 常用表达式 |
| --- | --- |
| AND | `a & b` |
| OR | `a \| b` |
| XOR | `a ^ b` |
| NOT | `~a` |
| 检查 bit N | `(state & (1u << N)) != 0` |
| 设置 bit N | `state \|= (1u << N)` |
| 清除 bit N | `state &= ~(1u << N)` |
| 翻转 bit N | `state ^= (1u << N)` |
| 合并 flags | `state1 \| state2` |
| 判断奇偶 | `(x & 1) != 0` |

> [!important] Obsidian 排版说明
> 表格中为避免 Markdown 把 `|` 解释为列分隔符，写成了 `\|`；粘贴到 Obsidian 后显示的仍然是 C 运算符 `|`。

---

## 11. 自测题与答案

> [!question] Q1 · 指针与副本
> ```c
> struct Data { int *ptr; };
> void f(struct Data d) {
>     int y = 50;
>     d.ptr = &y;
>     *d.ptr = 200;
> }
> int x = 10;
> struct Data a = {&x};
> f(a);
> ```
> 最后 `x` 等于多少？
>
> > [!success]- 答案
> > `10`。`d` 是副本；给 `d.ptr` 重新赋 `&y` 不改变 `a.ptr`，后续写的是 `y`。

> [!question] Q2 · `const`
> ```c
> int a = 10;
> int *const p = &a;
> *p = 30;
> a = 40;
> ```
> 最后 `*p` 是多少？
>
> > [!success]- 答案
> > `40`。`p` 的地址不变，`a` 的值可以改变。

> [!question] Q3 · XOR 可逆性
> ```c
> int x = 25;
> int key = 42;
> x ^= key;
> x ^= key;
> ```
> 最后 `x` 是多少？
>
> > [!success]- 答案
> > `25`。`(x ^ key) ^ key = x`。

> [!question] Q4 · 右移的信息丢失
> ```c
> unsigned int x = 13;
> unsigned int y = (x >> 1) << 1;
> ```
> `y` 为多少？
>
> > [!success]- 答案
> > `12`，因为 `1101 -> 110 -> 1100`。

> [!question] Q5 · 位掩码
> ```c
> unsigned char state = 0x0F; // 00001111
> state ^= (1u << 2);
> ```
> `state` 最后是多少？
>
> > [!success]- 答案
> > `00001011`，即十进制 `11`。bit 2 从 1 翻转成 0。

> [!question] Q6 · 综合训练（未在课堂中直接给出答案）
> 现在有 `unsigned char flags = 0x35;`。请**只通过位运算**依次：① 设置 bit 6；② 清除 bit 4；③ 翻转 bit 0；④ 检查 bit 6 是否为 1。你能算出每一步的 8 位结果吗？

---

## 12. 后续衔接

- [x] Lecture 10 理论：传参、结构体、`const`、位运算、位掩码。
- [ ] 核对对应实验任务的完成情况（以本学期发布的 Lab 要求为准）。
- [ ] 对照本笔记完成一道独立的 bit mask 小练习。
- [ ] **Lecture 11：Linked Lists（链表）**：结构体节点、`next` 指针、动态内存分配、链表插入与删除。
- [ ] **Lecture 12：File Input/Output**：文件读写、错误处理与数据持久化。

**复习关联**：[[Lecture 8]]（Pointers） · [[Lecture 9]]（Strings and Structures） · [[Lecture 11]]（Linked Lists）

> [!note] 课程顺序说明
> 本学期课程表将 Lecture 11 安排为 Linked Lists、Lecture 12 安排为 File Input/Output；旧版课件合集中下一讲的章节安排可能不同。后续以本学期安排为准。
