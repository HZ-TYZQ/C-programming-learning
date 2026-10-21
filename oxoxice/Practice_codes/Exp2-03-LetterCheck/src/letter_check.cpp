#include<iostream>
using namespace std;

int main()
{
    char a;
    cout << "请输入任意一个字母：";
    cin >> a;

    // 大写段 A~Z 或 小写段 a~z，段内用 &&，段间用 ||
    if (a >= 'a' && a <= 'z' || a >= 'A' && a <= 'Z')
    {
        cout << "输入的字符" << a << "是英文字母" << endl;
    }
    else
    {
        cout << "输入的字符" << a << "不是英文字母" << endl;
    }

    return 0;
}
