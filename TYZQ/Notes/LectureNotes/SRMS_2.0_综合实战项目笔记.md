> **Clarification:** AI-generated content, reviewed by HZ-TYZQ (yes).

# Course 9 综合实战笔记：SRMS 2.0（Student Record Management System）

**课程：** UESTC1005 — Introductory Programming  
**练习定位：** Lecture 1–9 知识综合巩固；命令行、固定容量、内存版学生记录管理系统  
**整理日期：** 2026-11-09  
**练习源码目录：** [`TYZQ/practiceCode/Course9Practice/src/`](../../practiceCode/Course9Practice/src/)  
**资料依据：** 本次逐步编写、Code Review、测试输出与集成反馈；另核对了 GitHub 仓库 `AGENTS.md`、现有 SRMS 文件结构及此前 SLSMS 笔记风格。  
**范围说明：** 这是自主综合练习笔记，不是 Lab 作业或历年真题。本文记录已讨论和已完成的功能，不代写或更改学生的 `.c` / `.h` 文件。

> **版本提醒（重要）：** 截至本次整理，GitHub `main` 分支里的 [`student.c`](../../practiceCode/Course9Practice/src/student.c) 仍主要包含显示与添加函数，[`main.c`](../../practiceCode/Course9Practice/src/main.c) 的远端版本仍只有菜单 1、2、0。后续完成的 `findById()`、`findByName()`、`calculateStats()` 及菜单 3、4、5，是**学习对话中的本地实现与测试记录**，并不表示这些修改已经推送到 GitHub。后续提交前应以本地实际源码为准。

---

## 0. 目标、范围与最终成果

SRMS 2.0 使用 `struct Student` 保存学生学号、姓名和三门成绩，允许最多存储 20 名学生。项目的主要目的不是功能数量，而是将结构体、数组、指针、字符串、函数接口、多文件编译及输入验证整合成一个可测试的小项目。

本次实际完成的菜单功能：

```text
========== SRMS ==========
1. Add Student
2. Display All Students
3. Search Student by ID
4. Search Student by Name
5. View Student Statistics
0. Exit
==========================
```

| 功能 | 关键实现 | 本次学习结果 |
| --- | --- | --- |
| 显示一名学生 | `printStudent()` | 单个结构体指针、`->`、格式化输出 |
| 显示所有学生 | `printAll()` | 结构体数组、有效长度、复用单条显示函数 |
| 添加学生 | `addStudent()` | 容量限制、ID 去重、结构体整体赋值、修改 `count` |
| 读取整数 | `readInt()` | `fgets`、`strtol`、输入流残留、转换与范围检查 |
| 读取字符串 | `readString()` | 真实数组容量、`fgets`、换行符清理、超长输入 |
| 按学号查找 | `findById()` | 线性查找、返回下标与 `-1` |
| 按姓名查找 | `findByName()` | `strcmp()`、区分大小写、首个匹配项 |
| 成绩统计 | `calculateStats()` | 累加、浮点除法、最大/最小值、多个指针输出参数 |
| 菜单集成 | `main.c` | `switch`、`case` 作用域、用户交互与数据逻辑分离 |

**本版本不包含：** 动态内存、链表、删除/修改学生记录、排序、文件持久化。退出程序后，内存中的学生数据不会自动保存。

---

## 1. 项目分层与多文件编译

本次逐步形成以下文件分工：

```text
Course9Practice/src/
├── student.h    // 结构体、宏与学生数据接口
├── student.c    // 添加、显示、查找、统计的实现
├── input.h      // 输入函数的公开声明
├── input.c      // 输入读取、解析与内部辅助函数
├── main.c       // 主菜单、交互和业务输入规则
├── test.c       // 学生模块的独立测试
├── build.sh     // 简单编译/运行脚本
└── test.sh      // 测试辅助脚本
```

### 1.1 两组接口、两类职责

- `student.h` / `student.c`：负责学生记录的数据管理和计算，不负责从终端读取输入，也不负责在错误时追问用户。
- `input.h` / `input.c`：负责从 `stdin` 获取合法整数或可容纳的字符串，不知道什么是“学生”或“成绩”。
- `main.c`：负责菜单、提示、成绩必须在 `0–100` 之间等业务规则，并根据函数返回值决定显示什么。
- `test.c`：在不依赖交互菜单的情况下验证数据函数。

