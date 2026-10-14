#include<iostream>
using namespace std;
int main()
{
	double m,w,bml;
	cout<<"请输入身高（米）";
	cin>>m;
	cout<<"请输入体重（公斤）：";
	cin>>w;
	bml=w/m/m;
	cout<<"此人的身体质量指数为："<<bml<<"kg/m*2";
	return 0;
}
