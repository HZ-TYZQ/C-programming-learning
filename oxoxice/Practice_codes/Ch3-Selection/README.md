# 第 3 章 选择结构 · 练习

对应教材第 3 章：关系运算符、`if`、`else if`、`switch`、嵌套 `if`、条件运算符 `?:`。

## 题目清单

| 文件 | 题目 | 主要知识点 |
| --- | --- | --- |
| [01-if-pass.cpp](01-if-pass.cpp) | 输入分数，判断及格 / 不及格 | `if` / `else`、关系运算符 |
| [02-bmi-zero-check.cpp](02-bmi-zero-check.cpp) | 给 BMI 程序加"身高不能为 0"的保护 | `if` 拦截非法输入 |
| [03-elseif-grade.cpp](03-elseif-grade.cpp) | 成绩评级 A / B / C / D / F | `else if` 链（**从严到宽**排序） |
| [04-bmi-category.cpp](04-bmi-category.cpp) | BMI 分级：偏瘦 / 正常 / 超重 / 肥胖 | `else if` 区间划分 |
| [05-switch-weekday.cpp](05-switch-weekday.cpp) | 输入 1~7，输出星期几 | `switch` / `case` / `break` / `default` |
| [06-switch-month-days.cpp](06-switch-month-days.cpp) | 输入月份，输出这个月有几天 | `switch` 多个 `case` 共用一段代码 |
| [07-calculator.cpp](07-calculator.cpp) | 简易计算器（四则运算） | `switch` + `case` 内嵌 `if` + 除零检查 + `return 1` |

## 几个容易踩的点

**`else if` 的顺序必须从严到宽。** 如果写成 `if (score >= 60) ... else if (score >= 70) ...`，
那么 95 分会在第一条就命中，被判成 D，后面的分支永远轮不到。

**`switch` 的每个分支末尾都要 `break`。** 漏了会"贯穿"到下一个 `case`，而且不会重新检查条件。

**`case` 后面只能写常量。** 想判断范围（`>= 90`）只能用 `else if`。

**`if` 只保护它花括号里的代码。** 想"拦住"后面的语句，得用 `return` 或者 `else` ——
`02-bmi-zero-check.cpp` 和 `07-calculator.cpp` 里各有一种写法。

## 编译与运行

```bash
mkdir -p builds
g++ 01-if-pass.cpp -o builds/01-if-pass
./builds/01-if-pass
```

Windows + Visual Studio：

```bat
cl /EHsc /utf-8 01-if-pass.cpp
```
