# Exp1-05 大模型微调算力费用

实验 1 第 5 题。

## 题目

假设云平台大模型微调算力单价为 2.35 元/小时，从键盘输入微调任务运行的小时数，计算本次微调任务的总费用并输出。

要求：将算力单价定义为**符号常量**，输出总费用保留 2 位小数。

```
总费用 = 单价 × 小时数
```

## 思路

单价用 `const double` 定义成符号常量，这样以后单价调整只改一处；保留 2 位小数用 `#include <iomanip>` 配合 `cout << fixed << setprecision(2);`。

## 语言

C++（`src/fine_tune_cost.cpp`）

## 编译与运行

```bash
mkdir -p builds
g++ src/fine_tune_cost.cpp -o builds/fine_tune_cost
./builds/fine_tune_cost
```

## 运行示例

输入小时数 `3.5`：

```
请输入微调运行的小时数：3.5
微调总费用为；8.22元
```
