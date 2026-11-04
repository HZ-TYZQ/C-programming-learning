> **Clarification:** AI-generated content, reviewed by HZ-TYZQ (not yet).

# Course 8 综合实战笔记：Smart Lab Sensor Management System（SLSMS）

**课程：** UESTC1005 — Introductory Programming  
**覆盖范围：** Lecture 1–8（主线）；Lecture 6 的递归仅作为可选扩展，**尚未集成**。  
**项目源文件：** [`src/SLSMS.c`](../../practiceCode/Course8Practice/src/SLSMS.c)  
**整理日期：** 2026-11-02  
**说明：** 本文依据仓库里实际存在的 `SLSMS.c` 及本次逐阶段学习、代码审查和集成测试整理；**只整理笔记，不修改学生编写的 `.c` 源代码**。本项目不是 Lab 作业，也不是历年真题。

---

## 0. 项目概览

编写一个命令行传感器数据管理系统：3 台设备，每台最多存储 5 条 `0–100` 的整数测量值。菜单包含录入、显示、统计、搜索、反转、升降序排序和退出。

```text
========== SMART LAB ==========
1. Add a reading
2. Display all readings
3. Show device statistics
4. Search for a reading
5. Reverse device readings
6. Sort device readings
0. Exit
================================
```

### 核心数据模型

```c
#define DEVICE_COUNT 3
#define MAX_READINGS 5

int readings[DEVICE_COUNT][MAX_READINGS] = {{0}};
int counts[DEVICE_COUNT] = {0};
```

| 数据             | 实际含义                                |
| ---------------- | --------------------------------------- |
| `readings[i][j]` | 第 `i + 1` 台设备第 `j + 1` 个存储位置  |
| `counts[i]`      | 第 `i + 1` 台设备**已有的有效记录数量** |
| `DEVICE_COUNT`   | 总设备数（行数，3）                     |
| `MAX_READINGS`   | 单设备最大容量（列数，5）               |

**不可破坏的数据不变量（Invariants）：**

1. 正常运行时 `0 <= counts[i] <= MAX_READINGS`。
2. 只有 `readings[i][0]` 到 `readings[i][counts[i]-1]` 属于当前有效记录。
3. 数值 `0` 是合法测量值，不能用“元素为 0”判断是否录入。
4. 用户看到的设备编号是 `1–3`，数组行下标是 `0–2`，所以必须先验证 `device`，再计算 `deviceIndex = device - 1`。
5. 搜索、排序和反转只处理有效长度 `counts[i]`；后两项不改变 `counts[i]`。

## 1. 项目功能与对应学习内容

| 菜单          | 实现函数 / 入口             | 核心知识                                                       |
| ------------- | --------------------------- | -------------------------------------------------------------- |
| 菜单循环      | `main`、`showMenu`          | Lecture 1–5：`printf`、`scanf`、`do...while`、`switch`、作用域 |
| 1. Add        | `addReading`                | 二维数组写入、边界验证、有效长度维护                           |
| 2. Display    | `displayReadings`           | 嵌套循环、二维数组传参、一维 `const` 参数                      |
| 3. Statistics | `calculateStats`            | 数组遍历、整数／浮点除法、多个指针输出参数                     |
| 4. Search     | `searchReadings`            | 线性搜索、重复值、多结果数组                                   |
| 5. Reverse    | `reverse_array`             | 双指针、原地交换、数组行首地址                                 |
| 6. Sort       | `bubbleSort` + 两个比较函数 | 冒泡排序、函数指针、Callback                                   |

### `main()` 的总体流程

```text
初始化 readings 和 counts
        ↓
do { showMenu(); 读取 choice; switch(choice) { ... } }
        ↑                               ↓
        └────────── 非 0，返回菜单 ──────┘
        ↓
      选择 0，退出
```

`switch` 中的 `break` 只退出 `switch`，不直接退出外层 `do...while`；外层继续由 `choice != 0` 决定是否循环。多个菜单分支使用 `{ ... }` 隔离局部变量的作用域。

## 2. 数据录入：验证后写入【Step 2】

真实实现接口：

```c
void addReading(int readings[][MAX_READINGS], int counts[],
                int device, int value);
```

依次执行：

1. 验证 `1 <= device <= DEVICE_COUNT`。
2. 验证 `0 <= value <= 100`。
3. 计算 `deviceIndex = device - 1`。
4. 检查 `counts[deviceIndex] >= MAX_READINGS`，满额就返回。
5. 在下一条空位置写入 `readings[deviceIndex][counts[deviceIndex]] = value;`。
6. **成功写入后**执行 `counts[deviceIndex]++`。

