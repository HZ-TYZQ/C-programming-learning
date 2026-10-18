// 第5题：求 1~100 的偶数之和
#include <iostream>
using namespace std;

int main()
{
    int sum = 0;
    for (int i = 1; i <= 100; i++)
    {
        if (i%2 != 1)
        {
            sum += i;
        }
    }
    cout << "1~100 的偶数和 = " << sum << endl;
    return 0;
}
