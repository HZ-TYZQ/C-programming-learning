#include <iostream>
using namespace std;

// 递归求 n 的阶乘
long long factorial(int n)
{
    cout << "进入 n=" << n << endl;   // 写在递归调用之前：由外往内执行

    if (n == 0) return 1;             // 终止条件：0! = 1
    return n * factorial(n - 1);      // 递推：把问题缩小一号，交给自己
}

int main()
{
    cout << factorial(5) << endl;     // 120
    return 0;
}

/*
运行输出：

进入 n=5
进入 n=4
进入 n=3
进入 n=2
进入 n=1
进入 n=0
120

「往下钻」是 5→0，「弹回来」时才算乘，所以乘起来是 1*2*3*4*5 = 120。
把 cout 挪到 return 之后，输出会变成 0 1 2 3 4 5。
*/