关键语句：

```c
readings[deviceIndex][counts[deviceIndex]] = value;
counts[deviceIndex]++;
```

**开发时实际出现过的错误：**

- 最初把容量检查写为 `== 3`，混淆了 `DEVICE_COUNT = 3` 与 `MAX_READINGS = 5`。改为 `>= MAX_READINGS`。
- 最初把写入列下标写成 `counts[deviceIndex + 1]`，误用了**下一台设备**的记录数；设备 3 时还可能读取 `counts[3]` 而越界。正确的是 `counts[deviceIndex]`。
- 初始 `counts = {1, 2, 0}`，向设备 2 添加数据，应写入 `readings[1][2]`，随后 `counts` 变成 `{1, 3, 0}`。

## 3. 数据显示：容量不是有效长度【Step 3A】

实际接口：

```c
void displayReadings(int readings[][MAX_READINGS],
                     const int counts[]);
```

- 外层循环遍历 `i < DEVICE_COUNT`，代表**设备行数**。
- 内层循环遍历 `j < counts[i]`，代表该行**有效记录数**。
- `counts[i] == 0` 时打印 `No data.`。
- 遇到 `continue` 会跳过本轮循环剩余语句；如果行尾换行在它后面，必须先换行再 `continue`。项目最终采用 `printf("No data.\n")`。

**真实踩坑：** 最初外层写 `i < MAX_READINGS` 会遍历到设备行 3、4，超过数组有效行数，应改为 `i < DEVICE_COUNT`。

**C11 限定参数注意：** 本项目的二维数组参数是 `int readings[][MAX_READINGS]`，而 `counts[]` 是 `const int counts[]`。严格 C11 下，从 `int (*)[N]` 到 `const int (*)[N]` 的二维数组参数转换可能触发 `-Wpedantic`，因此没有在此函数二维数组参数前使用 `const`。尽管编译器没有强制只读保护，`displayReadings` 的设计职责仍是**只读**。

## 4. 数据统计：多个指针输出参数【Step 3B】

实际接口：

```c
void calculateStats(const int data[], int count,
                    int *sum, double *average,
                    int *minimum, int *maximum);
```

- 输入：一台设备的一维数组 `readings[deviceIndex]` 与其有效长度。
- 输出：通过 `&sum`、`&average`、`&minimum`、`&maximum` 传入调用者变量的地址。
- 在函数内以 `*sum` 等**解引用**形式写回计算结果。
- `*minimum`、`*maximum` 从 `data[0]` 初始化；**必须保证 `count > 0`**。
- `*average = (double)*sum / count;` 避免先执行整数除法。
- `case 3` 在调用前检查设备编号和是否有有效记录，确保不会使用未初始化的统计输出。

例：`{72, 85, 40}` 的 `Count = 3`、`Sum = 197`、`Average = 65.67`（`%.2f`）、`Minimum = 40`、`Maximum = 85`。

**学习中的模块化讨论：** 原先曾在统计函数内部检查 `count == 0` 并打印提示；最后将用户提示和有效性检查放在菜单调用方，计算函数只负责计算。当前接口的前置条件是 `count > 0`，调用者必须维护该条件。

## 5. 搜索所有匹配位置【Step 4A】

最初的单结果线性搜索只返回第一个下标。学习者主动要求改成：**所有相同数据的下标都保存到第二个数组中**。

实际接口：

```c
int searchReadings(const int data[], int count,
                   int target, int matches[]);
```

实际核心算法：

```c
int matchCount = 0;
for (int i = 0; i < count; i++) {
    if (data[i] == target) {
        matches[matchCount] = i;
        matchCount++;
    }
}
return matchCount;
```

- `i` 是**原数组下标**。
- `matchCount` 既是已找到的数量，也是**结果数组的下一处空位置**。
- `matches[]` 的容量至少应为 `count`。当前项目中使用 `int matches[MAX_READINGS]`，与单设备有效长度上限匹配。
- 返回 `0` 表示没有找到；不是旧接口的 `-1`。
- 如果数据为 `{0, 0, 0}`，目标为 `0`，则返回 `3`，有效结果为 `{0, 1, 2}`。
- 结果输出应标记为 **Indices**，不是 Device。设备编号只有用户选定的那一个，而 `matches[i]` 是该设备内部的数据位置。

