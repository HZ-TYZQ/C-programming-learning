---
title: "Course 10 综合实战笔记：Lab Device Monitor（LDM）"
aliases:
  - LDM 综合实战
  - Course10Practice
  - 实验室设备监测系统
course: UESTC1005
lecture: 10
project: Course10Practice
date: 2026-11-12
status: 核心功能已实现；已报告单元测试通过；完整交互验收待逐项确认
tags:
  - C语言
  - UESTC1005
  - Lecture10
  - 综合实战
  - 结构体
  - 位运算
  - 函数指针
  - Makefile
  - 单元测试
---

> **Clarification：** 本文为 AI 根据学习讨论、已推送的项目源码及 `exercise.md` 辅助整理的**学习笔记**，不是学习者亲笔编写的源码；不修改任何 `.c` / `.h` 文件。reviewed by HZ-TYZQ

# Course 10 综合实战笔记：Lab Device Monitor（LDM）

> [!info] 资料来源与范围
>
> - 题目：[`Course10Practice/exercise.md`](../../practiceCode/Course10Practice/exercise.md)
> - 代码：[`device.h`](../../practiceCode/Course10Practice/src/device.h) · [`device.c`](../../practiceCode/Course10Practice/src/device.c) · [`main.c`](../../practiceCode/Course10Practice/src/main.c) · [`input.c`](../../practiceCode/Course10Practice/src/input.c) · [`test.c`](../../practiceCode/Course10Practice/src/test.c) · [`Makefile`](../../practiceCode/Course10Practice/Makefile)
> - 关联：[[Lecture 10 - Structures and Bit Manipulation]] · [[SLSMS_综合实战项目笔记]] · [[SRMS_2.0_综合实战项目笔记]]
> - 本文按**实际题面约定**记录；尤其排序回调沿用 Course8 的 `shouldSwap`（`0`／非零）形式，而不是强制 `-1`／`0`／`1` 三态比较器。
> - 本次对话中多轮 `make test` 由学习者报告通过；仓库源码已审阅，但不等同于已经在学习者机器上完成 `exercise.md` 中每一项端到端验收。

## 0. 项目定位与知识地图

LDM 是一个**固定容量、纯内存、命令行**设备管理系统。它不是文件数据库；退出程序后数据不会自动持久化。

```text
========== Lab Device Monitor ==========
1. Register device
2. Display all devices
3. Change device state
4. Add reading
5. View device report
6. Filter devices by flags
7. Sort devices
0. Exit
========================================
```

| 功能           | 关键函数／知识点                                                                 |
| -------------- | -------------------------------------------------------------------------------- |
| 注册及查找设备 | `registerDevice()`、`findDeviceById()`；结构体数组、唯一 ID、失败原子性          |
| 状态控制       | `toggleOnline()`、`setMaintenance()`；XOR、OR、AND、NOT                          |
| 状态显示       | `printDevice()`、`printAllDevices()`、`printFlags()`；移位、掩码                 |
| 录入采样       | `addReading()`；先检查后修改、位状态同步                                         |
| 统计报告       | `calculateStats()`、`printDeviceReport()`；`const`、返回结构体、浮点除法         |
| ANY／ALL 筛选  | `matchesFlags()`、`filterDevices()`；位运算、结果下标数组                        |
| 两种排序       | `compareById()`、`compareByAverage()`、`sortDevices()`；函数指针、回调、冒泡排序 |
| 菜单与构建     | `main.c`、`input.c`、`Makefile`；作用域、EOF、依赖图、增量构建                   |

---

## 1. 数据模型：固定容量 ≠ 有效数量

### 1.1 常量与结构体

```c
#define MAX_DEVICES 10
#define NAME_SIZE 24
#define MAX_READINGS 10

struct Device {
    int id;
    char name[NAME_SIZE];
    int readings[MAX_READINGS];
    int readingCount;
    unsigned int flags;
};

struct ReadingStats {
    int count;
    int sum;
    int maximum;
    int minimum;
    double average;
};
```

