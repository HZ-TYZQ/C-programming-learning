// 期中复习卷（第二套）第 1 题：加减规律组项求和
// 求 1 - 1/2 + 1/3 - 1/4 + ... 前 100 项之和，保留 4 位小数
// 预期输出：0.6882
//
// 踩过的坑：一开始用 i / 2 != 0 判断奇偶，这个条件恒为真，导致全部相加，
// 结果是 5.1874。判断奇偶必须用 i % 2，所以循环变量要用 int。
// 分子用 double，保证 1.0 / i 是浮点除法。

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double a = 1.0, sum = 0, sign = 1.0;

    for (int i = 1; i <= 100; i++)
    {
        sum = sum + sign * (a / i);
        sign = -sign;              // 每轮翻转符号：1 -> -1 -> 1 -> ...
    }

    cout << fixed << setprecision(4) << sum << endl;

    return 0;
}