## 6. 双指针原地反转【Step 4B】

真实接口：

```c
void reverse_array(int *arr, int size);
```

实际调用：

```c
reverse_array(readings[deviceIndex], counts[deviceIndex]);
```

- `readings[deviceIndex]`：当前设备**一整行的首元素地址**。
- `counts[deviceIndex]`：反转的**有效长度**，绝不是固定容量 `MAX_READINGS`。
- `start` 和 `end` 分别从首尾向内移动，通过 `temp` 交换 `*start`、`*end`。
- 长度 `<= 1` 时直接返回；长度 0 时菜单先显示 `No data to reverse.`。
- 时间 `O(n)`，额外空间 `O(1)`；反转不改变记录数量。

**重要区分：** `{40, 50, 60, 70, 0}` 且 `count = 4`，反转为 `{70, 60, 50, 40, 0}`；若 `count = 5`，最后的 `0` 是**有效记录**，反转才是 `{0, 70, 60, 50, 40}`。

## 7. Callback 冒泡排序【Step 5】

实际接口：

```c
int shouldSwapAscending(int left, int right);
int shouldSwapDescending(int left, int right);
void bubbleSort(int data[], int count, int (*shouldSwap)(int, int));
```

两种比较规则：

- 升序：`left > right` 时返回 `1`（应交换）。
- 降序：`left < right` 时返回 `1`。
- 相等时均返回 `0`，因此相等元素不互换，满足稳定性。

排序函数的关键结构（与真实代码逻辑一致）：

```c
for (int i = 0; i < count - 1; i++) {
    for (int j = 0; j < count - i - 1; j++) {
        if ((*shouldSwap)(data[j], data[j + 1])) {
            int temp = data[j];
            data[j] = data[j + 1];
            data[j + 1] = temp;
        }
    }
}
```

- 外层 `i` 记录已经完成的趟数；内层 `j` 访问左右相邻元素。
- `j < count - i - 1` 保证 `j + 1` 不越界，并跳过右侧已确定的部分。
- `(*shouldSwap)(x,y)` 与 `shouldSwap(x,y)` 在这里等价。
- `case 6` 负责决定是传 `shouldSwapAscending` 还是 `shouldSwapDescending`；排序函数本身不接受 `order`，也不需要判断升降序。
- 比较函数参数类型和返回类型必须与 `int (*shouldSwap)(int,int)` 对应；不要写 `shouldSwapAscending(10,20)` 代替函数指针。
- 时间复杂度 `O(n²)`；额外空间 `O(1)`。

## 8. 测试记录与结果

### 8.1 跨模块集成测试

学习者确认以下流程测试通过；整理笔记时又对仓库中的完整 `SLSMS.c` 执行了一次严格 C11 编译，并以脚本输入重跑该联动场景。

| 步骤 | 操作                         | 预期／观察结果                                            |
| ---- | ---------------------------- | --------------------------------------------------------- |
| 1    | 设备 1 依次录入 `40, 20, 40` | 有效记录数为 3                                            |
| 2    | 搜索 `40`                    | `matchCount = 2`；下标 `0 2`                              |
| 3    | 升序排序                     | `20 40 40`                                                |
| 4    | 再次搜索 `40`                | 下标变成 `1 2`                                            |
| 5    | 原地反转                     | `40 40 20`                                                |
| 6    | 统计                         | Count `3`、Sum `100`、Average `33.33`、Min `20`、Max `40` |

**得出的两个性质：**

1. 排序／反转改变**元素位置**，因此搜索得到的下标可能变化。
2. 排序／反转不改变**元素集合和有效长度**，因此总和、平均值、最小值、最大值不变。

### 8.2 编译检查

在整理当天使用 GCC 14.2 对仓库源文件执行：

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror \
    TYZQ/Practice_codes/Course8Practice/src/SLSMS.c -o SLSMS
