#include<iostream>
using namespace std;

int main()
{
    int a, b, min, max;                    // min 存较小数，max 存较大数
    cout << "请输入两个整数:";
    cin >> a >> b;

    // 求较小数：先假设 a 最小，再用单分支 if 检查 b 是否更小
    min = a;
    if (a > b)
    {
        min = b;
    }

    // 求较大数：用条件运算符。条件成立取 a，否则取 b
    max = a > b ? a : b;

    cout << "较小数为：" << min << endl;
    cout << "较大数为：" << max << endl;

    return 0;
}
