# Lab 2 学习笔记：Mini Grayscale Image Processor

> **课程：** UESTCHN1005 — Introductory Programming · 2026–2027 S1  
> **材料：** 官方 *Lab 2 Learning Guide* 与 *Lab 2 Exercise Sheet*，结合本人编写与测试过程整理  
> **环境：** Linux（CachyOS）+ GCC  
> **完成状态：** Exercise A–D 官方本地测试均 `PASS`；Exercise E 完整程序已通过 CodeGrade  
> **关联知识：** Lecture 6–8（函数、数组、二维数组、指针）与多文件编译／链接
>
> **说明：** 本笔记中的代码是根据 Lab 2 实现过程整理的**复习示例**，不是直接导出的 CodeGrade 提交快照；实际提交文件以本地最终版为准。官方要求与额外的 Linux / C 语言补充知识会在相应小节注明。

---

## 0. 学习目标与整体流程【官方 Learning Guide】

本 Lab 用整数数组模拟一张灰度图像，先分别实现处理函数，最后在 `main.c` 中组装：

```text
       image1 ──┐
                ├── blend_images() ──> blended
       image2 ──┘                         │
                                         ▼
                                 adjust_brightness()
                                         │
                                         ▼
                                     brightened
                                         │
                                         ▼
                      rotate_clockwise() / rotate_counterclockwise()
                                         │
                                         ▼
                                      rotated
                                         │
                                         ▼
                                   print_image()
```

| 阶段 | 文件 | 本次掌握的重点 | 结果 |
| --- | --- | --- | --- |
| Check Point 1 | `check_points/01_brightest_pixel.c` | 一维数组遍历、最大值及首次出现的下标 | 预测与算法正确 |
| A | `print_image.c` | 二维数组遍历、严格控制输出空格 | 本地 `PASS` |
| Check Point 2 | `check_points/02_parameter_changes.c` | 标量值传递与数组形参的区别 | 预测正确 |
| B | `image_blend.c` | 双图像逐像素整数平均值 | 本地 `PASS` |
| C | `brightness.c` | 亮度调整与 clamping | 本地 `PASS` |
| Check Point 3 | 纸面推导 | 90° 旋转的坐标映射 | 掌握推导 |
| D | `rotate.c` | 顺时针／逆时针坐标映射 | 本地 `PASS` |
| E | `main.c` | 输入验证顺序、流水线调用、多文件链接 | CodeGrade 通过 |

---

## 1. Image Representation — 图像如何变成数组【Learning Guide §1–2】

### 1.1 Grayscale pixel（灰度像素）

一个灰度像素使用整数表示，题目规定有效范围为 `0–255`：

- `0` 表示黑色；
- `255` 表示白色；
- 中间的数值表示不同程度的灰色。

一张 `2 × 3` 的图像可以用二维数组表示：

```c
int image[2][3] = {
    {10, 20, 30},
    {40, 50, 60}
};

// image[0][0] == 10
// image[1][2] == 60
```

第一个下标 `row` 选行，第二个下标 `col` 选列；二者都从 `0` 开始。

### 1.2 Row-major order（按行连续存放）

C 的二维数组本质上是「由多个一维行数组组成的数组」，内存顺序是：

```text
第 0 行：10  20  30 | 第 1 行：40  50  60
```

本 Lab 的公共头文件 `image.h` 定义了：

```c
#define MAX_SIZE 20
```

因此：

```c
int image[MAX_SIZE][MAX_SIZE];
```

**注意容量与有效尺寸的区别：**

- `MAX_SIZE = 20` 是物理数组的**最大行数、每行容量**；
- `rows`、`cols` 或 `size` 是当前图像实际需要处理的**有效区域**；
- 即使有效图像只有 `2 × 2`，声明为 `image[20][20]` 的数组，每一行仍然占有 20 个 `int` 的位置；
- 对于这种声明，`image[row][col]` 的线性元素偏移是 `row * MAX_SIZE + col`，而不是 `row * cols + col`。

所以处理有效像素时，应使用：

```c
for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
        // 只访问有效区域
    }
}
```

不要为了遍历有效像素就写成 `row < MAX_SIZE` 或 `col < MAX_SIZE`。

### 1.3 Check Point 1：寻找最亮像素

给定一维数组 `pixels`，保留当前最大值与对应下标：

```c
int pixels[5] = {40, 210, 80, 255, 120};
int brightest = pixels[0];
int brightest_index = 0;

for (int i = 0; i < 5; i++) {
    if (pixels[i] > brightest) {
        brightest = pixels[i];
        brightest_index = i;
    }
}
```

