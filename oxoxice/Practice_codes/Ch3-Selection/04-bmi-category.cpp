// 动手2：BMI 分级（用学生的答案，接在第1题的完整程序上）
#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
	cout << "2026114164蒋贞奇" << endl;

	double m, w, bml;
	cout << "请输入身高（米）:";
	cin >> m;
	cout << "请输入体重（公斤）：";
	cin >> w;

	bml = w / m / m;
	cout << fixed << setprecision(2);
	cout << "此人的身体质量指数为：" << bml << "kg/m^2" << endl;

	if (bml < 18.5)
	{
		cout << "偏瘦" << endl;
	}
	else if (bml<24)
	{
		cout << "正常" << endl;
	}
	else if (bml<28)
	{
		cout << "超重" << endl;
	}
	else
	{
		cout << "肥胖" << endl;
	}

	return 0;
}
