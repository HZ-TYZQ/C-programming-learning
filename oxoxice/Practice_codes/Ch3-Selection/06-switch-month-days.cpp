// 动手2：用学生的答案（补全成完整程序）
#include <iostream>
using namespace std;

int main()
{
    int month;
    cout << "请输入月份 1~12：";
    cin >> month;

    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        cout << month << " 月有 31 天" << endl;
        break;

    case 4:
    case 6:
    case 9:
    case 11:
        cout << month << " 月有 30 天" << endl;
        break;

    case 2:
        cout << month << " 月有 28 天（平年）" << endl;
        break;

    default:
        cout << "输入错误！只能输 1~12" << endl;
        break;
    }

    return 0;
}
