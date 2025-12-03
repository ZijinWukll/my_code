#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int ops[105] = {0};
int main()
{

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int k;
    string s1;
    string s2;
    cin >> n >> k;
    cin >> s1 >> s2;

    if (s1[0] != s2[0])
    {
        cout << "NO";
        return 0;
    }

    // 标记s1的每个位置是否已被ops占用
    bool used[105] = {0};
    for (int i = n - 1; i >= 0; i--)
    {
        bool found = false;
        for (int j = i; j >= 0; j--)
        {
            if (s2[i] == s1[j] && !used[j])
            {
                ops[i] = j;
                // 将所有大于j的位置都标记为已占用
                for (int t = j + 1; t < n; t++)
                    used[t] = true;
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "NO";
            return 0;
        }
    }

    int max_ops = 0;
    for (int i = 0; i < n; i++)
    {
        max_ops = max(max_ops, i - ops[i]);
    }
    if (k >= max_ops)
    {
        cout << "YES";
    }
    else
    {
        cout << "NO";
    }
    return 0;
}