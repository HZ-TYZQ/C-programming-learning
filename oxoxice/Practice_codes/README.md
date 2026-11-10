# oxoxice 的 C++ 练习

这里整理 C++ 的练习题。分两种组织方式：

- **实验**：一个题目一个小项目，每个项目有自己的 `src/` 和 `README.md`
- **章节练习**：按章节放在一个目录里，一个 `.cpp` 一道题，按题号命名

## 实验 1

| 项目 | 内容 |
| --- | --- |
| [Exp1-01-BMI](Exp1-01-BMI/) | 输入身高体重，求身体质量指数 BMI |
| [Exp1-02-MinuteConvert](Exp1-02-MinuteConvert/) | 把分钟数换算成几小时几分钟 |
| [Exp1-03-DepositInterest](Exp1-03-DepositInterest/) | 三年期存款到期后的本息和 |
| [Exp1-04-LetterASCII](Exp1-04-LetterASCII/) | 大写英文字母的 ASCII 码与字母序号 |
| [Exp1-05-FineTuneCost](Exp1-05-FineTuneCost/) | 大模型微调算力费用的计算 |

## 实验 2

| 项目 | 内容 |
| --- | --- |
| [Exp2-01-GPUTemp](Exp2-01-GPUTemp/) | 按 85℃ 阈值判断 GPU 温度是否正常 |
| [Exp2-02-TwoNumbers](Exp2-02-TwoNumbers/) | 单分支 `if` 求较小数、条件运算符求较大数 |
| [Exp2-03-LetterCheck](Exp2-03-LetterCheck/) | 判断一个字符是否为英文字母 |
| [Exp2-04-Divisible](Exp2-04-Divisible/) | 判断能否被 4 整除、是否不能被 7 整除 |
| [Exp2-05-ShopDiscount](Exp2-05-ShopDiscount/) | 商品满 20 件打八折，并计算找零 |

## 实验 3

| 项目 | 内容 |
| --- | --- |
| [Exp3-01-VRAMJudge](Exp3-01-VRAMJudge/) | 按显存大小判断可运行的 AI 任务（`if-else` 阶梯） |
| [Exp3-02-TriangleType](Exp3-02-TriangleType/) | 判断三条边能否构成三角形及类型（嵌套 `if`） |
| [Exp3-03-GasTier](Exp3-03-GasTier/) | 阶梯气费计算（分段累加 + `setprecision`） |
| [Exp3-04-SeasonSwitch](Exp3-04-SeasonSwitch/) | 判断月份所属季节（`switch` + case 穿透） |

第 5 题（三天打鱼两天晒网，`switch` + 闰年）还在整理，之后补上。

## 实验 4

| 项目 | 内容 |
| --- | --- |
| [Exp4-01-BinaryToDecimal](Exp4-01-BinaryToDecimal/) | 二进制整数转十进制（`while`） |
| [Exp4-02-ConfidenceStats](Exp4-02-ConfidenceStats/) | AI 推理置信度的平均值与达标次数（`do-while`） |
| [Exp4-03-CongruenceRange](Exp4-03-CongruenceRange/) | 区间内同时满足三个同余条件的整数（`for`） |
| [Exp4-04-ProductionDoubling](Exp4-04-ProductionDoubling/) | 产值翻一番需要的年份（复利迭代） |
| [Exp4-05-SampleConsumption](Exp4-05-SampleConsumption/) | 每天取走一半多 1 条，取完样本需要的天数 |
## 实验 5

| 项目 | 内容 |
| --- | --- |
| [Exp5-01-PrimeFactorization](Exp5-01-PrimeFactorization/) | 合数的质因数分解（单层循环） |
| [Exp5-02-CharTriangle](Exp5-02-CharTriangle/) | 按行数和字符输出右对齐三角形（嵌套循环） |
| [Exp5-03-NineNineTable](Exp5-03-NineNineTable/) | 九九乘法表（右对齐，嵌套循环） |

第 4 题（搬砖问题）和第 5 题（区间回文数）还在整理，之后补上。
## 章节练习

| 目录 | 内容 | 题数 |
| --- | --- | --- |
| [Ch3-Selection](Ch3-Selection/) | 第 3 章 选择结构：`if` / `else if` / `switch` / 嵌套 `if` | 7 |
| [Ch4-Loop](Ch4-Loop/) | 第 4 章 循环结构：`while` / `for` | 6 |
| [Ch5-Function](Ch5-Function/) | 第 5 章 函数：函数定义 / 值传递 / 递归 | 6 |

每个目录的 `README.md` 里列出了题目清单和易错点。

函数这一章的笔记与踩坑记录见 [../Notes/](../Notes/)。


## 期中复习卷

| 目录 | 内容 |
| --- | --- |
| [Review-01-Midterm](Review-01-Midterm/) | 第 1~5 章综合复习卷：快速判断 / 读代码写输出 / 找错并改正 / 编程题，附答案与逐题解析 |
| [Review-02-Midterm](Review-02-Midterm/) | 按期中考纲缺口出题：累和累积 / 数论 / 进制转换 / 枚举 / 图形，共 11 题 |

## 综合练习（作业）

| 目录 | 内容 | 题数 |
| --- | --- | --- |
| [Homework1](Homework1/) | 第 2~4 章综合题：秒数换算、快递运费、阶乘之和 | 3 |

## 编译与运行

源文件是 C++（`.cpp`）。

实验类的项目（以 `Exp1-01-BMI` 为例）：

```bash
cd Exp1-01-BMI
mkdir -p builds
g++ src/bmi.cpp -o builds/bmi
./builds/bmi
```

章节练习（以 `Ch4-Loop` 为例）：

```bash
cd Ch4-Loop
mkdir -p builds
g++ 02-while-sum.cpp -o builds/02-while-sum
./builds/02-while-sum
```

Windows 上用 Visual Studio 的话：

```bat
cl /EHsc /utf-8 src\bmi.cpp
cl /EHsc /utf-8 02-while-sum.cpp
```

编译产物统一放在各自的 `builds/` 目录，该目录已被 Git 忽略。