把输入处理抽到 `input.c` 的起因是一个**实际痛点**：原先处理 `scanf` 失败、输入残留和 EOF 的代码越来越长；学号、菜单选项、成绩又都需要重复读取。封装的目的是消除重复，而不是为了增加抽象层级。

### 1.2 `.h` 与 `.c` 的关系

- 头文件放对外接口、宏、类型定义；用 include guard 避免重复包含。
- 源文件定义函数，并通过 `#include` 使用相应声明。
- `static void discardLine(void)` 定义在 `input.c`：它具有**内部链接**，是该翻译单元内部的辅助函数，不需要放入 `input.h`。
- `static` 修饰文件作用域函数表示内部链接，与“函数内部 `static` 局部变量会保留值”不是同一种具体效果。

### 1.3 分别构建主程序和测试程序

```bash
gcc -std=c11 -Wall -Wextra -g main.c student.c input.c -o srms
./srms
```

独立测试学生模块可使用：

```bash
gcc -std=c11 -Wall -Wextra -g test.c student.c -o test_srms
./test_srms
```

`main.c` 和 `test.c` 都定义了 `main()`，**不能把这两个文件同时链接进同一个可执行程序**。曾短暂讨论过 Bash 编译脚本，但学习主线仍然是 C 代码本身，不额外引入 Makefile 等工具作为必需前提。

---

## 2. 数据模型：容量、有效人数和固定科目数

项目采用的结构体及常量：

```c
#define MAX_STUDENTS 20
#define NAME_SIZE 24
#define SUBJECT_COUNT 3

struct Student {
    int id;
    char name[NAME_SIZE];
    int scores[SUBJECT_COUNT];
};
```

主程序初始化：

```c
struct Student students[MAX_STUDENTS] = {0};
int count = 0;
```

需要始终区分三个概念：

| 名称 | 含义 | 当前值 |
| --- | --- | ---: |
| `MAX_STUDENTS` | 学生数组**总容量** | 20 |
| `count` | 已保存的**有效学生数量** | 运行时变化 |
| `SUBJECT_COUNT` | 每名学生的成绩数组固定长度 | 3 |

**核心不变量：** 正常运行中 `0 <= count <= MAX_STUDENTS`，有效记录为 `students[0]` 到 `students[count - 1]`。当 `count == 0` 时没有有效学生；值为 `0` 的学号或成绩不能被当作“记录是否存在”的判据。

`NAME_SIZE == 24` 表示姓名字符数组最多存储 **23 个普通字符加一个 `\0`**（按当前按字节处理的输入约定）。

### 2.1 为什么统计函数不需要额外传入成绩 `count`

`findById()` 处理的学生数组容量为 20，但当前人数不一定为 20，因此需要 `count`。

`calculateStats()` 接收的是一名有效学生的 `struct Student *`，其成员 `scores[SUBJECT_COUNT]` 的长度由类型定义固定为 3，因此直接遍历 `i < SUBJECT_COUNT` 即可。两种数组的“容量是否等于有效长度”不同，不能混淆。

---

## 3. 显示功能：从一名学生到整张表

### 3.1 `printStudent()`

实际学习中使用：

```c
void printStudent(const struct Student *student) {
    printf("%-8d%-8s", student->id, student->name);
    for (int i = 0; i < SUBJECT_COUNT; i++) {
        printf("%-8d", student->scores[i]);
    }
    printf("\n");
}
```

- `student->id` 等价于 `(*student).id`，但指针形式更直观。
- `%-8d`、`%-8s` 表示字段最小宽度为 8、左对齐；该宽度**不会截断**更长内容。
- 最后的换行保证下一名学生从新的一行开始。
- `const struct Student *` 表示函数不应该修改学生记录。

### 3.2 `printAll()`

```c
void printAll(const struct Student students[], int count) {
    printf("%-8s%-8s%-8s%-8s%-8s\n",
           "ID", "Name", "C", "Math", "English");
    printf("----------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printStudent(students + i);
    }
}
```

`students + i` 是指向第 `i` 名学生的指针，等价于 `&students[i]`。显示函数只遍历有效记录，而不是固定输出 20 行。

本阶段先用 `test.c` 建立三名学生 Mia、Ben、Leo，独立运行得到正确表格，再进入交互菜单。这样既验证函数，又避免在开发 UI 时同时排查数据输出的问题。