输出应为最亮值 `255`、下标 `3`。使用严格大于 `>` 而不是 `>=`，可以在最大值重复出现时**保留第一次出现的位置**。

---

## 2. Exercise A — Print an Image【Exercise Sheet A】

### 2.1 函数目标

```c
void print_image(const int image[][MAX_SIZE], int rows, int cols);
```

- 每行的像素按顺序输出；
- 相邻数字之间**恰好一个空格**；
- 每行行首、行尾**没有空格**；
- 每行末尾都输出一个 `\n`，**最后一行也一样**；
- 不输出标题、输入提示或额外空行；
- 不修改 `image`。

### 2.2 本次采用的实现思路

与其在每个数字后面加空格，不如给**第二列及之后的数字**加前导空格：

```c
void print_image(const int image[][MAX_SIZE], int rows, int cols)
{
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (col == 0) {
                printf("%d", image[row][col]);
            } else {
                printf(" %d", image[row][col]);
            }
        }
        printf("\n");
    }
}
```

对于 `2 × 3` 图像，准确输出：

```text
10 20 30
40 50 60
```

**踩坑记录：** 初次写函数时把 `print_image` 拼成了 `frint_image`。C 语言不会自动匹配近似函数名；函数定义要与 `image.h` 中的声明完全一致，否则调用处可能在链接阶段报 `undefined reference`。

---

## 3. Passing Scalars and Arrays to Functions【Learning Guide §2.3】

### 3.1 C 语言参数始终是按值传递（Pass by Value）

Check Point 2 的核心：

```c
void change_values(int value, int image[][MAX_SIZE])
{
    value = 0;
    image[0][0] = value;
}

int number = 10;
int image[MAX_SIZE][MAX_SIZE] = {{10}};
change_values(number, image);
```

最终：

```text
number: 10
image[0][0]: 0
```

解释：

- `int value` 是普通整数的局部副本，因此修改 `value` 不影响外部的 `number`；
- `int image[][MAX_SIZE]` 在函数形参中会调整为指向**首行数组**的指针：`int (*image)[MAX_SIZE]`；
- 传给函数的仍然是一个**地址值的副本**，但它指向调用者的原数组，因此 `image[0][0] = 0` 会修改原数组元素。

不能说 C 真正拥有另一套“按引用传递”语法：底层仍是按值传递指针。

### 3.2 为什么二维数组形参必须写第二维？

```c
void f(int image[][MAX_SIZE], int rows, int cols);
```

等价于接收：

```c
void f(int (*image)[MAX_SIZE], int rows, int cols);
```

编译器需要知道**每一行含多少个 `int`**，才能计算下一行的起始地址。因此第二维不能省略。

**额外辨析：** `int a[2][3]` 不能直接当作 `int image[][20]` 的实参，因为行类型不同；这不只是元素总数是否足够的问题。

### 3.3 `const` 输入与非 `const` 输出

```c
void blend_images(const int image1[][MAX_SIZE],
                  const int image2[][MAX_SIZE],
                  int output[][MAX_SIZE],
                  int rows, int cols);
```

- `const image1`、`const image2`：不可通过这两个参数修改输入像素；
- `output`：可写的目标数组，结果放这里；
- `void`：函数本身不返回一个图像值，结果通过 `output` 参数传回调用者可见的数组。

---

## 4. Exercise B — Blend Two Images【Exercise Sheet B】

对有效区域的每个坐标，计算两张输入图像的**整数平均值**：

\[
\operatorname{out}[r][c]=\left\lfloor\frac{\operatorname{image1}[r][c]+\operatorname{image2}[r][c]}{2}\right\rfloor
\]

```c
for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
        output[row][col] =
            (image1[row][col] + image2[row][col]) / 2;
    }
}
```

例如 `(20 + 41) / 2 == 30`，因为这里使用的是整数除法，舍弃小数部分。

**边界与不变量：** 输入像素均为 `0–255`，所以两者相加最多为 `510`；不必担心本 Lab 中的 `int` 加法溢出。只写入有效区域，输入数组、输出数组的非有效区域都不应被修改。

---

## 5. Exercise C — Adjust Brightness【Learning Guide §3 / Exercise Sheet C】

### 5.1 Clamping（范围截断）

原像素 `pixel` 加上 `change` 后，必须仍在 `0–255` 范围：

