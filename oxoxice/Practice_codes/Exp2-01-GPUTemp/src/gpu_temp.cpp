#include<iostream>
using namespace std;

int main()
{
    double a;                              // 温度可能是小数，用 double 而不是 int
    cout << "请输入GPU当前温度（°C）:";
    cin >> a;

    if (a <= 85)                           // 小于或等于 85℃ 都算正常，所以用 <=
    {
        cout << "GPU 温度正常，可继续AI训练" << endl;
    }
    else                                   // 两条路径互斥，用 if...else
    {
        cout << "GPU温度过高，暂停AI训练" << endl;
    }

    return 0;
}