| 项目         | 题目要求                                                |
| ------------ | ------------------------------------------------------- |
| 设备容量     | 最多 10 台                                              |
| ID           | 正整数、唯一；ID **不等于**数组下标                     |
| 名称         | 最多 23 **字节**，另留 `\0`；允许中间有空格，不能全空白 |
| 每台采样容量 | 最多 10 个整数                                          |
| 合法采样     | `0～100`，含端点                                        |
| 正常采样     | `10～90`                                                |
| 报警采样     | `0～9` 或 `91～100`                                     |

**关键不变量（Invariants）：**

1. `0 <= deviceCount <= MAX_DEVICES`；只有 `devices[0]` 到 `devices[deviceCount - 1]` 有效。
2. `0 <= readingCount <= MAX_READINGS`；只有 `readings[0]` 到 `readings[readingCount - 1]` 有效。
3. `readings[i] == 0` **不能**代表“没有记录”，因为 `0` 是合法采样。
4. `HAS_DATA` 与有效采样数一致：首次成功录入后置 1。
5. `ALARM` 只表示**最近一次成功录入**的采样是否异常，不表示历史上是否发生过报警。
6. 排序后设备的**位置**可以变化；涉及 ID 的操作要重新 `findDeviceById()`，不要缓存旧下标。

> [!warning] 容量与数量
> `MAX_READINGS == 10` 表示数组可存 10 条；`readingCount == 3` 表示目前只有下标 `0、1、2` 有效。**下一条应写入下标 3**。

### 1.2 结构体整体赋值与清零

```c
struct Device temp = {0};
// 设置 id、name、flags 等成员后：
devices[*count] = temp;
```

- `{0}` 会使结构体所有数值成员初始化为零、字符数组为空字符串。
- `devices[*count] = temp` 会复制**整个结构体**，包括名称、采样数组、计数和状态位。
- 对当前这种仅含内嵌数组和数值成员的结构体，整体赋值适用；若结构体将来包含指针成员，则复制的是指针值，不会深拷贝其指向的数据。

---

## 2. 结构体指针、`const` 与返回结构体

### 2.1 `.`、`->`、数组与指针

```c
devices[i].id                // 数组第 i 项的成员
(devices + i)->id            // 等价写法
device->readingCount         // 等价于 (*device).readingCount
```

- **修改调用者对象**：传 `struct Device *`，例如 `addReading(struct Device *device, int value)`。
- **只读取设备**：传 `const struct Device *`，例如 `calculateStats()`、两个比较器。
- **修改主菜单里的设备数量**：传 `&deviceCount`；C 语言形参本身仍然是按值传递，函数获得的是地址的副本。
- **一次返回多个统计值**：`struct ReadingStats calculateStats(const struct Device *device)` 按值返回结构体；无需五个输出指针。

> [!tip] 职责分离
> `device.c` 负责业务规则；`input.c` 负责输入解析；`main.c` 负责询问用户、调用业务函数和输出反馈；`test.c` 负责断言测试。

### 2.2 `static` 辅助函数

`static void printMenu(void)` 是 `main.c` 内部使用的辅助函数。文件作用域函数加 `static` 后具有**内部链接**，其他翻译单元不能通过同名外部符号调用它。不要与“静态局部变量保留值”混为一谈。

---

## 3. 四个位状态：检查、设置、清除、翻转

```c
#define ONLINE      (1u << 0)   // 0001 = 1
#define MAINTENANCE (1u << 1)   // 0010 = 2
#define ALARM       (1u << 2)   // 0100 = 4
#define HAS_DATA    (1u << 3)   // 1000 = 8
```

| 操作     | 关键表达式            | 含义                 |
| -------- | --------------------- | -------------------- |
| 检查某位 | `(flags & MASK) != 0` | 此位是否开启         |
| 开启某位 | `flags                | = MASK`              | 设置为 1，保持其他位 |
| 关闭某位 | `flags &= ~MASK`      | 设置为 0，保持其他位 |
| 翻转某位 | `flags ^= MASK`       | 1 ↔ 0                |

