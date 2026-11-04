> **Clarification:** AI-generated content, reviewed by HZ-TYZQ (not yet).

# Lecture 8（下）学习笔记：Function Pointers、Callbacks、const 与 Dangling Pointers

**课程：** UESTC1005 — Introductory Programming  
**学习范围：** 接续 [`Lecture8_上_指针_学习笔记.md`](Lecture8_上_指针_学习笔记.md)，整理 Lecture 8 剩余知识点及当次练习。  
**整理日期：** 2026-11-02  
**资料依据：** 本项目的 UESTC1005 Lecture 8 课件汇编、前半部分学习笔记和本次实际问答／编程练习。  
**范围约定：** 标记为**【课件内容】**的部分以课程材料为依据；**【实战巩固】**来自学习对话或项目；**【补充辨析】**是学习时进一步澄清的标准与编程细节。本笔记不包含历年真题，真题留待期末复习。

---

## 0. 当前学习进度

| 主题                 | 学习结果                   | 主要证据                                                                                           |
| -------------------- | -------------------------- | -------------------------------------------------------------------------------------------------- |
| Reverse an Array     | 已独立完成                 | 双指针反转函数，后续集成到 SLSMS                                                                   |
| Function Pointers    | 已理解声明、赋值、调用     | 函数指针语法练习                                                                                   |
| Callbacks            | 已完成基础与编程练习       | `callbackPractice.c` 与 SLSMS 自定义排序                                                           |
| `const` and Pointers | 已完成内存地址辨析         | 比较 `const int *p`、`int *const p`                                                                |
| Dangling Pointers    | 已完成作用域和生命周期练习 | 内外层变量遮蔽与悬垂指针判断                                                                       |
| Lecture 8 综合项目   | 主体完成                   | [SLSMS 综合实战项目笔记](SLSMS_综合实战项目笔记.md) |

> **进度说明：** 上半部分旧笔记的“Reverse an Array 尚未完成／下次从这里开始”记录的是当时的进度；现在此项已经完成。历年真题统一安排在期末复习。

## 1. Reverse an Array：用双指针原地反转【实战巩固】

原始数组 `{10, 20, 30, 40, 50}` 需要变成 `{50, 40, 30, 20, 10}`，要求不创建第二个数组。

实际练习完成的算法：

```c
void reverse_array(int *arr, int size) {
    if (size <= 1) {
        return;
    }

    int *start = arr;
    int *end = arr + size - 1;

    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}
```

- `start` 保存首元素地址，`end` 保存最后一个有效元素的地址。
- `*start` 和 `*end` 是**被指向的整数**；交换它们才会改变原数组。
- `start++`、`end--` 改变的是**两个指针的位置**，不是元素本身。
- `start < end`：两个指针相遇（奇数长度）或交错（偶数长度）时停止。
- `size <= 1` 先返回，避免为长度为零的数组计算 `arr + size - 1`。
- 时间复杂度 `O(n)`；额外空间 `O(1)`。

**最关键的辨析：** `start++` 使指针移向下一个 `int`；`(*start)++` 才是让当前被指向的整数加一。

## 2. Function Pointers：函数指针【课件内容】

普通指针保存对象的地址；**函数指针保存函数的地址**，可以通过它调用相应函数。

```c
int add(int a, int b) {
    return a + b;
}

int (*operation)(int, int) = add;
int result = operation(3, 4);   // 7
```

函数指针声明的通用形式：

```c
return_type (*pointer_name)(parameter_list);
```

### 2.1 括号决定类型

| 声明                          | 含义                                                                |
| ----------------------------- | ------------------------------------------------------------------- |
| `int (*operation)(int, int);` | 指向“接收两个 `int`、返回 `int`”的函数的指针变量                    |
| `int *operation(int, int);`   | 名为 `operation` 的**函数声明**；该函数接收两个 `int`，返回 `int *` |

第二种不是指针变量。因为函数调用／声明的 `()` 与 `*` 结合时需要注意优先级；`(*operation)` 的括号不能随意省略。

### 2.2 为什么调用时可以省略 `*`？

```c
operation(3, 4);       // 合法
(*operation)(3, 4);    // 同样合法
```

C 语言允许直接通过函数指针使用调用运算符 `()`；上面两种调用等价。

但：

```c
*operation(3, 4);
```

会先调用 `operation(3, 4)`，再尝试解引用**返回值**。如果被指向函数返回的是普通 `int`，这就是无效的解引用，不能视为前两种写法的替代。

`operation = add;` 与 `operation = &add;` 在此处都可以赋予函数指针；调用前传递函数名 `add`，而不是先执行 `add(...)`。

## 3. Callbacks：把函数交给另一个函数【课件内容 + 实战巩固】

**Callback（回调）**：把函数指针作为参数传递，由接收方在需要时调用这个函数。

课件使用按钮／门铃事件作为示例：事件发生时可以执行 `onClick` 或 `onRelease`。为避免课件示例中“声明返回 `int` 但没有返回值”的问题，以下示意用 `void`：

```c
void onClick(void) {
    printf("Play sound\n");
}

void simulateButton(void (*callback)(void)) {
    callback();
}

// 调用者：
simulateButton(onClick);
```