\[
\operatorname{clamp}(x)=
\begin{cases}
0,&x<0\\
x,&0\le x\le255\\
255,&x>255
\end{cases}
\]

实例：

| 原像素 | `change` | 计算值 | 最终像素 |
| ---: | ---: | ---: | ---: |
| 100 | +30 | 130 | 130 |
| 240 | +30 | 270 | 255 |
| 10 | -30 | -20 | 0 |
| 200 | -30 | 170 | 170 |

### 5.2 核心实现

```c
for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
        int value = input[row][col] + change;

        if (value > 255) {
            output[row][col] = 255;
        } else if (value < 0) {
            output[row][col] = 0;
        } else {
            output[row][col] = value;
        }
    }
}
```

本次一开始直接重复写三次 `input[row][col] + change`，逻辑也正确；抽取为局部变量 `value` 只是改善可读性。

---

## 6. Exercise D — Rotate an Image【Learning Guide §4.1 / Exercise Sheet D】

这是本 Lab 最值得掌握的数学部分：**旋转改变的是像素位置，不是像素值。**

### 6.1 从“转置 + 镜像”推导

对边长为 `n` 的**正方形**图像，合法下标为 `0` 到 `n - 1`。

两个基础变换：

1. **Transpose（转置）：** `(r, c) → (c, r)`，交换行列号；
2. **Index reversal（下标反转）：** `x → n - 1 - x`，例如 `0,1,2` 反转为 `2,1,0`。

#### 顺时针 90° = 转置 + 左右翻转

```text
(r, c)  --转置-->  (c, r)  --左右翻转列号-->  (c, n-1-r)
```

即：

\[
\boxed{(r,c)\to(c,n-1-r)}
\]

#### 逆时针 90° = 转置 + 上下翻转

```text
(r, c)  --转置-->  (c, r)  --上下翻转行号-->  (n-1-c, r)
```

即：

\[
\boxed{(r,c)\to(n-1-c,r)}
\]

手算示例：`n = 4`，原坐标 `(1, 2)` 顺时针旋转：

```text
(1, 2) → (2, 1) → (2, 4 - 1 - 1) = (2, 2)
```

### 6.2 一个关键陷阱：赋值方向与公式方向

以上推导的是 **原图坐标 → 输出图坐标**，可以写：

```c
// 顺时针：从输入像素出发，寻找输出位置
output[col][n - 1 - row] = input[row][col];

// 逆时针：从输入像素出发，寻找输出位置
output[n - 1 - col][row] = input[row][col];
```

但自己最初采用的语句形式是：

```c
output[row][col] = input[...][...];
```

这里 `row, col` 已经是**输出坐标**，需要把映射反过来，寻找输入源坐标：

| 旋转方向 | 从输入出发（Source → Destination） | 从输出出发（Destination ← Source） |
| --- | --- | --- |
| 顺时针 | `output[c][n-1-r] = input[r][c]` | `output[r][c] = input[n-1-c][r]` |
| 逆时针 | `output[n-1-c][r] = input[r][c]` | `output[r][c] = input[c][n-1-r]` |

**最初的错误：** 将“输入坐标 → 输出坐标”推导出的公式直接塞进 `input[...]`，导致顺、逆时针写反。改正后两函数通过了官方测试。

### 6.3 本次最终采用的实现方式

```c
void rotate_clockwise(const int input[][MAX_SIZE],
                      int output[][MAX_SIZE], int n)
{
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            output[row][col] = input[n - col - 1][row];
        }
    }
}

void rotate_counterclockwise(const int input[][MAX_SIZE],
                             int output[][MAX_SIZE], int n)
{
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            output[row][col] = input[col][n - row - 1];
        }
    }
}
```

用这张图检查方向：

```text
输入：          顺时针：         逆时针：
1 2 3          7 4 1           3 6 9
4 5 6   -->    8 5 2     或    2 5 8
7 8 9          9 6 3           1 4 7
```

旋转采用**不同的输入／输出数组**，不能在此算法中让输入输出指向同一张图像，否则可能覆盖还没读取的像素。

---

## 7. Separate Source Files — 多文件编译与链接【Learning Guide §4.2】

### 7.1 头文件、源文件、链接器各负责什么？

```text
image.h           函数原型 + MAX_SIZE
   │
   ├── print_image.c
   ├── image_blend.c
   ├── brightness.c
   ├── rotate.c
   └── main.c
          │
          ▼
       编译 + 链接
          │
          ▼
     image_processor
```