- `ONLINE` 手动切换用 **XOR**，不能用单纯赋值覆盖全部状态。
- `MAINTENANCE` 开启用 **OR**、关闭用 **AND + NOT**；重复开启或关闭应当**幂等**。
- `ALARM`、`HAS_DATA` 不允许用户手动改；它们由成功录入采样自动维护。
- 设备离线或进入维护模式，已有采样、`HAS_DATA`、`ALARM` 不会自动清空。

### 3.1 低 8 位二进制打印

```c
for (int i = 7; i >= 0; --i) {
    printf("%u", (flags >> i) & 1u);
}
printf("\n");
```

依次提取 bit 7 到 bit 0；即使 `flags = 0x10B`，输出仍是 `00001011`。循环变量用 `int`；若用 `unsigned int i` 配合 `i >= 0` 倒数，条件永远成立，减到 0 后会回绕，后续移位还可能产生未定义行为。

### 3.2 核心状态转移表

| 操作                        | 二进制 flags | readingCount |
| --------------------------- | ------------ | -----------: |
| 新设备注册                  | `00000001`   |            0 |
| 成功录入 `95`               | `00001101`   |            1 |
| 成功录入 `50`               | `00001001`   |            2 |
| 开启维护                    | `00001011`   |            2 |
| 再开启维护                  | `00001011`   |            2 |
| 维护中尝试录入 `20`（拒绝） | `00001011`   |            2 |
| 关闭维护                    | `00001001`   |            2 |
| 切换离线                    | `00001000`   |            2 |
| 离线尝试录入 `20`（拒绝）   | `00001000`   |            2 |
| 恢复在线                    | `00001001`   |            2 |
| 尝试录入 `101`（拒绝）      | `00001001`   |            2 |

> [!important] 报警不是永久标记
> 先录入 95、再录入 50：两条数据都留下，但 `ALARM` 从 1 变为 0。**被拒绝**的采样不得改变 ALARM。

---

## 4. 注册与录入：先检查，后写入

### 4.1 注册设备 `registerDevice()`

实际项目使用以下状态码：

| 返回值 | 含义             |
| ------ | ---------------- |
| `0`    | 注册成功         |
| `-1`   | 达到设备容量     |
| `-2`   | ID 非正数        |
| `-3`   | ID 重复          |
| `-4`   | 名称过长         |
| `-5`   | 名称为空或全空白 |

流程：先验证**容量 → ID → 去重 → 名称长度 → 是否全空白**，全部通过才准备完整设备、写到 `devices[*count]` 并 `(*count)++`。失败不改变设备总数与现有记录。

`strlen(name)` 计算字符串字节长度（不含终止 `\0`）；`strspn(name, " \t\n\r\v\f") == strlen(name)` 可识别全空白名称。`NAME_SIZE = 24` 能存最多 **23 字节名称 + 1 字节终止符**。

### 4.2 录入 `addReading()`

当前实现检查顺序与错误码：

| 返回值 | 原因              |
| ------ | ----------------- |
| `-1`   | 离线              |
| `-2`   | 维护中            |
| `-3`   | 容量已满          |
| `-4`   | 数值不在 `0～100` |
| `0`    | 成功              |

成功录入时的核心步骤：

```c
device->readings[device->readingCount] = value;
device->readingCount++;
device->flags |= HAS_DATA;

if (value >= 10 && value <= 90) {
    device->flags &= ~ALARM;
} else {
    device->flags |= ALARM;
}
```

**为什么先写入再自增？** `readingCount` 本身就是下一个空闲位置的下标。如果先自增，会跳过位置；原有 9 条时甚至可能写到 `readings[10]`，发生越界。

**为什么容量判断用 `>= MAX_READINGS`？** 不仅拒绝恰好装满的设备，也防止异常计数已经大于容量时继续写入（但不会代替对负数或损坏对象的全面检查）。

