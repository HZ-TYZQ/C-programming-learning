#include<iostream>
using namespace std;

int main()
{
    int a, b, min, max;
    cout << "请输入两个整数:";
    cin >> a >> b;

    // 较小数：单分支 if
    min = a;
    if (a > b)
    {
        min = b;
    }

    // 较大数：条件运算符
    max = a > b ? a : b;

    cout << "较小数为：" << min << endl;
    cout << "较大数为：" << max << endl;

    return 0;
}
