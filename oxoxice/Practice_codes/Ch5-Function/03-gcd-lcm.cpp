#include <iostream>
using namespace std;

// 辗转相除法求最大公约数
int gcd(int a, int b)
{
    while (b != 0)
    {
        int t = a % b;   // 先存余数，否则 a 被覆盖后就再也算不出 a % b 了
        a = b;           // a 挪到 b 的位置
        b = t;           // b 挪到余数的位置
    }
    return a;            // 循环结束时 b 为 0，答案留在 a 里
}

// 最小公倍数：先除后乘，避免 a * b 溢出
int lcm(int a, int b)
{
    return a / gcd(a, b) * b;
}

int main()
{
    int x, y;
    cin >> x >> y;
    cout << "最大公约数是:" << gcd(x, y) << endl;
    cout << "最小公倍数是:" << lcm(x, y) << endl;
    return 0;
}
