#include <iostream>
using namespace std;
long long n;
long long high[200005];
bool isbuhuo[200005];
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> high[i];
        isbuhuo[i] = false;
    }
    int ans = 0;
    int left = 0;
    while (left < n)
    {
        while (left < n && isbuhuo[left]) // 找到第一个没有被捕获的星星，位置是left
        {
            left++;
        }
        if (left == n)
            break;
        ans++; // 发射飞船
        long long curh = high[left];
        for (int i = left; i < n; i++)
        {

            if (!isbuhuo[i] && curh == high[i])
            {
                isbuhuo[i] = true;
                curh++;
            }
        }
    }
    cout << ans << endl;
    return 0;
}