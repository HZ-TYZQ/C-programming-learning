#include <iostream>
using namespace std;

int main()
{
    int m;
    cout << "请输入月份：";
    cin >> m;

    if (m > 12 || m < 1)                 // 先判断合法性，非法月份不进入 switch
    {
        cout << "月份输入错误" << endl;
        return 0;
    }

    // 几个 case 摞在一起共用一个 break，把 12 个标签压到 4 个分句
    switch (m)
    {
    case 3:
    case 4:
    case 5:
        cout << m << "月处于春季" << endl;
        break;

    case 6:
    case 7:
    case 8:
        cout << m << "月处于夏季" << endl;
        break;

    case 9:
    case 10:
    case 11:
        cout << m << "月处于秋季" << endl;
        break;

    case 12:
    case 1:
    case 2:
        cout << m << "月处于冬季" << endl;
        break;
    }

    return 0;
}
