// 第1题：输入分数，判断及格还是不及格
#include <iostream>
using namespace std;

int main()
{
    int score;
    cout << "请输入分数：";
    cin >> score;

    if (score>=60)
    {
        cout << "及格" << endl;
    }
    else
    {
        cout << "不及格" << endl;
    }

    return 0;
}
