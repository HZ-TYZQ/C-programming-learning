// 期中复习卷（第二套）第 2 题：a + aa + aaa + ...
// 输入 a（1~9）和 n，求 a + aa + aaa + ... 共 n 项之和
// 样例：输入 2 3  ->  输出 246（2 + 22 + 222）
//
// 关键：用 t = t * 10 + a 递推每一项，不需要数组。
// 注意 t 和 sum 都要是 int，用 double 会出现 222.0000001 这种误差。

#include <iostream>
using namespace std;

int main()
{
    int a, n, t = 0, sum = 0;

    cin >> a >> n;

    for (int i = 1; i <= n; i++)
    {
        t = t * 10 + a;            // 第 1 轮 0*10+a 正好等于 a，第一项自动生成
        sum = sum + t;
    }

    cout << sum << endl;

    return 0;
}
