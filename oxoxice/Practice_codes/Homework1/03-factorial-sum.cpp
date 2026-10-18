// 第3题：求 1! + 2! + 3! + ... + n!
#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
	int n, fact, sum;
	fact = 1;
	sum = 0;

	cout << "请输入数值n:";
	cin >> n;

	for (int i = 1; i <= n; i++)
	{
		fact = fact * i;
		sum = sum + fact;
	}
	cout << "阶乘之和为" << sum << endl;
	return 0;
}
