// 第1题：秒数换算成「几时几分几秒」，并计算占一天的百分比
#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
	int a,b,c,d,e;
	double zhanbi;

	cout << "请输入秒数：";
	cin >> a;

	 b= a/ 60;
	 c=b / 60;
	 d=a %60;
	 e = b % 60;
	zhanbi = (double)a / 3600 / 24*100;

	cout << c << "时" << e << "分" << d << "秒" << endl;
	cout << fixed << setprecision(2);
	cout << "占一天的 " << zhanbi << "%" << endl;
	return 0;
}
