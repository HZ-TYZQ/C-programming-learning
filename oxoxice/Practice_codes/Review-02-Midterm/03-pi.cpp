// 期中复习卷（第二套）第 3 题：用级数求 pi
// pi/4 = 1 - 1/3 + 1/5 - 1/7 + ...
// 加到某一项的绝对值小于 1e-6 为止，输出 pi（保留 6 位小数）
// 预期输出：3.141591
//
// 关键：循环次数未知，用 while；分母每次 +2；符号交替用 sign = -sign。
// 这个级数收敛极慢，要算到 1e-6 大约需要五十万项，循环里不能有 cout。

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double num1 = 1.0, num2 = 3.0, sign = -1.0, pi = 1.0;

    while (num1 / num2 >= 1e-6)    // 只看项的绝对值，符号不参与判断
    {
        pi = pi + num1 * sign / num2;
        sign = -sign;
        num2 = num2 + 2;
    }

    cout << fixed << setprecision(6) << pi * 4.0 << endl;

    return 0;
}
