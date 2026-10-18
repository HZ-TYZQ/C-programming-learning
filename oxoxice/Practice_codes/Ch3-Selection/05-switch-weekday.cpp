// 第5题：输入 1~7，输出星期几
#include <iostream>
using namespace std;

int main()
{
    int day;
    cout << "请输入 1~7：";
    cin >> day;

    switch (day)
    {
    case 1:
        cout << "星期一" << endl;
        break;
    case 2:
        cout << "星期二" << endl;
        break;
    case 3:
        cout << "星期三" << endl;
        break;
    case 4:
        cout << "星期四" << endl;
        break;
    case 5:
        cout << "星期五" << endl;
        break;
    case 6:
        cout << "星期六" << endl;
        break;
    case 7:
        cout << "星期日" << endl;
        break;
    default:
        cout << "输入错误！只能输 1~7" << endl;
        break;
    }

    return 0;
}
