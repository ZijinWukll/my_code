#include <bits/stdc++.h>

const int inf = 1e9 + 7;
const int MAXN = 10050;

using namespace std;

int n, L[MAXN];

void Init()
{
    for (int i = 0; i < MAXN; i++)
        L[i] = inf; // Since L(x) is a minimum number for x, we initially set all uncalculated L(i) to inf
    L[1] = 1;       // 1只能用一个“1”表示
}

signed main()
{
    // Initialization
    Init();

    cin >> n;

    // Get answer from sub-problems
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j * 2 <= i; j++)
            L[i] = min(L[i], L[j] + L[i - j]); // Use '+' to achieve i from j and i-j

        for (int j = 1; j * j <= i; j++)
            if (!(i % j))
                L[i] = min(L[i], L[j] + L[i / j]); // Use '*' to achieve i from j and i/j

        // 拼接操作
        if (i >= 10)
        {
            for (int p = 10; p <= i; p *= 10)
            {
                int k = i % p;
                int j = (i - k) / p;
                string sj = to_string(j), sk = to_string(k);
                string si = sj + sk;
                if (k == 0 || j == 0)
                    continue;
                if (stoi(si) == i)
                    L[i] = min(L[i], L[j] + L[k]);
            }
        }
    }

    // Calculate final answer
    cout << L[n] << endl;

    return 0;
}