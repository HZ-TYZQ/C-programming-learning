#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    int a;                                 // a：商品数量
    double b, c, d;                        // b：总金额  c：付款金额  d：找零
    cout << "请输入A商品数量: ";
    cin >> a;

    if (a < 0)                             // 数量为负：非法输入，直接结束程序
    {
        cout << "A商品数量输入错误!" << endl;
        return 0;
    }
    else if (a >= 20)                      // 20 个及以上打八折
    {
        b = a * 9.2 * 0.8;
    }
    else                                   // 不足 20 个，按原价
    {
        b = a * 9.2;
    }

    cout << fixed << setprecision(1);      // 之后所有小数统一保留 1 位
    cout << "商品总金额为" << b << endl;    // 末尾的 endl 负责换行

    cout << "请输入付款金额: ";
    cin >> c;

    d = c - b;                             // 找零 = 付款金额 - 总金额
    cout << fixed << setprecision(1);
    cout << "找零金额为" << d << endl;

    return 0;
}
