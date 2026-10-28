#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double v, cost;                                  // v 是用气量，cost 是总价
    cout << "请输入天然气年使用量（立方米）：";
    cin >> v;

    if (v < 0)
    {
        cout << "数据输入错误！" << endl;
        return 0;                                    // 用量为负直接结束，不再往下算总价
    }

    // 阶梯气费是分段累加：只有超出前一段的部分才按高价算
    if (v <= 360)
    {
        cost = v * 2.02;
    }
    else if (v <= 600)
    {
        cost = 360 * 2.02 + (v - 360) * 2.43;
    }
    else
    {
        cost = 360 * 2.02 + 240 * 2.43 + (v - 600) * 3.04;
    }

    // fixed 表示按小数点后固定位数，setprecision(1) 表示保留 1 位
    cout << "这一年天然气费的总价为：" << fixed << setprecision(1) << cost << endl;

    return 0;
}
