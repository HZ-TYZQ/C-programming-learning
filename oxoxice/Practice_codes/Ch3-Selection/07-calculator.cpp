// 综合项目：简易计算器（四则运算）
// 用到了第3章学过的：if、else、switch、break、default、return
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    cout << "===== 简易计算器 =====" << endl;
    cout << "支持的运算符：+  -  *  /" << endl;

    double a, b;
    char op;

    cout << "请输入第一个数：";
    cin >> a;
    cout << "请输入运算符：";
    cin >> op;
    cout << "请输入第二个数：";
    cin >> b;

    double result;

    switch (op)
    {
    case '+':
        result = a + b;
        break;

    case '-':
        result = a - b;
        break;

    case '*':
        result = a * b;
        break;

    case '/':
        if (b == 0)                       // 嵌套在 case 里的 if
        {
            cout << "错误：除数不能为 0！" << endl;
            return 1;                     // 直接结束整个程序
        }
        result = a / b;
        break;

    default:
        cout << "错误：不认识的运算符 [" << op << "]" << endl;
        return 1;
    }

    cout << fixed << setprecision(2);
    cout << a << " " << op << " " << b << " = " << result << endl;

    return 0;
}
