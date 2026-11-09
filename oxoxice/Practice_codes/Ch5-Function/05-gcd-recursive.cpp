#include <iostream>
using namespace std;

// 辗转相除法的递归写法：与数学定义一一对应
//   gcd(a, 0) = a
//   gcd(a, b) = gcd(b, a % b)
int gcd(int a, int b)
{
    if (b == 0) return a;        // 终止条件
    return gcd(b, a % b);        // 新的 a 是旧的 b，新的 b 是余数
}

int main()
{
    cout << gcd(48, 18) << endl;     // 6
    cout << gcd(7, 13) << endl;      // 1
    cout << gcd(100, 75) << endl;    // 25
    return 0;
}

/*
对比 03-gcd-lcm.cpp 里的循环版：

    while (b != 0)
    {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;

循环版手动维护 a、b 的「滚动」，递归版把滚动交给函数调用自己完成。
两者结果完全一样，递归版更短、更贴数学定义。
*/
