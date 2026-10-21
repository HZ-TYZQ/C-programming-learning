# Exp2-05 商品折扣与找零

实验 2 第 5 题。

## 题目

A 商品单价 9.2 元，购买数量 20 个及以上打八折。输入数量，若数量不为负数，算出总金额；再输入付款金额，算出找零。所有输出保留 1 位小数。

## 语言

C++（`src/shop_discount.cpp`）

## 编译与运行

```bash
mkdir -p builds
g++ src/shop_discount.cpp -o builds/shop_discount
./builds/shop_discount
```

## 运行示例

```
请输入A商品数量: 21
商品总金额为154.6
请输入付款金额: 200
找零金额为45.4
```

```
请输入A商品数量: -3
A商品数量输入错误!
```

## 要点

- 数量判断用 `a < 0`（题目是「不为负数」），写成 `a <= 0` 会把 0 件也当成错误。
- 折扣条件是「20 个及以上」，所以用 `a >= 20`；正好 20 个也要打折。
- 保留 1 位小数：`cout << fixed << setprecision(1)`，需要 `#include<iomanip>`。**只写 `setprecision` 不加 `fixed`** 会出现科学计数法或有效数字位数不对。
- 每个 `cout` 结尾都要有 `endl`，否则提示语会和结果挤在同一行。