> [!warning] 失败路径的契约
> 任何条件失败后，**采样数组、readingCount、flags 全部保持原样**。特别是尝试录入正常值 `50` 失败时，不能顺手清除之前由 `95` 触发的报警。

---

## 5. 统计：返回 `struct ReadingStats`

```c
struct ReadingStats calculateStats(const struct Device *device);
```

算法的关键设计：

1. `struct ReadingStats stats = {0};`：所有结果初始化为零。
2. `readingCount == 0`：立刻返回全零结构体，不读 `readings[0]`，不除以零。
3. 非空时，用 `readings[0]` 初始化 `sum`、`maximum` 和 `minimum`，`count = readingCount`。
4. 遍历下标 `1` 到 `count - 1`，累加并更新极值。
5. `stats.average = (double)stats.sum / stats.count;`，最后 `return stats;`。

示例：`[80, 20, 95, 50]` → `count = 4`、`sum = 245`、`minimum = 20`、`maximum = 95`、`average = 61.25`。

> [!danger] 整数除法陷阱
> `stats.sum / stats.count` 两者均为 `int`，结果先被**截断**，即使随后赋给 `double` 也无法找回小数。 `(double)stats.sum / stats.count` 才会执行浮点除法。

无采样时统计函数内部返回全零，但**用户界面**应显示 `No readings`，平均值与极值显示 `N/A`，不能把占位零误当作实际测量结果。

---

## 6. 状态筛选：ANY、ALL 与输出下标数组

```c
// ANY：至少一个指定状态位
(flags & mask) != 0

// ALL：拥有所有指定状态位
(flags & mask) == mask
```

`mask` 必须是十进制 `1～15`；`requireAll = 0` 表示 ANY，`1` 表示 ALL。ALL 允许设备有**额外**的状态位，并不要求 `flags == mask`。

示例：`flags = ONLINE | HAS_DATA`（9），`mask = ONLINE | ALARM`（5）：

- `flags & mask == 1`：ANY 匹配；
- `flags & mask != mask`：ALL 不匹配。

`filterDevices()` 只读遍历已注册设备，把匹配位置写入 `matchedIndices`，返回命中数：

```c
if (matchesFlags(&devices[i], mask, requireAll)) {
    matchedIndices[matchedCount] = i;
    matchedCount++;
}
```

- `i` 是**原设备数组下标**。
- `matchedCount` 是已经命中的数量，也是结果数组的**下一个写入位置**。
- 调用者预分配容量足够的数组（例如 `int matchedIndices[MAX_DEVICES];`），但**只有前 `matchedCount` 项有效**。
- 如果没有匹配，返回 `0`，不要读取结果数组的旧内容。

---

## 7. 回调排序：本题用的是 `shouldSwap` 约定！

### 7.1 两套比较器惯例不要混淆

> [!important] `exercise.md` 1.7 的真实约定
> **比较器接收两台 `const` 设备指针，返回非零意味着“左边应该排在右边之后”，返回 0 表示“不用交换”。** 这沿用 Course8 的 `shouldSwap` 思路，并**不要求**负数／零／正数三态语义。

| 左右顺序             | 本题比较器返回    |
| -------------------- | ----------------- |
| 已符合目标顺序       | `0`               |
| 左侧本应排在右侧之后 | `1`（或其他非零） |

因此当前 `compareById()` 的规则是：`left.id > right.id` 返回 `1`；其他情况返回 `0`。**不要擅自把“小于”分支改成 `-1`，题目没有这个要求。**

对两个均有采样的设备，`compareByAverage()` 遵循降序：左边平均值更低才返回 `1`；同分时复用 `compareById()`。有采样总在无采样前面，**即便有采样的平均值为 `0.0`**；两台均无采样时按 ID 升序。

### 7.2 函数指针的作用

```c
void sortDevices(struct Device *devices, int count,
                 int (*compare)(const struct Device *,
                                const struct Device *));
```

`compareById` 与 `compareByAverage` 是**可传递的函数**；`compareById(a, b)` 则是**立即调用**并得到返回值。

