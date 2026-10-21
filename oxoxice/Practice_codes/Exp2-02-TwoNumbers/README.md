# Exp2-02 两数比较

实验 2 第 2 题。

## 题目

输入 2 个整数，使用 `if` 单分支结构求较小的数；使用条件运算符求较大的数。

## 语言

C++（`src/two_numbers.cpp`）

## 编译与运行

```bash
mkdir -p builds
g++ src/two_numbers.cpp -o builds/two_numbers
./builds/two_numbers
```

## 运行示例

```
请输入两个整数:33 16
较小数为：16
较大数为：33
```

## 要点

- 较小数用**单分支 `if`**：先假设 `a` 最小，再检查 `b` 是否更小。
- 较大数用**条件运算符**：`a > b ? a : b`，读作「a 大于 b 吗？是就取 a，否则取 b」。
  `if` 是语句、没有值；`?:` 是表达式、有值，所以能直接放在赋值号右边。
- 注意：变量名 `min` / `max` 会和 `std::min` / `std::max` 同名，更稳妥的写法是 `minVal` / `maxVal`。
