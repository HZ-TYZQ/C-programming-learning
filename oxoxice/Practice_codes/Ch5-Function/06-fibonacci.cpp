#include <iostream>
using namespace std;

// 递归版：写法最接近数学定义，但同一个子问题会被反复计算
long long fib(int n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fib(n - 1) + fib(n - 2);
}

// 循环版：O(n)，工程上的正确写法
long long fibLoop(int n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;

    long long a = 0, b = 1;      // a = f(0), b = f(1)
    for (int i = 2; i <= n; i++)
    {
        long long c = a + b;     // 先算新值
        a = b;                   // 往前挪一格
        b = c;
    }
    return b;
}

int main()
{
    for (int i = 0; i < 20; i++) cout << fib(i) << " ";
    cout << endl;

    for (int i = 0; i < 20; i++) cout << fibLoop(i) << " ";
    cout << endl;
    return 0;
}

/*
为什么递归版慢：

fib(5) = fib(4) + fib(3)
       = (fib(3) + fib(2)) + (fib(2) + fib(1))
                          ↑          ↑
                    fib(2) 被算了不止一次

调用次数大致：
    n = 20    约 2 万次
    n = 30    约 270 万次
    n = 40    约 3.3 亿次

每增加 1，工作量乘 1.618；每增加 5，乘 11。这叫指数级增长。

递归本身不慢，慢的是「重叠子问题」——同一个 fib(k) 被反复求值。
解决办法是「记忆化」：第一次算出来存进数组，之后直接查表。
（数组在下一章学。）
*/