```c
sortDevices(devices, count, compareById);
sortDevices(devices, count, compareByAverage);
```

把**排序算法**与**比较规则**解耦，避免为每种规则复制冒泡排序代码。

### 7.3 冒泡排序与结构体交换

```c
if (compare(&devices[j], &devices[j + 1]) > 0) {
    struct Device temp = devices[j];
    devices[j] = devices[j + 1];
    devices[j + 1] = temp;
}
```

- 当前比较器只返回 `0` 或 `1`，所以 `> 0` 与 `!= 0` 在**当前实现**中等价；题面若允许任意非零值，`!= 0` 更直接表达合同。
- 内层边界 `j < count - i - 1` 防止访问 `j + 1` 越界，且不再扫描已就位的尾部。
- 使用临时变量交换**整个 `struct Device`**，不能只交换 ID，否则名称、采样、flags 会错位。
- 只在需要交换时才交换，相等时不交换，因此此冒泡排序保留相同排序优先级元素的原相对顺序。

---

## 8. 输入模块与菜单：复用已有能力

### 8.1 输入接口

```c
int readInt(const char *prompt, int *value);
char *readString(const char *prompt, char *string, size_t capacity);
```

`readInt()` 利用 `fgets()`、`strtol()` 和范围判断处理整数；遇到非法文字会在函数内部重试，遇到 EOF 返回 `0`。`readString()` 读取一行、移除换行、检查超长输入，失败或 EOF 返回 `NULL`。

```c
if (!readInt("Enter choice: ", &choice)) {
    return 0; // EOF 或无法读取，正常退出
}
```

**输入合法不等于业务合法**：读入整数 `99` 成功，但它不是合法菜单选项，需要 `switch` 的 `default` 处理；设备 ID、读数、筛选掩码仍由对应业务逻辑验证。

### 8.2 `main()` 的变量生命周期与菜单控制

```text
main(): devices[MAX_DEVICES] = {0}, deviceCount = 0
   ↓
while (1)
   ↓
printMenu → readInt → switch(choice)
   ├─ case 0: return 0（结束 main）
   ├─ case 1..7: 执行业务，break（只退出 switch）
   └─ default: 提示非法选项，继续下一轮
```

- `devices` 和 `deviceCount` 在 **while 外** 初始化一次；放在循环内会导致每一轮清空已注册设备。
- 每个菜单分支使用 `{ ... }`，便于声明本分支局部变量。
- 若 `case` 的操作完毕忘记 `break`，可能 **fall through** 到下一项；多个连续空 `case` 标签共用代码则是允许的设计。
- 先 `findDeviceById()` 得到合法下标，找不到（`-1`）就停止，不得使用 `devices[-1]`。

### 8.3 显示与报告函数的职责

`case 2` 只调用 `printAllDevices(devices, deviceCount)`；`printAllDevices()` 判断空表、遍历有效设备，再委托 `printDevice()` 输出基本信息、四个文字状态以及 8 位 flags。`case 5` 通过 `printDeviceReport()` 显示全部采样与统计结果。相比在 `main()` 重复打印，分层后更容易复用（例如筛选后打印设备）。

---

## 9. Makefile：依赖图、自动变量与伪目标

### 9.1 实际构建结构

```text
all
├── builds/ldm
│   ├── builds/main.o    ← src/main.c, src/device.h, src/input.h
│   ├── builds/device.o  ← src/device.c, src/device.h
│   └── builds/input.o   ← src/input.c, src/input.h
└── builds/test_ldm
    ├── builds/test.o    ← src/test.c, src/device.h
    └── builds/device.o  ←（同一个共享目标文件）
```

`main.c` 和 `test.c` 都定义了 `main()`，**不能链接到同一个可执行文件**；一个用于交互，一个用于测试。

```makefile
.PHONY: all test clean run
all: builds/ldm builds/test_ldm

test: builds/test_ldm
	./builds/test_ldm

run: builds/ldm
	./builds/ldm

clean:
	rm -f builds/*.o builds/test_ldm builds/ldm
```

