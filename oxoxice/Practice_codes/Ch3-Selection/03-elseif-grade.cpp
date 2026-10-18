// 动手1：用学生的答案
#include <iostream>
using namespace std;

int main()
{
    int score;
    cout << "请输入分数：";
    cin >> score;

    if (score >= 90)      cout << "A" << endl;
    else if (score >=80)        cout << "B" << endl;
    else if (score >=70 )        cout << "C" << endl;
    else if (score >=60 )        cout << "D" << endl;
    else                  cout << "F" << endl;

    return 0;
}
