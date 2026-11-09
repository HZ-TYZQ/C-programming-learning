#include <iostream>
using namespace std;

// 递归求 n 的阶乘
long long fact(int n)
{
    if (n <= 1) return 1;                  // 0! = 1! = 1
    return (long long)n * fact(n - 1);     // 先转型再乘，防止中间结果溢出
}

int main()
{
    long long sum = 0;
    for (int i = 1; i <= 10; i++)
    {
        sum = sum + fact(i);
    }
    cout << sum << endl;                   // 4037913
    return 0;
}

/*
为什么返回类型必须是 long long：

    10! =      3,628,800    int 装得下
    12! =    479,001,600    int 装得下
    13! =  6,227,020,800    超过 int 上限 2,147,483,647

阶乘增长极快，一律用 long long（约 9.2 × 10^18）。

转型的位置也很关键：

    (long long)n * fact(n - 1)   ✔ 先转再乘
    (long long)(n * fact(n - 1)) ✘ 先乘已经溢出，再转没意义
*/
