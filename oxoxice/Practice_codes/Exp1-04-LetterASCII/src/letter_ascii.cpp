#include<iostream>
using namespace std;
int main()
{
	char a;
	int b, c;
	cout << "请输入一个大写英文字母：";
	cin >> a;
	b = a +0;
	c = b - 64;
    cout << "英文字母" << a << "的ASCII码是" << b << ",是26个英文字母的第" << c << "个字母"<<endl;
		return 0;
}
