# Exp2-01 GPU 温度判断

实验 2 第 1 题。

## 题目

输入 GPU 实时温度。若温度小于或等于 85℃，输出「GPU 温度正常，可继续AI训练」；否则输出「GPU温度过高，暂停AI训练」。

## 语言

C++（`src/gpu_temp.cpp`）

## 编译与运行

```bash
mkdir -p builds
g++ src/gpu_temp.cpp -o builds/gpu_temp
./builds/gpu_temp
```

## 运行示例

输入 `72.5`：

```
请输入GPU当前温度（°C）:72.5
GPU 温度正常，可继续AI训练
```

输入 `87`：

```
请输入GPU当前温度（°C）:87
GPU温度过高，暂停AI训练
```

## 要点

- 阈值判断用 `<=`：85 度本身也算正常，写成 `< 85` 会把边界判错。
- 温度可能是小数，用 `double` 而不是 `int`。
- 判断只有两条互斥的路径，所以用 `if...else` 而不是两个独立的 `if`。
