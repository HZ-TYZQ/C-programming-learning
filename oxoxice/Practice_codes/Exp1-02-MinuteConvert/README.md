# Exp1-02 分钟数换算

实验 1 第 2 题。

## 题目

从键盘输入 n 分钟，把它换算成「几小时几分钟」输出。

例如输入 `456`，应输出 `7小时36分钟`。

## 思路

用整除和取余各取一次：`n / 60` 得到整小时数（不足一小时的零头被丢掉），`n % 60` 得到剩下不足一小时的分钟数。

## 语言

C++（`src/minute_convert.cpp`）

## 编译与运行

```bash
mkdir -p builds
g++ src/minute_convert.cpp -o builds/minute_convert
./builds/minute_convert
```
