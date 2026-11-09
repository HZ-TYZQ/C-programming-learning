#include <iostream>
using namespace std;

// 求 1 + 2 + ... + n
int sumTo(int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum = sum + i;
    }
    return sum;
}

int main()
{
    int n;
    cin >> n;
    cout << sumTo(n) << endl;
    return 0;
}
