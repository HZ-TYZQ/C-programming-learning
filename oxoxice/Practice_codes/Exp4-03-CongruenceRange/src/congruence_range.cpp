// 实验 4 第 3 题：找出区间内同时满足三个同余条件的整数（要求使用 for 语句）
#include<iostream>
using namespace std;

int main()
{
	int num1, num2;          // 键盘输入的两个端点 m、n
	int yes = 0;             // 满足条件的整数个数

	cout << "请输入整数范围m和n:";
	cin >> num1 >> num2;

	// m、n 的大小关系不确定，先归一出上界 hi 和下界 lo
	int hi = (num1 > num2) ? num1 : num2;
	int lo = (num1 < num2) ? num1 : num2;

	for (int i = lo; i <= hi; i++)     // i 从下界走到上界，包含两个边界
	{
		if (i % 3 == 2 && i % 5 == 1 && i % 7 == 4)  // 三个条件同时成立
		{
			cout << i << endl;        // 输出符合条件的整数
			yes++;                    // 计数加 1
		}
	}
	cout << "共有" << yes << "个满足条件的整数" << endl;
	return 0;
}
