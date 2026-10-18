// 第2题：输入 n，求 1+2+...+n
#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "请输入 n：";
    cin >> n;

    int sum = 0;
    int i = 1;

    while (i<=n)
    {
        sum = sum + i;
        i++;
    }

    cout << "1+2+...+" << n << " = " << sum << endl;
    return 0;
}
