# Voltage QC System — 踩坑记录与注意事项

> [!info] 综合练习复盘
> 本次主要练习 C 语言的流程控制、循环嵌套、数据统计与程序状态管理。

## 1. break 的作用范围

`break` 退出最近的一层 `switch` 或循环，而不是简单退出最近的一对 `{}`。

例如：

    for (int i = 0; i < samples; i++)
    {
        switch (level)
        {
            case 1:
                break;  // 只退出 switch
        }

        // for 循环仍会继续执行
    }

**踩坑：**

- 曾经将 `break` 放在采样循环之前，导致后面的 `for` 根本无法执行。
- 在 `case '2'` 中将 `break` 放在 `if (hasData)` 内部，导致 `else` 分支执行完后贯穿到下一个 `case`。

**经验：**

尽量将每个 `case` 的最终 `break` 放在分支末尾，避免藏在 `if-else` 内部。

---

## 2. continue 与 break 不同

- `break`：结束整个最近的循环或 `switch`。
- `continue`：跳过当前循环剩余语句，进入下一次迭代。

特别注意：当 `switch` 嵌套在 `for` 中时：

- `break` 退出 `switch`。
- `continue` 作用于外层 `for`。

本题中：

- 电压为 `-1`：使用 `break` 结束采样。
- 电压 INVALID：使用 `continue`，跳过有效数据统计。
- 正常分类：退出 `switch` 后继续计算统计数据。

---

## 3. 最大值和最小值的初始化

**错误思路：**

直接令 `minVoltage = 0`。

如果所有有效电压都大于 0，最小值就可能一直错误地保持为 0。

**正确方法：**

第一个有效样本同时初始化最大值和最小值：

    if (validCount == 0)
    {
        minVoltage = voltage;
        maxVoltage = voltage;
    }
    else
    {
        if (voltage < minVoltage)
        {
            minVoltage = voltage;
        }

        if (voltage > maxVoltage)
        {
            maxVoltage = voltage;
        }
    }

    validCount++;

**踩坑：**

1. 曾先执行 `validCount++`，再判断 `validCount == 0`，导致首次初始化分支无法进入。
2. 曾将最小值判断放进最大值判断内部，使最小值无法独立更新。

**经验：**

- 先判断是否为首个有效样本，再更新计数。
- 更新最大值与最小值的两个 `if` 必须互相独立。

---

## 4. 避免除以零

平均值计算：

    average = sum / validCount;

当 `validCount == 0` 时，不能执行该运算。

正确方式：

    if (validCount > 0)
    {
        average = sum / validCount;
    }
    else
    {
        printf("No valid voltage data.\n");
    }

同时，没有有效样本时也不能读取尚未初始化的最大值、最小值。

---

## 5. 每次测试必须重置统计变量

如果计数器只在 `main()` 开头初始化，那么第二次测试可能混入第一次的数据。

每次选择 `1` 开始新测试时，都应该重新初始化：

    lowCount = 0;
    normalCount = 0;
    highCount = 0;
    invalidCount = 0;
    validCount = 0;

    sum = 0.0f;
    average = 0.0f;

**经验：**

重复执行的功能必须明确区分哪些数据需要保留，哪些需要重置。

---

## 6. 使用状态变量区分不同情况

本题使用：

    int hasData = 0;

表示是否进行过测试。

- `hasData == 0`：从未测试。
- `hasData == 1 && validCount == 0`：测试过，但没有有效样本。
- `hasData == 1 && validCount > 0`：存在有效测试数据。

测试完成后：

    hasData = 1;

比 `hasData++` 更符合这个变量的含义。

**经验：**

状态变量与计数器不同。

状态变量通常用于表示程序所处的状态，而不是记录执行次数。

---

## 7. float 与 double 的精度问题

**实际踩坑：**

使用 `float voltage` 读取 `3.10`，再与 `3.10` 比较时，曾错误分类为 LOW。

原因：

- `float` 和 `double` 通常不能精确表示 3.10 这样的十进制小数。
- `3.10` 默认是 `double` 字面量。
- 在比较中，`float` 变量会被提升为 `double`。
- 两种精度下的近似值可能不同。

本题使用：

    voltage < 3.10f

以及：

    voltage <= 3.50f

解决了实际测试中的边界误判。

> [!warning] 注意
> `3.10f` 仍然不是数学意义上精确的 3.10。
>
> 只是让比较双方采用相同的浮点类型，并不能消除所有浮点误差。
>
> 对于要求精确到固定单位的测量，可以考虑整数毫伏等表示方式。

