#include<iostream>
using namespace std;

int main()
{
	int n,h,m;
	cout<<"请输入分钟数：";
	cin>>n;

	h=n/60;
	m=n%60;

	cout<<n<<"分钟可换算为："<<h<<"小时"<<m<<"分钟"<<endl;

	return 0;
}
