#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "请输入n:";
    cin >> n;

    cout << n << "=";

    // 单层循环：用同一个因子反复除，直到 n 变成 1
    for (int a = 2; a <= n; a++)
    {
        if (n % a == 0)
        {
            cout << a;                  // 先输出这个因子
            n = n / a;                  // 再把 n 除掉它
            a--;                        // 同一个因子可能还能再除，退回来重试
            if (n != 1) cout << "*";    // 没除完才打乘号，末尾不会多一个 *
        }
    }

    cout << endl;
    return 0;
}
