#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
	double a, b, c;

	cout << "请输入微调运行的小时数：";
	cin >> a;

	c = 2.35;
	b = c * a;

	cout<<fixed<<setprecision(2);
	cout << "微调总费用为；" << b << "元" << endl;

	return 0;
}
