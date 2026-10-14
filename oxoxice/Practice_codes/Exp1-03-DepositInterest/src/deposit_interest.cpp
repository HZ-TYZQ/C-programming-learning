#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
	double a,b;
	cout<<"请输入存款本金（元）：";
	cin>>a;
	b=a*(1+0.0155*3);
		cout<<fixed<<setprecision(2);
		cout<<"三年后存款的本息和为："<<b<<"元"<<endl;
		return 0;
}
