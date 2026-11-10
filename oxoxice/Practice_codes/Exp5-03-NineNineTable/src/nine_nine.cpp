#include <iostream>
using namespace std;

int main()
{
    for (int i = 1; i <= 9; i++)
    {
        // 每行先补空格，让每一行右边对齐（一个算式占 8 列）
        for (int k = 1; k <= 9 - i; k++)
        {
            cout << "        ";      // 8 个空格
        }

        for (int j = 1; j <= i; j++)
        {
            cout << j << "*" << i << "=" << i * j;

            // 每个算式补到 8 个字符宽：
            //   结果是一位数 → 算式 5 个字符，补 3 个空格
            //   结果是两位数 → 算式 6 个字符，补 2 个空格
            if (i * j >= 10) cout << "  ";
            else             cout << "   ";
        }

        cout << endl;
    }
    return 0;
}
