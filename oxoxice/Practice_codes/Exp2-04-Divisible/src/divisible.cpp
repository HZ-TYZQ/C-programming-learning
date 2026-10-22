#include<iostream>
using namespace std;

int main()
{
    int a;
    cout << "请输入一个整数：";
    cin >> a;

    // 能被 4 整除：除 4 的余数为 0
    if (a % 4 == 0)
    {
        cout << a << "能被4整除" << endl;
    }
    else
    {
        cout << a << "不能被4整除" << endl;
    }

    // 不能被 7 整除：题目要求用「不等于」运算符，所以条件写 != 0
    if (a % 7 != 0)
    {
        cout << a << "不能被7整除" << endl;
    }
    else
    {
        cout << a << "能被7整除" << endl;
    }

    return 0;
}
