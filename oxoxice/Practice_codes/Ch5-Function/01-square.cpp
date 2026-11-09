#include <iostream>
using namespace std;

// 求 n 的平方
int square(int n)
{
    return n * n;          // 只负责算，不打印
}

int main()
{
    for (int a = 1; a <= 5; a++)
    {
        cout << a << "的平方是:" << square(a) << endl;   // 打印交给 main
    }
    return 0;
}