- **Declaration（声明）：** 告诉编译器函数接口是什么，例如 `image.h` 中的函数原型；
- **Definition（定义）：** 提供真正的函数体，位于各 `.c` 文件；
- **Compilation（编译）：** 将每个源文件转换为目标文件；
- **Linking（链接）：** 将各目标文件中的符号引用与定义匹配，生成可执行程序。

例如，测试程序调用 `print_image()`，如果只链接 `test_print_image.c`，没有链接 `print_image.c`，可能报：

```text
undefined reference to `print_image'
```

并不是必须“同时编译”，而是**最终链接时必须具有所调用函数的实现**。也可以先分别 `gcc -c ...` 得到 `.o` 文件，再一起链接。

### 7.2 Linux / GCC 编译命令

```bash
# Exercise A：若严格 C11 下测试代码使用 POSIX 接口，添加特性测试宏以暴露声明
gcc -std=c11 -Wall -Wextra -D_POSIX_C_SOURCE=200809L \
    test_print_image.c print_image.c -o test_print_image
./test_print_image

# Exercise B
gcc -std=c11 -Wall -Wextra test_blend.c image_blend.c -o test_blend
./test_blend

# Exercise C
gcc -std=c11 -Wall -Wextra test_brightness.c brightness.c -o test_brightness
./test_brightness

# Exercise D
gcc -std=c11 -Wall -Wextra test_rotate.c rotate.c -o test_rotate
./test_rotate

# Exercise E：仅链接应用的五个源文件，不要把 test_*.c 加进来
gcc -std=c11 -Wall -Wextra \
    main.c print_image.c image_blend.c brightness.c rotate.c \
    -o image_processor
./image_processor
```

| 选项／符号 | 作用 |
| --- | --- |
| `gcc` | 调用 GCC 编译驱动程序 |
| `-std=c11` | 采用 C11 语言标准 |
| `-Wall` | 开启一组常用警告（并非字面上的全部警告） |
| `-Wextra` | 开启额外的常用警告 |
| `-D_POSIX_C_SOURCE=200809L` | 定义 POSIX 特性测试宏；此处用于测试辅助代码的接口声明兼容性，**不是算法必需** |
| `-o name` | 指定生成的可执行文件名 |
| `\` | Shell 中续行符，让一条命令分成多行编写 |
| `./program` | 执行当前目录下的程序 |

### 7.3 Shell 的管道和标准输入【Linux 实操拓展】

```bash
printf '2 10 1\n10 20\n30 40\n50 60\n70 80\n' | ./image_processor
```

左侧 Shell `printf` 把文本写入 `stdout`，管道 `|` 将其连接到右侧程序的 `stdin`。因此程序内的 `scanf()` 能直接读取这些数据，无须改 C 代码。

另一个写法：

```bash
printf '2 10 1\n10 20\n30 40\n50 60\n70 80\n' > input.txt
./image_processor < input.txt
```

`>` 将输出保存为文件；`<` 将文件内容作为标准输入。

---

## 8. Exercise E — Build the Main Program【Exercise Sheet E】

### 8.1 官方明确规定的执行顺序

**不要只关注最终的输出字符串；读取时机也是规格的一部分。**

```text
① 读取 size、change、direction
         │
         ▼
② 立即检查这三个参数是否合法
   ├── 不合法：输出 "Invalid image input.\n" 并退出，不读取任何像素
   └── 合法：继续
         │
         ▼
③ 完整读取第一张图像
         │
         ▼
④ 完整读取第二张图像
         │
         ▼
⑤ 检查两张图像中所有像素是否位于 0–255
   ├── 有非法像素：输出 "Invalid image input.\n" 并退出
   └── 都合法：继续
         │
         ▼
