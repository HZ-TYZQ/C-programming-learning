// 实验 4 第 2 题：统计 AI 推理置信度的平均值与达标次数（要求使用 do-while 语句）
#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
	double num1;             // 本次输入的置信度（样张为小数，故用 double）
	double sum = 0;          // 所有有效置信度之和
	int yes = 0;             // 达标（>=60）的次数
	int round1 = 0;          // 有效输入的个数

	cout << "请依次输入AI推理置信度，输入小于0或大于100的数结束程序：" << endl;

	do
	{
		cin >> num1;
		if (num1 >= 0 && num1 <= 100)   // 只统计 0~100 之间的有效值
		{
			sum = sum + num1;           // 累加置信度
			round1++;                   // 有效次数加 1
			if (num1 >= 60)             // 60 及以上判定为达标
			{
				yes++;
			}
		}
	} while (num1 >= 0 && num1 <= 100); // 输入越界时结束循环

	if (round1 == 0)                    // 防止除数为 0
	{
		cout << "没有输入有效数据" << endl;
		return 0;
	}
	cout << fixed << setprecision(1);   // 平均值保留 1 位小数
	cout << round1 << "次推理的平均置信度：" << sum / round1 << endl;
	cout << "达标的推理次数：" << yes << endl;
	return 0;
}