```

检查通过。上面的命令为示例，输出文件 `SLSMS` 不需要提交仓库；本次也没有修改源文件。

### 8.3 建议的边界测试清单

- [x] 已确认联动流程：录入、搜索、升序、再次搜索、反转、统计
- [ ] 验证设备 1、2、3 数据互不干扰（保留为每次修改后的回归测试）
- [ ] 向同一台设备录入超过 5 次，观察 `Storage is full.`
- [ ] 录入 `0` 和 `100` 两个边界值
- [ ] 设备没有记录时，尝试显示、统计、搜索、反转、排序
- [ ] 单条记录下的反转和排序
- [ ] 含重复值数组的升序和降序

> 上面只将**本次明确重跑或确认的项目场景**标记为已完成；其余是留存的回归测试建议，不代表此前从未测试过。

## 9. 实际问题与改进记录

| 开发时遇到的问题                               | 原因                                         | 修正或结论                                                 |
| ---------------------------------------------- | -------------------------------------------- | ---------------------------------------------------------- |
| `addReading` 容量检查误写为 `3`                | 混淆设备数与单设备容量                       | 使用 `MAX_READINGS`                                        |
| `counts[deviceIndex + 1]` 作为写入位置         | 错把下一设备计数当当前设备计数，末设备会越界 | 使用 `counts[deviceIndex]`                                 |
| 显示模块外层写 `i < MAX_READINGS`              | 混淆行数和列数                               | 使用 `i < DEVICE_COUNT`                                    |
| 空设备时 `continue` 跳过换行                   | `continue` 跳过本轮剩余语句                  | 在 `continue` 之前先打印换行                               |
| 统计模块的空数据检查重复                       | 函数职责分配不明确                           | 调用者先验证 `count > 0`；计算函数只计算                   |
| 查找只返回一个匹配位置                         | 不能满足所有重复读数的需求                   | 新增 `matches[]` 保存所有下标，返回匹配数量                |
| 输出 `Device: matches[i] + 1`                  | 混淆设备编号和记录位置                       | 输出 `Indices: matches[i]`                                 |
| 二维数组参数添加 `const` 无法严格通过 C11 编译 | C11 数组限定类型转换问题                     | 显示函数二维数组参数不加 `const`，一维只读参数保留 `const` |
| 把反转称作排序                                 | 两者都改顺序，但目的不同                     | Reverse 是颠倒现有顺序；Sort 按比较规则重新排列            |

## 10. 已知限制和后续学习安排

1. **输入健壮性：** 目前 `scanf("%d", &...)` 的返回值没有普遍检查。遇到非整数输入时，变量可能保持不确定或旧值，剩余字符也可能导致重复读取失败；**本项目只在“用户输入可解析整数”的测试前提下验收核心流程**。用户明确决定将 `scanf`、输入缓冲区以及更健壮的输入处理留到单独专题，不在这次练习中强行加入。
2. **计算函数契约：** `calculateStats` 要求 `count > 0`，菜单已经做此检查。若未来复用该函数，应遵守前置条件或改成返回成功／失败状态的接口。
3. **固定容量：** 3 台设备、每台 5 条记录；尚未使用动态内存和文件持久化（后续课程内容）。
4. **递归拓展尚未做：** 可选地编写递归求和，并与已有的迭代统计结果比较。它不是当前已完成功能。
5. **课件真题：** 历年真题留到期末复习；这里记录的是自主练习项目。
6. **代码整理：** 源文件仍保留个别初始 `TODO` 注释和未使用的 `#include <iso646.h>`，不影响当前严格编译。这次按照 `AGENTS.md` 规则仅写笔记，没有擅自修改学生的 `.c` 文件。

## 11. 综合掌握结论与自测

这次练习串起了：`do...while`、`switch`、局部作用域、函数声明与调用、二维数组及有效长度、`const` 一维数组形参、指针输出参数、查找多结果、双指针反转、函数指针回调与冒泡排序。**核心系统已通过学习者确认的跨模块测试；这不等于所有异常输入和全部边界都完成覆盖。**

自检问题（不提供答案，供以后复习）：

1. 为什么 `counts[i]` 既能用作有效记录数，又能在录入前用作下一条数据的写入位置？
2. 为什么 `displayReadings` 外层必须使用 `DEVICE_COUNT` 而不是 `MAX_READINGS`？
3. 如果 `calculateStats` 收到 `count == 0`，当前接口可能有什么风险？
4. 搜索重复值时，`i` 与 `matchCount` 分别代表什么？
5. 为什么排序后同一读数的搜索下标可能改变，而平均值不变？
6. 为什么 `bubbleSort(data, count, shouldSwapAscending)` 正确，而传 `shouldSwapAscending(10,20)` 不正确？

**继续学习：** 代码保留在 [`src/SLSMS.c`](../../practiceCode/Course8Practice/src/SLSMS.c)；Lecture 8 后半部分的理论复习见 [`Lecture8_下_函数指针与指针安全_学习笔记.md`](../../Notes/LectureNotes/Lecture8_下_函数指针与指针安全_学习笔记.md)。
