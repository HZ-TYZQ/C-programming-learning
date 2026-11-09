#include <iostream>
using namespace std;

// 水仙花数：三位数，各位数字的立方和等于它本身
bool isNarcissistic(int n)
{
    int a = n / 100;          // 百位
    int b = n / 10 % 10;      // 十位：先去掉个位，再取末位
    int c = n % 10;           // 个位

    return n == a * a * a + b * b * b + c * c * c;
}

int main()
{
    for (int n = 100; n <= 999; n++)
    {
        if (isNarcissistic(n)) cout << n << endl;
    }
    return 0;
}

/*
输出：
153
370
371
407

拆位公式（三位数 n）：
    百位  n / 100
    十位  n / 10 % 10
    个位  n % 10

注意 n / 10 只去掉了个位，不是十位数字本身。
例如 153 / 10 = 15，还要再 % 10 才得到 5。
*/
