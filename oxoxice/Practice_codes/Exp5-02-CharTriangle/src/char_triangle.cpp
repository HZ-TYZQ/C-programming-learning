#include <iomanip>
#include <iostream>
using namespace std;

int main()
{
    int num1;
    char num2;

    cout << "请输入行数和字符:";
    cin >> num1 >> num2;

    // 一共 num1 行，第 i 行有 i 个字符
    for (int i = 1; i <= num1; i++)
    {
        // 前面的空格：第 i 行比最后一行少 i 个字符，
        // 每个字符占 2 列，所以补 (num1 - i) 组、每组 2 个空格
        for (int j = 1; j <= num1 - i; j++)
        {
            cout << "  ";
        }

        // 再输出这一行的 i 个字符，每个占 2 列
        for (int a = 1; a <= i; a++)
        {
            cout << setw(2) << num2;
        }

        cout << endl;
    }
    return 0;
}
