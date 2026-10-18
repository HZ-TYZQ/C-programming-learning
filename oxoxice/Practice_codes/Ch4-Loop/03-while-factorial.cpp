// 第3题：输入 n，求 n 的阶乘（含非法输入检查）
#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "请输入 n：";
    cin >> n;

    if (n <= 0)
    {
        cout << "请输入正确的n" << endl;
        return 1;                 // ← 加了这一行
    }

    int fact = 1;
    int i = 1;

    while (i <= n)
    {
        fact = fact * i;
        i++;
    }

    cout << n << "! = " << fact << endl;

    return 0;
}
