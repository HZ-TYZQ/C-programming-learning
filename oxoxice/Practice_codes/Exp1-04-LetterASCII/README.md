# Exp1-04 大写字母的 ASCII 码与序号

实验 1 第 4 题。

## 题目

从键盘输入一个大写英文字母，输出它对应的 ASCII 码，并计算该字母在 26 个英文字母中的序号。

## 思路

`char` 在内存里存的就是这个字符的编码，把它赋给 `int` 变量就得到 ASCII 码；序号用 `字母 - 'A' + 1` 计算。

## 语言

C++（`src/letter_ascii.cpp`）

## 编译与运行

```bash
mkdir -p builds
g++ src/letter_ascii.cpp -o builds/letter_ascii
./builds/letter_ascii
```

## 运行示例

输入 `D`：

```
请输入一个大写英文字母：D
英文字母D的ASCII码是68,是26个英文字母的第4个字母
```