---

## 4. 添加学生：从只复制学号到整体结构体赋值

公开接口：

```c
int addStudent(struct Student students[], int *count,
               const struct Student *newStudent);
```

返回约定：

| 返回值 | 含义 | 是否修改记录 / `count` |
| ---: | --- | --- |
| `1` | 添加成功 | 在 `students[*count]` 保存记录，人数加 1 |
| `-1` | 学号重复 | 不添加，人数不变 |
| `0` | 数组已满 | 不添加，人数不变 |

### 4.1 执行顺序

1. 若 `*count >= MAX_STUDENTS`，返回 `0`。
2. 遍历 `0 <= i < *count`，若 `students[i].id == newStudent->id`，返回 `-1`。
3. 执行 `students[*count] = *newStudent;`。
4. 执行 `*count += 1;`，随后返回 `1`。

### 4.2 实际发生过的代码问题

初版成功路径是：

```c
(students + *count)->id = newStudent->id;
*count += 1;
return 1;
```

这**只复制了学号**，没有复制姓名和三门成绩；最终修正为：

```c
students[*count] = *newStudent;
*count += 1;
return 1;
```

这里左侧是一个结构体对象，右侧 `*newStudent` 也是结构体对象。**C 允许结构体整体赋值；结构体内部的字符数组和整数数组也会随结构体一起复制。**

`*count += 1;` 和 `(*count)++;` 在此处都正确，不必因为风格不同而改写。

### 4.3 实际测试记录

学习者在 `test.c` 中报告了如下结果：

```text
Add Alice: 1
count: 4
Add Another: -1
count: 4
fill 20 students: PASS (count=20, expect 20)
add when full: 0 (expect 0), count: 20 (expect 20) -> PASS
last slot unchanged: 219     Filler  60      70      80
```

- 原有记录为 Mia、Ben、Leo；添加 `{104, "Alice", {95, 98, 100}}` 后列表显示第四名学生，姓名和成绩完整。
- 尝试以相同学号添加 Another，函数返回 `-1`，`count` 仍为 4，Alice 的记录没有改变。
- 填充 20 名学生后再添加，返回 `0`，`count` 仍为 20，最后一个位置的原记录仍未改变。

特别重要的一条测试原则：**失败不仅要看返回值，还要看原有数据是否被错误改动。** 这是对函数行为的验证，而非要求在函数里增加层层防御检查。

---

## 5. 为什么单独做 `input.c`：从 `scanf` 到整行验证

### 5.1 起因：`scanf("%d")` 的返回值不足以证明整行合法

用户输入 `2abc` 时，`scanf("%d", &choice)` 可以成功转换开头的 `2` 并返回 `1`，但仍留下 `abc\n`。如果只检查返回值，就可能接受本来应该拒绝的输入。

因此，本项目决定：**先读取整行，再验证整行是否构成可接受的整数**。

`input.h` 的两个公开接口：

```c
int readInt(const char *prompt, int *value);
char *readString(const char *prompt, char *string, size_t capacity);
```

两种返回值的含义不同：`readInt` 成功时返回 `1` 并通过 `*value` 写入整数，无法继续读取时返回 `0`；`readString` 成功时返回 `string`，无法读取时返回 `NULL`。当前实现对非法输入采用提示并重试的交互方式。

**为什么 `readInt` 要用指针输出？** 用户输入的整数可能本身就是 `0`，不能让同一个返回值同时代表“整数 0”和“读取失败”。C 语言按值传递，通过整数指针参数可以把输入值写回调用者，同时让返回值表示状态。

### 5.2 `fgets()` 的容量与行尾问题

```c
char buffer[64];
if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
    return 0;
}
```

`fgets` 最多存入 `n - 1` 个字符，再附加 `\0`；如果读到了换行符，`\n` 也会被存入字符串。

例如 `char buffer[8]`，用户输入 `123456789` 后按 Enter：

```text
buffer: "1234567" + '\0'
stdin 剩余: '8' '9' '\n'
```

**没有在缓冲区中找到 `\n` 不等于一定超长**：有可能恰好读满允许的字符数，使 `\n` 留在输入流；也可能输入在没有换行符时遇到 EOF。

因此最终采用：先检查缓冲区有没有换行符；若没有，再用一次 `getchar()` 观察下一个字符。

