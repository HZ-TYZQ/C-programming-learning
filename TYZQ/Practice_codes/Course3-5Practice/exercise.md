# 综合练习：Voltage QC System（电压质量检测系统）

**涉及知识：** `if-else`、`switch`、`for`、`do-while`、`break`、`continue`、嵌套循环、函数、格式化输出。

## 题目要求

编写一个 C 语言程序，模拟 3.3V 电源的电压采样与质量检测。

### 1. 菜单系统

程序循环显示菜单，直到用户选择 `0`：

    ===== Voltage QC System =====
    1. Start new test
    2. Show last report
    0. Exit
    Select:

### 2. 电压采样

选择 `1` 后：

- 输入采样数量，要求在 1～20 之间，否则重新输入。
- 逐个读取浮点数电压。
- 输入 `-1` 时提前结束采样。
- 超出 0～5V 的电压视为 INVALID，记录数量，但不参与有效数据统计。

电压分类规则：

| 电压范围                    | 分类    |
| --------------------------- | ------- |
| 0 ≤ V < 3.10                | LOW     |
| 3.10 ≤ V ≤ 3.50             | NORMAL  |
| 3.50 < V ≤ 5.00             | HIGH    |
| V < 0 或 V > 5（不包括 -1） | INVALID |

### 3. 数据统计

统计以下信息：

- 有效与无效样本数量
- LOW、NORMAL、HIGH 数量
- 有效电压的平均值、最小值、最大值
- 检测结果 PASS / WARN

**PASS 条件：**

至少有一个有效样本，且 LOW、HIGH、INVALID 数量全部为 0。

否则输出 WARN。

每次开始新测试时，必须清空上一轮统计数据。

### 4. 测试报告

选择 `2` 显示最近一次测试结果，并用嵌套循环绘制字符统计图。

示例：

    ===== Last Test Report =====
    Valid samples  :      4
    Invalid        :      1
    Low            :      1
    Normal         :      2
    High           :      1
    Average        :   3.26 V
    Minimum        :   2.95 V
    Maximum        :   3.60 V
    Result         : WARN

    LOW     : *
    NORMAL  : **
    HIGH    : *
    INVALID : *

特殊情况：

- 从未开始测试：显示 `No test data available.`
- 已经测试，但没有有效电压：不计算平均值、最大值和最小值，结果为 WARN。

## 练习限制

- 尽量使用本阶段学过的控制结构。
- 字符统计图使用嵌套循环实现。
- 暂时不使用数组。
- 暂不要求处理 `scanf` 的非数字输入错误。

**完成标准：** 能连续测试、正确分类、统计有效数据，并正确处理提前结束和无有效样本的情况。