⑥ blend_images → adjust_brightness → rotate → print_image
```

合法性要求：

| 参数 | 范围／要求 |
| --- | --- |
| `size` | `1 <= size <= MAX_SIZE`（本 Lab 为 20） |
| `change` | `-255 <= change <= 255` |
| `direction` | `1`（顺时针）或 `-1`（逆时针） |
| 每个像素 | `0 <= pixel <= 255` |

**注意：** 上述“先读取两张完整图像，再检查像素范围”是官方 Exercise E 的明确要求，不是可随意改变的实现风格。

### 8.2 参数验证：`&&` 与 `||`

最初误写为：

```c
// 错误：这个条件永远为真
direction != 1 || direction != -1
```

应当写成：

```c
// 只有既不等于 1，也不等于 -1 时才无效
(direction != 1 && direction != -1)
```

采用短路求值，一并检查 `scanf()` 是否读入三个整数：

```c
if (scanf("%d %d %d", &size, &change, &direction) != 3 ||
    size < 1 || size > MAX_SIZE ||
    change < -255 || change > 255 ||
    (direction != 1 && direction != -1)) {
    printf("Invalid image input.\n");
    return 0;
}
```

- `&&` 优先级高于 `||`，但加括号更容易读；
- `scanf()` 成功赋值项数不是 `3` 时，`||` 右侧不会继续访问可能尚未初始化的变量；
- 对无法解析为整数的输入进行失败检查属于代码健壮性补充。

### 8.3 本次 CodeGrade 踩坑：提前验证像素导致 FAIL

最早的代码把读入和范围检查写在同一个循环里：

```c
// 这种写法虽能发现非法像素，却违反本题读取顺序的要求
if (scanf("%d", &image1[row][col]) != 1 ||
    image1[row][col] < 0 || image1[row][col] > 255) {
    printf("Invalid image input.\n");
    return 0;
}
```

当第一张图像出现 `-1` 时，程序立即退出，**第二张图像尚未读取**。CodeGrade 给出了关键反馈：

```text
FAIL [first image: pixel -1; read both images before error]
program printed output or exited before image 2 was supplied
```

这里的重点不是错误信息是否正确，而是**程序过早退出**。即使：

```text
Expected: 'Invalid image input.\n'
Actual:   'Invalid image input.\n'
```

两者相同，也不能证明输入交互时序满足要求。测试可能在程序运行过程中逐步提供第二张图像，以验证程序是否提前结束。

**修改方式：** 前两轮循环只读入整数；两张图像读完后，再统一检查有效区域像素范围。

```c
// 先完整读取 image1
for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
        if (scanf("%d", &image1[row][col]) != 1) {
            printf("Invalid image input.\n");
            return 0;
        }
    }
}

// 再完整读取 image2
for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
        if (scanf("%d", &image2[row][col]) != 1) {
            printf("Invalid image input.\n");
            return 0;
        }
    }
}

// 两张图像都读完，才统一验证像素范围
for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
        if (image1[row][col] < 0 || image1[row][col] > 255 ||
            image2[row][col] < 0 || image2[row][col] > 255) {
            printf("Invalid image input.\n");
            return 0;
        }
    }
}
```

补充：如果 `scanf()` 无法正常读取指定整数，上述代码会提前按错误输入退出；这和“完整读入后再检查**像素数值范围**”是不同层面的问题。

### 8.4 复用 A–D 的函数组成流水线

```c
int blended[MAX_SIZE][MAX_SIZE];
int brightened[MAX_SIZE][MAX_SIZE];
int rotated[MAX_SIZE][MAX_SIZE];

blend_images(image1, image2, blended, size, size);
adjust_brightness(blended, brightened, size, size, change);

if (direction == 1) {
    rotate_clockwise(brightened, rotated, size);
} else {
    rotate_counterclockwise(brightened, rotated, size);
}

print_image(rotated, size, size);
return 0;
```

- 调整亮度的对象是 `blended`，**不是** `image1` 或 `image2`；
- 每个阶段读取上一步输出，并写入一个独立的下一阶段数组；
- 旋转方向由已经验证过的 `direction` 决定；
- 最后不能忘记 `print_image()`；
- 错误输出必须**严格**为 `Invalid image input.\n`，不得改成 `Invalid input.\n`。

---

## 9. 测试记录与边界检查

### 9.1 本次通过的测试

- Exercise A — `test_print_image`：`PASS`
- Exercise B — `test_blend`：`PASS`
- Exercise C — `test_brightness`：`PASS`
- Exercise D — `test_rotate`：`PASS`
- Exercise E — 修正“读完两张图后再检查像素”的顺序，CodeGrade 通过

### 9.2 官方样例：两张 2×2 图像

输入：

```text
2 10 1
10 20
30 40
50 60
70 80
```

计算过程：

```text
image1:     image2:     blended:     brightened (+10):
10 20       50 60       30 40        40 50
30 40       70 80       50 60        60 70
```

顺时针（`direction = 1`）输出：

```text
60 40
70 50
```

只把 `direction` 改成 `-1`，逆时针输出：

```text
50 70
40 60
```

用 Shell 管道快速运行：

```bash
printf '2 10 1\n10 20\n30 40\n50 60\n70 80\n' | ./image_processor
printf '2 10 -1\n10 20\n30 40\n50 60\n70 80\n' | ./image_processor
```

### 9.3 需要特别关注的边界输入

```bash
# 非法 size：必须在读取任何像素之前拒绝
printf '0 0 1\n' | ./image_processor
printf '21 0 1\n' | ./image_processor