- `simulateButton` 是**接收并执行回调的函数**。
- `onClick` 是**被传入的回调函数**。
- `simulateButton(onClick)` 传的是函数地址；`onClick()` 则表示立即调用，不能把这种 `void` 调用结果当作函数指针传入。
- 回调的价值是把“**执行什么**”交给调用者决定，而“**怎样安排执行**”保留在通用函数中。

### 3.1 独立练习：`callbackPractice.c`

实际完成了 `add`、`subtract`、`multiply` 和接收函数指针的 `executeOperation`：

```c
void executeOperation(int (*operation)(int, int), int x, int y) {
    printf("Result: %d\n", operation(x, y));
}
```

分别传入三种运算函数，使用参数 `10`、`5`，得到 `15`、`5`、`50`。同一个 `executeOperation` 不必通过 `if` 或 `switch` 判断具体运算函数。

### 3.2 进阶应用：SLSMS 的 Callback 排序

本次综合项目将升序和降序条件拆成两个函数，再由同一个 `bubbleSort` 调用比较函数：

```c
int shouldSwapAscending(int left, int right) {
    return left > right;
}

int shouldSwapDescending(int left, int right) {
    return left < right;
}

void bubbleSort(int data[], int count, int (*shouldSwap)(int, int));
```

这里两个简洁比较函数表达了**与原项目函数相同的规则**；项目中实际写法是完整的 `if...else`。

- 升序时传 `shouldSwapAscending`，降序时传 `shouldSwapDescending`。
- `shouldSwap(data[j], data[j + 1])` 返回非零，则交换相邻元素。
- 相等时不交换，保留冒泡排序的稳定性。
- 比较函数只回答“**应否交换**”；真正交换的是 `bubbleSort`。

**【课件与代码辨析】** 课件函数指针示例中的 `subtract` 一处误写为 `return a+b;`；若要求减法，应为 `return a-b;`。项目代码采用了正确的运算逻辑。

## 4. `const` 与指针：用内存地址来辨析【课件内容 + 补充辨析】

假设：`a` 在 `0x1000`（值为 `10`），`b` 在 `0x1004`（值为 `20`），指针 `p` 自身位于 `0x2000`，并保存 `0x1000`。

| 表达式    | 含义                                            |
| --------- | ----------------------------------------------- |
| `p`       | 指针中保存的地址，例如 `0x1000`                 |
| `&p`      | 指针变量自己的地址，例如 `0x2000`               |
| `*p`      | 读取／修改 `p` 所指地址中的对象，例如整数 `10`  |
| `p = &b`  | 把 `p` 保存的地址改成 `0x1004`                  |
| `*p = 99` | 修改当前所指地址中的整数，而不是修改 `p` 的地址 |

### 4.1 三种重要限定方式

| 声明                       | 能重新让 `p` 指向别处？ | 能通过 `p` 修改所指整数？ |
| -------------------------- | ----------------------- | ------------------------- |
| `const int *p = &a;`       | 能                      | 不能                      |
| `int *const p = &a;`       | 不能                    | 能                        |
| `const int *const p = &a;` | 不能                    | 不能                      |

**示例一：**

```c
int a = 10, b = 20;
const int *p = &a;
p = &b;      // 合法：修改 p 保存的地址
// *p = 30; // 不合法：不能通过 p 修改整数
```

`const int *p` 不表示对象永远不能改变：如果 `a` 本身是普通的 `int`，那么直接 `a = 30;` 仍然合法。

**示例二：**

```c
int a = 10, b = 20;
int *const p = &a;
*p = 99;     // 合法：修改 a
// p = &b;  // 不合法：p 保存的地址受 const 限制
```

### 4.2 课件示例的类型问题【补充辨析】

课件有一例将 `const int a = 40;` 与 `int *ptr = &a;` 放在一起。规范的写法应是：

```c
const int a = 40;
const int *ptr = &a;
```

不能丢弃所指对象的 `const` 限定，也不能试图经由普通 `int *` 修改 `const` 对象。

### 4.3 C11 二维数组 `const` 参数的实战坑【实战巩固】

对普通二维数组：

```c
int readings[3][5] = {{0}};
```

严格 C11 中，将其传入 `void display(const int a[][5]);` 会涉及从 `int (*)[5]` 到 `const int (*)[5]` 的限定转换；在 GCC 14.2 使用 `-std=c11 -Wpedantic -Werror` 时会报错（C23 前的数组限定兼容问题）。

本项目实际采用：

```c
void displayReadings(int readings[][MAX_READINGS],
                     const int counts[]);
```

- 二维数组参数不加 `const`，保持严格 C11 类型兼容；函数实现仍按**只读约定**处理数据。
- 一维数组参数 `const int data[]` 在 C11 中可以接收 `int` 数组，因此 `calculateStats(readings[index], ...)` 合法。
- 这不是“C11 禁止使用 `const` 二维数组”，而是此类函数参数间的**限定类型转换**受限制。

## 5. Dangling Pointer：作用域、生命周期和悬垂指针【课件内容 + 实战巩固】