| `getchar()` 的结果 | 解释 | 处理 |
| --- | --- | --- |
| `'\n'` | 输入刚好读到行尾 | 接受本次已读文本 |
| `EOF` | 行尾没有换行，输入已结束 | 接受本次已读文本 |
| 其他字符 | 当前行确有剩余字符 | 清理剩余行、报超长、重新输入 |

### 5.3 `discardLine()` 与 `static`

```c
static void discardLine(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}
```

- 函数只负责**消耗并丢弃当前行的剩余字符**，因此返回类型用 `void` 即可。
- `getchar()` 的返回类型是 `int`，因为除了普通字符还需表示 `EOF`。
- `\0` 是字符串结束字符，不代表标准输入流结束，不能用于此处的循环停止条件。
- **不可无条件调用** `discardLine()`；若 `fgets()` 已读完当前行，清理函数反而可能吞掉下一行输入。
- `static` 限制这个辅助函数的链接范围，只由 `input.c` 内部使用。

实际学习中的两处控制流错误：曾把 `ch == '\n' && ch == EOF` 写在一起（不可能同时成立），以及把 `discardLine()` 放在分支外无条件执行。分别改为合理的“或”条件，以及只在确实发生截断时清理。

### 5.4 `strtol()`：转换结果和转换终点

```c
char *end;
errno = 0;
long number = strtol(buffer, &end, 10);
```

`strtol` 会从字符串开头解析整数（可跳过开头空白），结果保存在 `long` 中，并通过 `end` 指明第一个未转换字符的位置。

| 输入 | 返回数值 | `end` 指向 | 本项目判断 |
| --- | ---: | --- | --- |
| `123\n` | 123 | `'\n'` | 合法 |
| `0\n` | 0 | `'\n'` | 合法 |
| `abc\n` | 0 | `'a'`，且 `end == buffer` | 非法 |
| `123abc\n` | 123 | `'a'` | 非法 |
| `123  \n` | 123 | `' '` | 当前规则下非法 |

这解释了为什么不能仅根据 `number == 0` 来判断转换是否失败：用户确实可能输入合法的 `0`。

验证顺序为：

1. `end == buffer`：未解析出任何数字，提示并重试。
2. `*end != '\n' && *end != '\0'`：数字后有剩余非法字符，提示并重试。
3. `errno == ERANGE || number < INT_MIN || number > INT_MAX`：超出 `long` 或 `int` 的可表示范围，提示并重试。
4. 验证通过后写入 `*value`，并 `return 1`，避免落入下一轮无限要求输入。

使用 `<stdlib.h>` 声明 `strtol`，`<errno.h>` 提供 `errno` / `ERANGE`，`<limits.h>` 提供 `INT_MIN` / `INT_MAX`。调用前清零 `errno`，避免旧错误状态影响本次判断。

`readInt` 并没有负责验证“成绩在 `0–100` 之间”：它只确保值是合法可表示的 `int`。业务范围检查留在 `main.c`，这是刻意的职责划分。

### 5.5 `readString()`：直接读取到目标数组

最早的版本使用 `buffer[64]`，再手动将内容复制到目标 `string`。学习中发现两个问题：复制后忘记补 `\0`；更重要的是，目标姓名数组只有 24 字节，复制 40 个字符会越界。

更简洁的方案是直接用：

```c
fgets(string, capacity, stdin);
```

但 `capacity` 必须是目标数组的**真实容量**，不是 `NAME_SIZE + 2`。向 24 字节数组告诉 `fgets`“可以写 26 字节”会造成越界风险；扩容两个字节也不能避免用户输入任意长字符串。

换行清理采用：

```c
char *newLinePos = strchr(string, '\n');
if (newLinePos != NULL) {
    *newLinePos = '\0';
} else {
    /* 再检查 getchar()，必要时 discardLine() 并重试 */
}
```

`strchr()` 找不到换行符时返回 `NULL`，因此解引用之前必须判断。成功时返回 `string`；`fgets` 失败时返回 `NULL`。这也解释了为什么不能看到 `newLinePos == NULL` 就立即宣告“输入过长”。

在 `main.c` 中：

```c
readString("Student name: ", newStudent.name,
           sizeof(newStudent.name));
```

`sizeof(newStudent.name)` 在这个位置是整个**数组对象**的大小，正好与目标容量对应。

