#include <bits/stdc++.h>
#include <iostream>
using namespace std;

const int N = 5010;
int s[N];
int A, B, C;
void preprocess(int max_len) // 预处理，对相同的abc生成相同的s串
{
    int tmp = 0;
    for (int i = 1; tmp < max_len; i++)
    {
        long long x = (1ll * A * i * i + 1ll * B * i + 1ll * C);

        for (int j = 0; j < 20 && tmp < max_len; j++)
            s[tmp++] = (x >> j) & 1;
    }
}

long long calvalue(const int *s, int n)
{
    long long total = 0, current = 0;
    for (int i = 0; i < n; ++i)
    {
        if (s[i] == 1)
            current++;
        else
            total += current * (current + 1) / 2, current = 0;
    }
    total += current * (current + 1) / 2;
    return total;
}

int main()
{
    int q;
    cin >> q >> A >> B >> C;
    vector<int> lens(q);
    vector<int> value(5010);

    preprocess(5000); // 只预处理到最大需要的长度
    for (int i = 0; i <= 5000; i++)
    {
        value[i] = calvalue(s, i);
    }
    for (int i = 0; i < q; ++i)
    {
        cin >> lens[i];
        cout << value[lens[i]] << endl;
    }
    return 0;
}