**悬垂指针**：指针曾经指向某个对象，但该对象已经结束生命周期或内存已被释放，不能继续安全地通过它访问原对象。

```c
int *p = NULL;

{
    int x = 100;
    p = &x;
    printf("%d\n", *p);  // x 存活，输出 100
}

// x 已结束生命周期，此处不能再使用 *p 读取 x。
```

`{ ... }` 可以独立构成一个新的代码块。`x` 是内层的自动存储期局部变量，离开代码块后生命周期结束；`p` 在外层声明，作用域仍覆盖后续代码，但是原指向关系已失效。

### 5.1 直接使用变量名 vs 通过悬垂指针访问

- 离开内层作用域后直接写 `printf("%d", x);`：`x` 这个名字不再可见，编译器会诊断未声明标识符。
- 外层 `p` 仍可见，不意味着它还指向有效对象；解引用悬垂指针可能通过编译，却会产生未定义行为（Undefined Behavior）。
- 原地址中的物理字节即使看起来没有改变，也不能因此认定原对象还存在。

### 5.2 Shadowing：变量遮蔽

```c
int a = 10;
int *p = &a;

{
    int a = 20;    // 新的内层 a，遮蔽外层 a
    p = &a;
    printf("%d\n", *p);  // 20
}

p = &a;              // 重新指向外层仍存活的 a
printf("%d\n", *p);  // 10
```

- 内层 `int a = 20` **新建了另一个变量**，不会修改外层 `a` 的 `10`。
- `p = &a` 在内层取得的是**内层** `a` 的地址；若离开代码块后不重新赋值，不能再安全解引用 `p`。
- 返回外层后 `p = &a` 可以重新建立有效的指向关系。

### 5.3 `NULL` 与悬垂指针

| 类型        | 含义                                           |
| ----------- | ---------------------------------------------- |
| `NULL` 指针 | 明确表示当前不指向对象；不能解引用             |
| 有效指针    | 指向生命周期内、可按适用规则访问的对象         |
| 悬垂指针    | 原来指向的对象已失效，不允许再当作有效对象访问 |

课件建议初始化指针，并在释放动态内存后将相应指针设为 `NULL`；**补充注意**：设为 `NULL` 不能自动清除其他别名指针，也不代表 `NULL` 本身可以解引用。动态内存释放的具体操作留给后续课程。

## 6. Lecture 8 下半部分易错点速查

| 易错写法／理解                     | 正确理解                                                         |
| ---------------------------------- | ---------------------------------------------------------------- |
| `int *f(int,int)` 就是函数指针     | 它是返回 `int *` 的函数声明；函数指针须写 `int (*f)(int,int)`    |
| `f(3,4)` 必须写成 `(*f)(3,4)`      | 两种调用在 `f` 是相应函数指针时等价                              |
| `*f(3,4)` 等价于 `(*f)(3,4)`       | 不等价；前者先调用，再解引用返回值                               |
| 传 `onClick()` 给回调接收者        | 传 `onClick`（函数地址），而不是提前执行                         |
| `const int *p` 使 `p` 不能移动     | 限制通过 `p` 修改数据；`p` 自身可以改指向                        |
| `int *const p` 使 `*p` 只读        | 限制 `p` 重新赋值；可通过它修改非 const 对象                     |
| `p` 仍在作用域中，`*p` 就安全      | 必须同时检查所指对象的生命周期                                   |
| 第 5 个数组位置值为 `0` 就是空数据 | **是否有效由 `counts` 决定，不由元素是否为零决定**               |
| 任何二维数组都能传给 `int **`      | 二维 `int [R][C]` 调整为指向行数组的 `int (*)[C]`，不是 `int **` |

## 7. 后续安排

- [x] Lecture 8 下半部分概念与课堂练习
- [x] Reverse an Array 独立练习与项目复用
- [x] Callback 独立编程练习
- [x] Smart Lab Sensor Management System 核心功能与跨模块测试
- [ ] `scanf` 非整数输入、输入缓冲区、健壮性封装：**用户输入专项**
- [ ] 历年真题：**期末复习**
- [ ] 后续课程（Lecture 9 起）：按教学顺序继续

**关联代码：** [`SLSMS.c`](../../practiceCode/Course8Practice/src/SLSMS.c)；详见 [Course 8 Practice 笔记](SLSMS_综合实战项目笔记.md)。

## 8. 复习自测（不附答案）

1. `int (*f)(int,int)` 与 `int *f(int,int)` 分别声明了什么？
2. 为什么 `onClick` 能作为参数传给 `simulateButton`，而 `onClick()` 不行？
3. 假设 `p` 自身地址是 `0x2000`，`p` 保存 `0x1000`，执行 `p = &b` 改变了哪个内存位置里的内容？
4. 在 `const int *p` 和 `int *const p` 中，哪一种可以修改指针所指整数？
5. 为何局部变量退出作用域后，即使它原先的地址还残留数值，也不能继续解引用先前指向它的指针？
6. 为何在本项目里 `reverse_array(readings[i], counts[i])` 不能写成传 `MAX_READINGS`？
