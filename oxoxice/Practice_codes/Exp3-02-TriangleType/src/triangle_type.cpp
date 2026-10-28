#include<iostream>
using namespace std;

int main()
{
    double a, b, c;
    cout << "请输入三角形的三条边长：";
    cin >> a >> b >> c;

    if (a <= 0 || b <= 0 || c <= 0)                          // 边长必须为正数
    {
        cout << "输入的边长有误，请重新输入！" << endl;
    }
    else if (a + b > c && a + c > b && b + c > a)            // 外层：先判断能不能构成三角形
    {
        if (a == b && b == c)                                // 等边一定也是等腰，所以等边必须排在前面
        {
            cout << "可以构成等边三角形" << endl;
        }
        else if (a == b || b == c || a == c)                 // 等边已排除，再有两边相等就是等腰
        {
            cout << "可以构成等腰三角形" << endl;
        }
        else
        {
            cout << "可以构成一般三角形" << endl;
        }
    }
    else
    {
        cout << "不能构成三角形" << endl;
    }

    return 0;
}
