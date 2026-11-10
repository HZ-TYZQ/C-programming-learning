// 期中复习卷（第二套）第 4 题：用级数求 e
// e = 1 + 1/1! + 1/2! + 1/3! + ...
// 加到某一项小于 1e-6 为止，输出 e（保留 6 位小数）
// 预期输出：2.718282
//
// 关键：不要每次重算阶乘，用递推 t = t / i。
// t 表示当前项，初值 1.0（即 1/0!），e 初值 1.0。
// 坑：循环条件描述的是"还要继续"，所以是 term >= 1e-6，不是 <。
//     写成 < 时第一轮 1.0 < 1e-6 为假，循环一次都不进，输出 1.000000。

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double e = 1.0, term = 1.0;

    for (int i = 1; term >= 1e-6; ++i)
    {
        term /= i;                 // 先造当前项
        e += term;                 // 再累加，顺序不能反
    }

    cout << fixed << setprecision(6) << e << endl;

    return 0;
}
