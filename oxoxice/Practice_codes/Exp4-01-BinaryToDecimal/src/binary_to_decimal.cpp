// 实验 4 第 1 题：把一个二进制整数转换成十进制整数（要求使用 while 语句）
#include<iostream>
using namespace std;

int main()
{
	long long num1;          // 以十进制形式读入的二进制串，如 1101
	long long sum = 0;       // 转换后的十进制结果
	long long base = 1;      // 当前位的权值：1、2、4、8、16……

	cout << "请输入一个二进制整数:";
	cin >> num1;

	while (num1 > 0)                  // 只要还有位没处理完就继续
	{
		int digit = num1 % 10;        // 取出最低位，得到 0 或 1
		sum = sum + digit * base;     // 该位乘以权值后累加到结果
		base = base * 2;              // 权值翻倍，准备处理高一位
		num1 = num1 / 10;             // 去掉已处理的这一位
	}
	cout << "转换成十进制是:" << sum << endl;
	return 0;
}
