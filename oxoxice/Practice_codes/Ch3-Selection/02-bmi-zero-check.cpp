// 第2题：给 BMI 程序加“身高不能为 0”的保护
#include<iostream>
#include<iomanip>
using namespace std;

int main()
{

	double m, w, bml;
	cout << "请输入身高（米）:";
	cin >> m;
	cout << "请输入体重（公斤）：";
	cin >> w;

	if (m == 0)
	{
		cout << "身高必须大于 0！" << endl;
	}
	else
	{
		bml = w / m / m;
		cout << fixed << setprecision(2);
		cout << "此人的身体质量指数为：" << bml << "kg/m^2" << endl;
	}

	return 0;
}
