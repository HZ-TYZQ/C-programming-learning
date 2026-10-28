#include<iostream>
using namespace std;

int main()
{
    double vram;                           // 题目要求支持小数，所以用 double
    cout << "请输入显卡显存大小(GB)：";
    cin >> vram;

    // 四档区间从大到小判断：每个 else if 只写下限，上限已经被上面的分支排除了
    if (vram >= 24)
    {
        cout << "可以运行大模型训练" << endl;
    }
    else if (vram >= 10)                   // 能走到这里，说明 vram 一定小于 24
    {
        cout << "可以运行模型微调" << endl;
    }
    else if (vram >= 4)                    // 同理，vram 一定小于 10
    {
        cout << "仅支持模型推理" << endl;
    }
    else                                   // vram < 4
    {
        cout << "显存不足，无法运行AI任务" << endl;
    }

    return 0;
}
