// 实验 4 第 5 题：每天取走剩余样本的一半再多 1 条，统计取完需要多少天
#include<iostream>
using namespace std;

int main()
{
	int sum;                 // 当前剩余的样本数量
	int day = 0;             // 已经训练的天数

	cout << "请输入AI训练样本总数n:";
	cin >> sum;

	if (sum <= 0)            // 样本数非法时直接结束
	{
		cout << "输入有误！请重新输入！" << endl;
		return 0;
	}

	while (sum > 0)                       // 还有剩余样本就继续取
	{
		sum = sum - sum / 2 - 1;          // 取走一半（整数商）再多取 1 条
		day++;                            // 天数加 1
		cout << "第" << day << "天训练后剩余：" << sum << endl;
	}
	cout << "将所有样本取用完毕共需" << day << "天" << endl;
	return 0;
}