# 第一张图像出现非法像素：按照官方顺序仍需先读取第二张图像
printf '1 0 1\n-1\n60\n' | ./image_processor

# 第二张图像出现非法像素
printf '1 0 1\n100\n256\n' | ./image_processor

# 亮度截断：255 + 20 应保持 255
printf '1 20 1\n255\n255\n' | ./image_processor

# 亮度截断：0 - 20 应保持 0
printf '1 -20 -1\n0\n0\n' | ./image_processor
```

上述非法输入的最终输出均应为：

```text
Invalid image input.
```

**重要限制：** 普通管道测试能检查最终输出，却**不一定能检查程序何时开始输出或退出**；本次 CodeGrade 的失败正说明这类输入时序也需要验证。

---

## 10. 最终提交清单【Exercise Sheet E】

提交到 **Exercise E CodeGrade** 的只有以下五个 `.c` 文件：

1. `main.c`
2. `print_image.c`
3. `image_blend.c`
4. `brightness.c`
5. `rotate.c`

不要提交：`image.h`（也不要修改）、`test_*.c`、Check Point 文件、可执行程序、`.o` 文件。

A–D 的函数不需要分别提交 CodeGrade；它们由 E 一起集成提交。

---

## 11. 本次个人 Debugging Log（错误 → 原因 → 经验）

| 出现过的问题 | 真正原因 | 记住的规则 |
| --- | --- | --- |
| `frint_image` | 函数名拼写不匹配头文件接口 | 声明与定义必须严格一致 |
| 读取图像时用 `MAX_SIZE` | 把物理容量当成实际图像尺寸 | 数组容量 ≠ 有效区域 |
| `direction != 1 \|\| direction != -1` | 两个不等式总有一个为真 | “既不 A 也不 B”要用 `&&` |
| 顺、逆时针旋转初版写反 | 把 Source→Destination 的公式放进 Destination←Source 形式 | 先明确赋值语句的坐标方向 |
| 缺少最后的 `print_image` | 处理完成却没有输出 | 主程序要完成整条 pipeline |
| 第一张图像发现 `-1` 就立即退出 | 未完整读取第二张图像，违背官方交互时序 | 需求中的“先……再……”是可测试的规格 |

## 12. 复习时应能独立回答的问题

1. `int image[MAX_SIZE][MAX_SIZE]` 中的 `MAX_SIZE` 与函数参数 `rows/cols` 有什么区别？
2. 为什么二维数组函数形参可以省略第一维，却不能省略第二维？
3. 为什么 `change_values(number, image)` 后 `number == 10`，但 `image[0][0] == 0`？
4. 怎样保证 `print_image()` 不输出行首／行尾多余空格？
5. 为什么 `(20 + 41) / 2` 的结果是 `30`，不是 `30.5`？
6. `clamping` 处理过亮与过暗像素的具体条件是什么？
7. 不看笔记，能否用“转置 + 镜像翻转”推导两个 90° 旋转公式？
8. `output[r][c] = input[...][...]` 与 `output[...][...] = input[r][c]` 为什么需要不同的下标表达式？
9. 头文件中的函数声明和 `.c` 文件中的函数定义分别有什么作用？`undefined reference` 属于什么阶段的错误？
10. 为什么第一张图像出现 `-1` 时立即输出错误，仍然会被 Exercise E 的测试判错？

**本 Lab 的最大收获：** 不只是学会操作二维数组，而是把**内存布局、函数接口、代数坐标变换、程序输入协议和多文件链接**放在一条完整的处理流水线中理解。

---

### 来源与范围

- **课程来源：** UESTCHN1005 2026–2027 S1 *Lab 2 Learning Guide* 与 *Lab 2 Exercise Sheet*（本笔记保留其 A–E 顺序与规范）。
- **学习过程来源：** 本次 Lab 2 对话中的代码、局部测试 `PASS`、CodeGrade 失败反馈及修正后的通过结果。
- **拓展辨析：** 更严格的 C 语言指针／参数术语、Linux GCC 选项、Shell 管道与标准输入等；这些用于理解与复习，不代表官方要求额外实现。