另外，`-1.0f` 可以被二进制浮点数精确表示，因此本题使用 `voltage == -1.0f` 判断停止标记是可行的。

---

## 8. scanf 读取 char 时的空格

普通写法：

    scanf("%c", &choice);

可能读到上次输入留下的换行符。

本题使用：

    scanf(" %c", &choice);

`%c` 前面的空格可以跳过空白字符，包括空格、制表符和换行符。

**注意：**

`scanf("%d", &number)` 和 `scanf("%f", &voltage)` 本身就会跳过前导空白字符。

---

## 9. switch 的贯穿（Fall-through）

如果某个 `case` 没有执行 `break`，程序会继续执行后面的 `case`，不会重新检查它是否匹配。

    switch (x)
    {
        case 1:
            printf("A\n");

        case 2:
            printf("B\n");
            break;
    }

当 `x == 1` 时，会输出：

    A
    B

**经验：**

写完每个 `case` 后，检查是否需要 `break`。

尤其注意 `break` 是否只存在于某一个 `if` 分支中。

---

## 10. 嵌套循环的理解

本题使用两层 `for` 绘制统计图：

- 外层循环：依次处理 LOW、NORMAL、HIGH、INVALID。
- 内层循环：根据当前类别的数量打印 `*`。

例如：

    for (int j = 0; j < count; j++)
    {
        printf("*");
    }

当 `count == 0` 时，内层循环不会执行。

因此不需要额外判断是否有星号要打印。

**经验：**

分析嵌套循环时，先固定外层变量，再观察内层循环如何完整运行。

如果内层次数随外层变量变化，总执行次数需要逐轮计算。

---

## 11. printf 格式化输出

本题使用：

    printf("%-15s: %6d\n", "Low", lowCount);
    printf("%-15s: %6.2f\n", "Average", average);

其中：

- `%-15s`：字符串左对齐，最小宽度为 15。
- `%6d`：整数右对齐，最小宽度为 6。
- `%6.2f`：浮点数保留两位小数，最小宽度为 6。

注意：宽度是最小值，不代表超过宽度的内容会被截断。

---

## 12. 函数与 return

本题提前使用了自定义函数：

    int determine_voltage_level(float voltage)

作用是将电压分类逻辑从 `main()` 中独立出来。

- `int`：函数返回整数。
- `float voltage`：函数参数。
- `return`：结束当前函数，并返回结果。

注意：`return` 与 `break` 不同。

- `return`：退出当前函数。
- `break`：退出最近的循环或 `switch`。

后续课程再系统学习函数和参数。

---

## 13. 代码格式：Allman 风格

以后统一使用 Allman 风格和 4 空格缩进。

例如：

    if (voltage > maxVoltage)
    {
        maxVoltage = voltage;
    }
    else
    {
        printf("Not maximum\n");
    }

特点：

- 左大括号单独占一行。
- 大括号上下对齐。
- 多层嵌套时更容易辨认代码块。
- 即使只有一条语句，也尽量保留 `{}`。

Neovim 的 `.clang-format` 可配置：

    BasedOnStyle: LLVM
    BreakBeforeBraces: Allman
    IndentWidth: 4
    UseTab: Never

---

## 14. 暂时搁置：scanf 输入健壮性

当前程序尚未正确处理输入字母等非数字内容。

例如：

    scanf("%d", &samples);

如果输入 `abc`，`scanf` 无法完成整数转换。

由于错误字符可能留在输入缓冲区，反复读取可能导致死循环。

同时：

    scanf("%f", &voltage);

读取失败时也不会自动将 `voltage` 改成正确的新值。

> [!todo] 后续专项学习
>
> - `scanf` 返回值
> - 输入失败的判断
> - 输入缓冲区处理
> - 避免非数字输入造成死循环

本阶段暂时只要求处理正确类型的输入。

---

## 总结

本次综合题最大的收获：

1. `break`、`continue` 必须结合嵌套结构判断作用范围。
2. 统计变量的初始化和更新顺序非常重要。
3. 多轮测试需要正确管理程序状态。
4. 边界情况（零有效样本、提前结束、非法电压）必须单独考虑。
5. 浮点数比较可能出现精度问题。
6. 保持统一的大括号风格，有助于避免看错控制结构。

**核心思路：先保证控制流程正确，再维护统计状态，最后处理边界情况和输出格式。**
