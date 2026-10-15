# Exp1-03 三年期存款本息和

实验 1 第 3 题。

## 题目

假设三年期存款年利率为 1.55%，输入存款本金，计算三年期存款到期后的本息和，输出时本息和保留 2 位小数。

## 思路

「三年期存款」按**单利**计算，到期一次还本付息：

```
本息和 = 本金 × (1 + 年利率 × 年数)
```

保留 2 位小数用 `#include <iomanip>` 配合 `cout << fixed << setprecision(2);`。

## 语言

C++（`src/deposit_interest.cpp`）

## 编译与运行

```bash
mkdir -p builds
g++ src/deposit_interest.cpp -o builds/deposit_interest
./builds/deposit_interest
```

## 运行示例

输入本金 `1000.5`：

```
请输入存款本金（元）：1000.5
三年后存款的本息和为：1047.02元
```