> [!tip] `.PHONY` 不会删除或屏蔽文件
> 它只是告诉 Make：`all`、`test`、`run`、`clean` 是命令目标，不按同名实体文件判断“是否已完成”。例如目录中存在普通文件 `clean`，`make clean` 仍会执行清理配方。**不要把真实构建产物** `builds/ldm` 声明成 `.PHONY`。

### 9.2 自动变量速查

| 写法         | 含义                       | 示例                                           |
| ------------ | -------------------------- | ---------------------------------------------- |
| `$@`         | 当前目标                   | `builds/main.o`                                |
| `$<`         | 第一个依赖                 | `src/main.c`                                   |
| `$^`         | 所有依赖（去重）           | `builds/main.o builds/device.o builds/input.o` |
| `$(CC)`      | Make 变量                  | `gcc`                                          |
| `$(CFLAGS)`  | 编译选项                   | `-std=c11 -Wall -Wextra -Wpedantic -g`         |
| `builds/*.o` | shell 通配：所有 `.o` 文件 | 在 `rm -f` 命令中展开                          |

`make 目标` 的过程：**递归检查依赖 → 先更新依赖 → 根据时间戳／文件存在性决定是否更新目标 → 执行目标命令**。构建不是通过理解源代码实际差异来判定的。

- 只修改 `src/main.c` → 重建 `main.o` 和 `ldm`。
- 只修改 `src/input.h` → 重建 `input.o`、`main.o` 和 `ldm`。
- 修改 `src/device.h` → 重建 `device.o`、`test.o`、`main.o`，继而重链接两个程序。

**真实踩坑：** `mkdir - p builds` 多了空格，正确是 `mkdir -p builds`；相同的 `builds/ldm` 配方重复声明会触发覆盖警告。

---

## 10. 测试设计：AAA 与失败不变量

AAA = **Arrange（准备）→ Act（执行）→ Assert（验证）**。

测试不应只看返回码，还应检查**副作用与非预期修改**。

| 测试                         | 重点                                                                          |
| ---------------------------- | ----------------------------------------------------------------------------- |
| 注册成功、重复 ID、非法名称  | 返回码、`deviceCount`、旧设备不变                                             |
| 切换 ONLINE、维护开关        | 目标位变化；重复设置幂等；其他位不变                                          |
| `printFlags()`               | `11` → `00001011`、`0x10B` → `00001011`、`0` → `00000000`；当前为人工核对输出 |
| 录入 `95` 再录入 `50`        | `ALARM` 开后关、`HAS_DATA` 常开、历史样本保留                                 |
| 离线、维护、数组满、数值越界 | 拒绝录入时采样数组、计数、flags 不变                                          |
| 统计：普通、空、一条         | `count`、`sum`、`min/max`、`average` 都正确                                   |
| 筛选 ANY／ALL                | 匹配数量、返回下标以及“无命中”                                                |
| ID 与平均值排序              | 预期顺序、同分 ID、零平均值优先于无样本、结构体字段关联不破坏                 |

### 10.1 这次实际修正过的易错点

- **漏掉 `readingCount = 1`**：测试设置了 `readings[0] = 95`，但 `{0}` 初始化后计数仍为 0；测试 Arrange 自己就不符合场景。
- **只断言 ALARM**：即使忘记追加采样也可能通过；要检查返回码、数量、数组元素、完整 flags。
- **失败时使用相同新旧数据**：更容易掩盖误覆盖。选择能区分新旧状态的测试值。
- **容量测试**：第 11 条应该拒绝；若使用能触发报警的非法“追加尝试”，更易发现失败后误更新 flags。
- **浮点比较**：`61.25` 可在二进制浮点中精确表示，可直接断言相等；一般非精确值可考虑误差范围。
- **比较器约定混淆**：本题 `0` = 不交换，非零 = 应交换；无需为了通用 `qsort` 的三态惯例改写。

