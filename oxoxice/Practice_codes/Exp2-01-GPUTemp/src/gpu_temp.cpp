#include<iostream>
using namespace std;

int main()
{
    double a;
    cout << "请输入GPU当前温度（°C）:";
    cin >> a;

    if (a <= 85)
    {
        cout << "GPU 温度正常，可继续AI训练" << endl;
    }
    else
    {
        cout << "GPU温度过高，暂停AI训练" << endl;
    }

    return 0;
}