**输入规则的明确边界：** 当前字符串读取允许空字符串；当前整数解析允许前导空白、不接受尾随空白。姓名是否允许为空、是否限制字符集等属于业务规则，尚未额外约束。

---

## 6. 主菜单 `case 1`：添加学生的完整集成思路

实际实现流程：

```text
创建临时 newStudent
    ↓ readInt 学号
    ↓ readString 姓名（传真实容量）
    ↓ for 遍历三门成绩
         └─ while 重试当前科目，直到成绩在 0–100
    ↓ addStudent(students, &count, &newStudent)
    ↓ 根据 1 / -1 / 0 显示成功 / 重复 / 已满
```

成绩范围检查是后续集成时**实际发现并补充**的遗漏。最终采用外层 `for`、内层 `while`：

```c
for (int i = 0; i < SUBJECT_COUNT; i++) {
    while (1) {
        int scoreInput;
        printf("Subject %d ", i + 1);
        if (!readInt("Score: ", &scoreInput)) {
            return 0;
        }
        if (scoreInput >= 0 && scoreInput <= 100) {
            newStudent.scores[i] = scoreInput;
            break;
        }
        printf("Invalid score.\n");
    }
}
```

- 外层选科目，内层只重试**当前**科目，不会在 `101`、`-1` 时错误进入下一门。
- 成绩通过规则检查后才写入 `newStudent.scores[i]`。
- `readInt` 处理数字格式；菜单处理成绩业务范围。
- `case 1: { ... }` 给 `newStudent` 等局部变量建立清晰作用域。

本次还讨论了一个可选取舍：当前程序会读取完姓名和成绩后才发现重复学号；这是可以优化的交互体验，但不影响数据正确性，**没有为了这个问题重构已测试通过的函数**。

---

## 7. 查找功能：整数比较与字符串比较

### 7.1 `findById()`

```c
int findById(const struct Student students[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}
```

返回的是**数组下标**，不是学生学号，也不是“找到返回 1”的布尔状态。找到时返回 `i`，未找到时返回 `-1`。

本次实际测试输出：

```text
Search 102:
1
Search 999:
-1
```

`case 3` 先检查 `targetIndex == -1`，再通过 `printStudent(&students[targetIndex])` 显示学生；不能直接访问 `students[-1]`。

### 7.2 `findByName()`

```c
int findByName(const struct Student students[], int count,
               const char name[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(name, students[i].name) == 0) {
            return i;
        }
    }
    return -1;
}
```

- `==` 比较两个字符数组表达式时不会比较字符串内容；这里要使用 `<string.h>` 中的 `strcmp()`。
- `strcmp(a, b) == 0` 表示内容完全相同。
- 默认区分大小写，`Alice` 与 `alice` 不匹配。
- 若有同名学生，只返回**第一个**匹配项。

本次实际测试输出为 `0`、`-1`、`-1`：因为这轮测试数据里 Alice 位于 `students[0]`，所以返回 `0` 是正确下标，不能因为先前示例将 Alice 放在下标 3 就误判测试失败。

`case 4` 使用 `readString()` 读取要查询的姓名，再调用 `findByName()` 和 `printStudent()`；学习者确认集成测试通过。

---

## 8. `calculateStats()`：固定长度数组 + 四个输出指针

函数声明：

```c
void calculateStats(const struct Student *student,
                    int *total, double *average,
                    int *maximum, int *minimum);
```

C 语言函数参数按值传递；这里将四个结果变量的**地址值**传进去，再通过 `*total`、`*average`、`*maximum`、`*minimum` 修改调用者的对象。函数本身无需靠返回值运回四项数据，因此返回类型是 `void`。

### 8.1 总分与平均分

```c
*total = 0;
for (int i = 0; i < SUBJECT_COUNT; i++) {
    *total += student->scores[i];
}
*average = (double)*total / SUBJECT_COUNT;
```

累加前必须初始化 `*total`；强制转换应发生在除法之前，避免整数除法截断小数。

### 8.2 最高分与最低分

```c
*maximum = student->scores[0];
*minimum = student->scores[0];

for (int i = 1; i < SUBJECT_COUNT; i++) {
    if (student->scores[i] > *maximum) {
        *maximum = student->scores[i];
    }
    if (student->scores[i] < *minimum) {
        *minimum = student->scores[i];
    }
}
```

