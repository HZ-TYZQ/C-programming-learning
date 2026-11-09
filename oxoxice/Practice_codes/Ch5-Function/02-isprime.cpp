#include <iostream>
using namespace std;

// 判断 n 是否为素数：是返回 true，否则 false
bool isPrime(int n)
{
    if (n < 2) return false;             // 0、1、负数都不是素数，先挡掉

    for (int i = 2; i * i <= n; i++)     // 只需试到根号 n
    {
        if (n % i == 0) return false;    // 找到一个因数，立刻否决
    }
    return true;                         // 一个因数都没找到
}

int main()
{
    for (int a = 1; a <= 100; a++)       // 从 1 开始，靠函数自己挡住
    {
        if (isPrime(a)) cout << a << endl;
    }
    return 0;
}
