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

## 章节练习

| 目录 | 内容 | 题数 |
| --- | --- | --- |
| [Ch3-Selection](Ch3-Selection/) | 第 3 章 选择结构：`if` / `else if` / `switch` / 嵌套 `if` | 7 |
| [Ch4-Loop](Ch4-Loop/) | 第 4 章 循环结构：`while` / `for` | 6 |

每个目录的 `README.md` 里列出了题目清单和易错点。

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