因第一门成绩已作为初值，比较循环从 `i = 1` 开始即可。两个独立 `if` 分别更新最大值和最小值，无需额外抽象。

### 8.3 实际测试与菜单集成

学生 Alice 的成绩 `{95, 98, 100}`：

```text
Total: 293
Average: 97.67
Maximum: 100
Minimum: 95
```

测试结果与预期一致。`case 5` 先根据学号调用 `findById()`；只有找到学生后才调用：

```c
calculateStats(&students[targetIndex],
               &total, &average, &maximum, &minimum);
```

输出时平均分采用 `%.2f`。学习者确认统计功能的菜单集成测试通过。

---

## 9. 测试策略与本次实际完成情况

测试顺序是**先数据函数、再菜单集成**，避免把算法错误与输入交互错误混在一起。

| 阶段 | 实际证据 | 结论 |
| --- | --- | --- |
| 显示 | Mia、Ben、Leo 的三行表格正确 | 基础显示通过 |
| `addStudent` 正常添加 | Alice 完整显示为第四条记录；返回 `1`、`count = 4` | 通过 |
| 重复学号 | Another 返回 `-1`、`count = 4`、Alice 未被覆盖 | 通过 |
| 满容量 | 填满 20 条后再添加返回 `0`；人数和最后一条记录不变 | 通过 |
| 添加菜单与输入 | 学习者报告 GCC 无警告，菜单集成测试通过 | 已由学习者确认 |
| 成绩范围 | 补充 `0 <= score <= 100` 的内层重试循环并完成代码审查 | 逻辑已审查；未收到逐个边界值的独立运行记录 |
| 按 ID 查找 | `102 → 1`、`999 → -1` | 独立测试通过，菜单集成通过 |
| 按姓名查找 | `Alice → 0`、`Unknown → -1`、`alice → -1` | 独立测试通过，菜单集成通过 |
| 四项统计 | `293` / `97.67` / `100` / `95` | 独立测试通过，菜单集成通过 |

**测试表述原则：** “学习者报告集成测试通过”与“本次直接重新拉取最新源码并运行自动化测试”并不相同。本笔记没有假装复测尚未推送到仓库的本地最新实现。

可作为以后回归测试的场景（下列不是宣称已经全部执行）：

- [ ] 依次输入成绩 `-1`、`0`、`100`、`101`，验证两个边界和错误重试。
- [ ] 整数输入 `2abc`、`abc`、超出 `int` 范围的数，以及超过缓冲区长度的一整行。
- [ ] 姓名长度分别为 23 与 24 个字符、空字符串、直接 EOF。
- [ ] 多人同名时确认姓名搜索返回第一个匹配项。
- [ ] 添加失败后再次显示全部记录，确认有效人数和内容均未变化。

---

## 10. 本次真实踩坑与设计判断

| 遇到的问题或争议 | 原因 | 最终处理 |
| --- | --- | --- |
| 添加时只复制 `id` | 忽略结构体内的姓名和成绩数组 | 使用 `students[*count] = *newStudent` 整体复制 |
| `scanf("%d")` 接受 `2abc` 的开头数字 | 转换成功不代表整行合法 | `fgets` 读行，再用 `strtol` 检查转换终点 |
| 遍历字符串时检查 `\0` 的分支不可达 | 循环写了 `i < strlen(buffer)`，不会访问终止符 | 用 `buffer[i] != '\0'` 控制循环；查找失败放循环后处理 |
| `getchar` 清理循环错误检查 `\0` | 混淆字符串结尾与输入流行尾 | 只以 `\n`、`EOF` 作为清理终止条件 |
| `ch == '\n' && ch == EOF` | 同一个值不可能同时满足两个条件 | 按逻辑使用 `||`，或等价地检查 `ch != '\n' && ch != EOF` |
| `discardLine` 被无条件调用 | 会多吃下一行输入，甚至导致程序等待 | 仅明确发现当前行有剩余字符时调用 |
| 没找到 `\n` 就直接判定超长 | 恰好填满数组或 EOF 都可能没有 `\n` | 额外看一次 `getchar()` 才作判断 |
| `strtol()` 后没有清零 `errno` | 旧错误状态可能污染本次检查 | 每次转换前 `errno = 0` |
| `readInt()` 成功赋值后忘记返回 | 外层 `while (1)` 导致继续提示输入 | 成功后写入 `*value` 并 `return 1` |
| `readString()` 手动复制但忘记 `\0` | 目标不是有效的 C 字符串 | 直接读到目标数组，并用 `strchr` 去换行 |
| 想把 `capacity` 传成 `NAME_SIZE + 2` | 误以为参数能扩充实际数组大小 | 只能传目标真实容量，例如 `sizeof(newStudent.name)` |
| 第一次姓名测试得到 `0`，不是示例 `3` | 测试数据里的 Alice 本来就在首位 | 按实际数组位置解释返回下标，不凭示例臆断出错 |
| 成绩格式合法但超过 100 | 输入格式校验与成绩业务规则不同 | 在菜单中对当前科目使用重试循环 |
| 担心“过度防御性编程” | 额外检查与抽象容易使小项目臃肿 | 优先正确性、简洁性、明确函数契约；只为真实问题增加必要处理 |