### 10.2 题面最终验收重点（建议逐项手动复核）

- [ ] 从空表显示、筛选、排序，不越界且提示合理。
- [ ] 注册重复 ID、非正 ID、全空白名称，以及第 11 台设备，都拒绝且旧数据不变。
- [ ] 按 **§3.2 状态转移表** 完成整轮交互：最终两条采样 `[95, 50]`，`sum = 145`、`average = 72.50`、`min = 50`、`max = 95`。
- [ ] 9、10、90、91 的报警依次：开、关、关、开。
- [ ] 0、100 合法且报警；-1、101 非法且不影响历史数据。
- [ ] 第 11 条采样拒绝，不覆盖、不改变报警。
- [ ] 掩码 5：ANY 对在线／报警任一状态匹配；ALL 要求同时在线且报警。
- [ ] 相同平均值按 ID 升序；平均值零的**有数据**设备排在**无数据**设备之前。
- [ ] 排序后重新按 ID 查找报告，名称、状态、样本及其顺序保持关联。
- [ ] `abc`、`12abc`、超长输入、整数溢出、EOF 都能重试或正常退出，不提交半条记录。

> [!note] 当前完成度
> 仓库默认分支已包含菜单 1～7、设备模块、输入模块及测试代码；学习者已多次反馈 `make test` 通过。**完整端到端验收是否逐项通过，仍需要以上清单的实际运行记录。**

---

## 11. 复盘：这次真正学会了什么？

1. **数据模型先于操作**：容量、有效数量、唯一 ID、状态来源都必须有明确不变量。
2. **修改原对象必须有地址**：结构体指针使业务函数能修改设备；`const` 表达只读契约；返回结构体适合一次带回多个计算结果。
3. **位标志是状态机**：`|=`、`&= ~`、`^=` 目的不同；最新成功采样驱动 ALARM，不能让失败操作污染状态。
4. **算法与规则分离**：相同冒泡排序，通过函数指针接收两种 `shouldSwap` 回调就能切换排序策略。
5. **写代码同时设计测试**：成功路径检查结果，失败路径还要验证“不应发生的修改”。
6. **Makefile 是依赖图**：改了哪份源文件／头文件，只编译或链接必要目标，不要把所有源文件混到一个构建步骤。
7. **主程序只负责串联**：输入模块读数据，业务模块处理规则，显示函数组织输出，菜单不重复实现算法。

## 12. 自测题（先答再看答案）

1. `flags = ONLINE | HAS_DATA`，`mask = ONLINE | ALARM`：ANY 和 ALL 各返回什么？
2. 为什么 `readings[readingCount] = value; readingCount++;` 的次序不能交换？
3. 为什么 `stats.average = stats.sum / stats.count;` 可能算错？
4. 有采样 `[0]` 的设备和没有采样的设备，谁在平均值降序排序中靠前？
5. 本题的 `shouldSwap` 比较器返回 `0` 代表什么？
6. `make run` 时，若只修改 `src/input.h`，哪些文件重新生成？
7. 为什么 `case 1` 的 `break` 不会退出 `while (1)`？

> [!example]- 参考答案
>
> 1. ANY = 1；ALL = 0。
> 2. `readingCount` 指向下一个空位；先加会跳过一个下标，数组满前可能越界。
> 3. 两个 `int` 相除先做整数除法；至少一个操作数先转 `double` 才保留小数。
> 4. 有采样 `[0]` 的设备靠前；有合法零值 ≠ 没有样本。
> 5. 返回 0 表示当前左右顺序不需交换；非零表示左边应排在右边之后。
> 6. `input.o`、`main.o`、`ldm`（在题目所用的显式依赖 Makefile 下）。
> 7. `break` 退出最近的 `switch`（或循环），不是最外层 `while`；要退出 `main` 用 `return`。

---

**下一步：** 把 §10.2 的验收清单跑一轮；全部勾选后，提交代码与这份笔记，即可将 `Course10Practice` 标记为 **已完成并验收**。
