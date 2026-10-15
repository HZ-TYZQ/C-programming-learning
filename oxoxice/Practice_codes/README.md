# oxoxice 的 C++ 练习

这里按「一个小项目一个目录」的方式整理练习题。每个项目都有自己的 `src/` 和 `README.md`。

## 实验 1

| 项目 | 内容 |
| --- | --- |
| [Exp1-01-BMI](Exp1-01-BMI/) | 输入身高体重，求身体质量指数 BMI |
| [Exp1-02-MinuteConvert](Exp1-02-MinuteConvert/) | 把分钟数换算成几小时几分钟 |
| [Exp1-03-DepositInterest](Exp1-03-DepositInterest/) | 三年期存款到期后的本息和 |
| [Exp1-04-LetterASCII](Exp1-04-LetterASCII/) | 大写英文字母的 ASCII 码与字母序号 |
| [Exp1-05-FineTuneCost](Exp1-05-FineTuneCost/) | 大模型微调算力费用的计算 |

## 编译与运行

源文件是 C++（`.cpp`）。以 `Exp1-01-BMI` 为例：

```bash
cd Exp1-01-BMI
mkdir -p builds
g++ src/bmi.cpp -o builds/bmi
./builds/bmi
```

Windows 上用 Visual Studio 的话：

```bat
cl /EHsc /utf-8 src\bmi.cpp
```

各项目的 README 里写了对应的源文件名。编译产物统一放在各项目的 `builds/` 目录，该目录已被 Git 忽略。
