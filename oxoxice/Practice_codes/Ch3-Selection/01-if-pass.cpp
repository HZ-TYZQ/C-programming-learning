// 动手1：用学生的答案 score>=60
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