本次最值得保留的工程原则：**先明确函数职责和返回值，再实现；先完成可观察的功能和必要的测试，最后才考虑是否真的需要封装或重构。**

---

## 11. 当前限制与下一阶段

1. **固定容量：** 学生最多 20 人，每人三门成绩；无动态扩容。
2. **不持久化：** 未实现文件读写，程序退出会丢失当次输入的记录。
3. **姓名规则：** 精确区分大小写，查找同名只返回首项；当前未单独拒绝空姓名。
4. **学号规则：** 添加函数只保证不重复；当前未单独制定学号必须为正的业务规则。
5. **输入函数契约：** `fgets == NULL` 时当前简单接口将 EOF 与读取错误合并成无法继续读取；对于本次终端练习可接受，若以后需求改变再细分状态。
6. **GitHub 同步：** 当前仓库远端代码落后于最近的本地完成进度。后续提交前应先核对 `student.c`、`main.c` 和测试程序的本地最新内容；本次仅生成学习笔记，不擅自覆盖学生代码。
7. **不盲目扩展：** 修改、删除、排序、链表和文件 I/O 留作后续可选内容；SRMS 2.0 作为 Lecture 1–9 阶段性综合练习已经结项。

### 复习自测（先不附答案）

1. 为什么 `students[*count] = *newStudent` 能复制内部数组，而 `students[*count] = newStudent` 不行？
2. `MAX_STUDENTS`、`count`、`SUBJECT_COUNT` 各自控制哪一段循环的上界？
3. 为什么 `scanf("%d")` 返回 `1` 仍不能证明 `2abc` 合法？
4. 为什么 `fgets` 没读到 `\n` 时，不能马上认定输入过长？
5. `\0`、`\n`、`EOF` 三者分别扮演什么角色？
6. 为什么 `readInt()` 把整数写入 `*value`，而不是直接以返回值返回用户输入？
7. 在 `strtol` 转换结束后，`end == buffer` 与 `*end == 'a'` 分别说明什么？
8. 为什么不能把 `NAME_SIZE + 2` 传给一个仅有 `NAME_SIZE` 字节的姓名数组？
9. 为什么 `findByName()` 要用 `strcmp()` 而不能直接用 `==`？
10. 为什么初始化 `*maximum = scores[0]` 后，后面的比较循环可以从 `i = 1` 开始？
11. 如果 `findById()` 返回 `-1`，为什么不能调用 `printStudent(&students[index])`？
12. 为什么同一个数组可以把 `0` 当作合法成绩，却不能凭 `scores[i] == 0` 判断该学生有没有记录？

**阶段总结：** 这次练习真正完成了从“单个函数能运行”到“有稳定接口、分层输入、可独立测试、可集成菜单的小型 C 项目”的转变。保留每次真实错误、边界讨论和测试证据，比给最终代码附上一堆空泛的规范更有复习价值。

**相关资料：** [`student.h`](../../practiceCode/Course9Practice/src/student.h) · [`input.h`](../../practiceCode/Course9Practice/src/input.h) · [`SLSMS_综合实战项目笔记.md`](SLSMS_综合实战项目笔记.md) · [`输入健壮性专题笔记`](../../extracurricularLearning/inputRobustnessInC/Phase1-3Note.md) · [仓库 `AGENTS.md`](../../../AGENTS.md)
