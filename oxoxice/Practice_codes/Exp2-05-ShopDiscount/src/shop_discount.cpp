#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    int a;
    double b, c, d;
    cout << "请输入A商品数量: ";
    cin >> a;

    if (a < 0)
    {
        cout << "A商品数量输入错误!" << endl;
        return 0;
    }
    else if (a >= 20)          // 20 个及以上打八折
    {
        b = a * 9.2 * 0.8;
    }
    else
    {
        b = a * 9.2;
    }

    cout << fixed << setprecision(1);
    cout << "商品总金额为" << b << endl;

    cout << "请输入付款金额: ";
    cin >> c;

    d = c - b;
    cout << fixed << setprecision(1);
    cout << "找零金额为" << d << endl;

    return 0;
}
