// 第6题：判断一个整数是不是素数
#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "请输入一个整数：";
    cin >> n;

    int count = 0;

    for (int i = 1; i <= n; i++)
    {
        if (n % i == 0)
        {
            count++;
        }
    }

    if (count == 2)
    {
        cout << n << " 是素数" << endl;
    }
    else
    {
        cout << n << " 不是素数" << endl;
    }

    return 0;
}
