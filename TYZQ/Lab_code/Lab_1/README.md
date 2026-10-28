# 实验 1（Lab 1）· UESTCHN1005

三位数的位运算与阿姆斯特朗数（Armstrong number）判断。
练习 A / B / C 与检查点 4 / 5 / 6 的全部源码都在 `src/` 下，编译产物放在 `builds/`（已被 Git 忽略）。

## 目录结构

```
Lab_1/
├── src/
│   ├── digit_analyzer.c              练习 A：三位数拆位分析
│   ├── if_validation.c               检查点 4：if-else 区间校验
│   ├── switch_menu.c                 检查点 5：switch 菜单
│   ├── while_validation.c            检查点 6：while 循环校验
│   └── armstrong/
│       ├── armstrong.h               函数声明
│       ├── armstrong_checker.c       练习 B：判断单个三位数
│       ├── test_armstrong_checker.c  练习 B 单元测试（7 个用例）
│       └── armstrong_explorer.c      练习 C：枚举 100 ~ 上限之间的阿姆斯特朗数
└── builds/                           编译产物（Git 忽略）
```

## 文件清单

| 文件 | 练习 | 主要知识点 |
| --- | --- | --- |
| [src/digit_analyzer.c](src/digit_analyzer.c) | A | `/` 与 `%` 拆出百位、十位、个位；逆序数拼接；`digit_sum / 3.0` 得到浮点平均值 |
| [src/armstrong/armstrong_checker.c](src/armstrong/armstrong_checker.c) | B | 三位数的立方和与原数比较，返回「是 / 否」 |
| [src/armstrong/test_armstrong_checker.c](src/armstrong/test_armstrong_checker.c) | B | 给定输入与期望值比对，7 个用例全过返回 0，否则返回 1 |
| [src/armstrong/armstrong_explorer.c](src/armstrong/armstrong_explorer.c) | C | `while` 反复读入直到合法；`for` 遍历 100 ~ 上限并调用 checker；计数器 + 空结果提示 |
| [src/if_validation.c](src/if_validation.c) | 检查点 4 | `if` / `else if` / `else` 三路分支 |
| [src/switch_menu.c](src/switch_menu.c) | 检查点 5 | `switch` / `case` / `break` / `default`；`scanf(" %c")` 前导空格吃掉换行 |
| [src/while_validation.c](src/while_validation.c) | 检查点 6 | 用 `while` + 逻辑或 `||` 拦住非法输入 |

## 编译与运行

下面的命令都在 `Lab_1/` 目录下执行。

单独的程序：

```bash
mkdir -p builds

gcc -std=c11 -Wall -Wextra -Wpedantic src/digit_analyzer.c    -o builds/digit_analyzer
gcc -std=c11 -Wall -Wextra -Wpedantic src/if_validation.c     -o builds/if_validation
gcc -std=c11 -Wall -Wextra -Wpedantic src/switch_menu.c       -o builds/switch_menu
gcc -std=c11 -Wall -Wextra -Wpedantic src/while_validation.c  -o builds/while_validation

./builds/digit_analyzer
```

`armstrong/` 下的两个程序都依赖 `armstrong_checker.c`，要把 checker 一起传给 `gcc`：

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic \
    src/armstrong/armstrong_checker.c src/armstrong/test_armstrong_checker.c \
    -o builds/test_armstrong

gcc -std=c11 -Wall -Wextra -Wpedantic \
    src/armstrong/armstrong_checker.c src/armstrong/armstrong_explorer.c \
    -o builds/explorer

./builds/test_armstrong
./builds/explorer
```

Windows + Visual Studio：

```bat
cl /W4 /utf-8 src\digit_analyzer.c
```

## 运行示例

`digit_analyzer`，输入 `472`：

```
Enter a three-digit number: 472
Hundreds digit: 4
Tens digit: 7
Ones digit: 2
Sum of digits: 13
Product of digits: 56
Reversed number: 274
Average digit value: 4.33
```

`test_armstrong_checker`：

```
Test 1: 100 -> PASS
Test 2: 153 -> PASS
Test 3: 352 -> PASS
Test 4: 370 -> PASS
Test 5: 371 -> PASS
Test 6: 407 -> PASS
Test 7: 999 -> PASS
All 7 tests passed.
```

`armstrong_explorer`，输入 `500`：

```
=== Armstrong Number Explorer ===
Enter a three-digit upper limit: 500

Armstrong numbers from 100 to 500:
153
370
371
407
Total found: 4
```

输入非法值（如 `99`）会先报错再重新询问：

```
Invalid input: enter a number from 100 to 999.
Enter a three-digit upper limit: 
```

## 几个容易踩的点

**三位数阿姆斯特朗数只有 4 个：153、370、371、407。** 上限给到 999 时结果也还是这 4 个，
不是程序漏了，是 3 位数里就这些。

**`digit_sum / 3.0` 里的 `3` 必须写成 `3.0`。** 写成 `3` 会走整数除法，`472` 的平均值会算成 `4` 而不是 `4.33`。

**`armstrong.h` 里的函数声明要两个 `.c` 都能看到。** 编译时如果只传 `armstrong_explorer.c`，
会得到 `undefined reference to is_armstrong_number` —— checker 的源码必须一起编译。

**`scanf(" %c", &choice)` 前面的空格不能删。** 删掉的话上一次输入留在缓冲区里的换行符会被
`%c` 直接读走，菜单看起来像是"没等你输入就跳到 default"。
