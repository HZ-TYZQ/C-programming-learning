// 第2题：快递运费计算（按重量分段计价）
#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
	double w;

	cout << "请输入包裹重量（公斤）：";
	cin >> w;

	cout << fixed << setprecision(2);

	if (w <= 0)
	{
		cout << "重量输入错误" << endl;
		return 1;
	}
	else if (w > 5)
	{
		cout << "运费：" << 30 + (w - 5) * 3 << " 元" << endl;
	}
	else if (w > 1)
	{
		cout << "运费：" << 10 + (w - 1) * 5 << " 元" << endl;
	}
	else
	{
		cout << "运费：" << 10.0 << " 元" << endl;
	}
	return 0;
}
