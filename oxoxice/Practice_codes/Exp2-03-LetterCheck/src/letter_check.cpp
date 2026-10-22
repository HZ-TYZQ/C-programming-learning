#include<iostream>
using namespace std;

int main()
{
    char a;                                // 存字符必须用 char，用 int 会读不到字母
    cout << "请输入任意一个字母：";
    cin >> a;

    // 英文字母分两段：a~z 和 A~Z。段内用 && 夹住范围，段间用 || 连接
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
