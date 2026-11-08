// 实验 4 第 4 题：按固定年增长率计算产值翻一番需要多少年
#include<iostream>
using namespace std;

int main()
{
	double rate;             // 年增长率，如输入 0.13 表示 13%
	double all = 100;        // 当年产值，初始为 100 万元
	int year = 0;            // 已经过的年数

	cout << "请输入年增长率:";
	cin >> rate;

	if (rate <= 0)           // 增长率非正时产值不会增长，会导致死循环
	{
		cout << "输入有误！请重新输入！" << endl;
		return 0;
	}

	while (all < 200)                 // 只要还没达到原来的 2 倍就继续
	{
		all = all * (1 + rate);       // 按复利方式增长
		year++;                       // 年数加 1
		cout << year << "年后产值为：" << all << endl;
	}
	cout << "需要" << year << "年" << endl;   // 输出总共需要的年数
	return 0;
}
