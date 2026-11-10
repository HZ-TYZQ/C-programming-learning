#include <iostream>
using namespace std;

// 真因子之和：1 ~ n/2 里能整除 n 的那些数加起来
int sumOfFactors(int n)
{
    if (n < 2) return 0;                  // 1 的真因子和就是 0

    int sum = 0;
    for (int i = 1; i <= n / 2; i++)      // 真因子最大不会超过 n / 2
    {
        if (n % i == 0) sum = sum + i;
    }
    return sum;
}

// 完全数：恰好等于它所有真因子之和
bool isPerfect(int n)
{
    return n == sumOfFactors(n);          // 比较表达式本身就是 bool
}

int main()
{
    for (int n = 1; n <= 10000; n++)
    {
        if (isPerfect(n)) cout << n << endl;
    }
    return 0;
}

/*
输出：

6
28
496
8128

—— 修改记录（第一版 → 这一版）——

1. int 函数里写了 return false
       int sumOfFactors(int n) { ... return false; }
   false 会被隐式转成 0，碰巧能跑对，但返回类型是 int 就该交数字。
   改成 return 0;

2. 循环上界写成 i < n
   真因子最大只可能是 n / 2，写到 n - 1 等于白白多转一倍。
   改成 i <= n / 2;

3. main 里写成 n < 10000
   题目要求 1 ~ 10000，等于漏掉了 10000 本身。
   改成 n <= 10000;
   （10000 恰好不是完全数，所以这次输出没受影响，但边界确实漏了一个）

4. isPerfect 里的 if ... else return true / return false 压成一行
   return n == sumOfFactors(n);
   比较的结果本来就是 true / false，不用再套一层判断。
*/
