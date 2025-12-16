#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;
int n, moqi[21][21], danda[21];
long long zudui[21][21][21];
long long dp[1 << 21];

long long jingongmax(int i, int j, int k)
{
    long long dan = max({danda[i], danda[j], danda[k]});

    long long shuang = max({moqi[i][j], moqi[j][i], moqi[i][k], moqi[k][i], moqi[j][k], moqi[k][j]});

    long long san = 1LL * moqi[i][j] * moqi[i][k] * moqi[j][k];
    return max({dan, shuang, san});
}

void preprocess()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                if (i != j && i != k && j != k)
                    zudui[i][j][k] = jingongmax(i, j, k);
}

long long DP()
{

    int full = (1 << n) - 1;

    vector<pair<long long, int>> triples;
    triples.reserve(n * (n - 1) * (n - 2) / 6);
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            for (int k = j + 1; k < n; ++k)
            {
                long long w = zudui[i][j][k];
                int m = (1 << i) | (1 << j) | (1 << k);
                triples.emplace_back(w, m);
            }
    sort(triples.begin(), triples.end(), [](const pair<long long, int> &a, const pair<long long, int> &b)
         { return a.first > b.first; });

    int maxTriples = triples.size();
    vector<long long> pref(maxTriples + 1, 0);
    for (int i = 0; i < maxTriples; ++i)
        pref[i + 1] = pref[i] + triples[i].first;

    auto greedy_lower = [&]()
    {
        int rem = full;
        long long sum = 0;
        for (auto &t : triples)
        {
            int m = t.second;
            if ((m & rem) == m)
            {
                sum += t.first;
                rem ^= m;
            }
            if (rem == 0)
                break;
        }
        return sum;
    };
    long long best = greedy_lower();

    function<void(int, long long)> dfs = [&](int mask, long long cur)
    {
        if (mask == 0)
        {
            if (cur > best)
                best = cur;
            return;
        }
        int cnt = __builtin_popcount(mask);
        int need = cnt / 3;

        long long ub = (need <= maxTriples) ? pref[need] : pref[maxTriples];
        if (cur + ub <= best)
            return;

        int p = __builtin_ctz(mask);

        for (int j = p + 1; j < n; ++j)
            if (mask & (1 << j))
            {
                for (int k = j + 1; k < n; ++k)
                    if (mask & (1 << k))
                    {
                        int newmask = mask ^ ((1 << p) | (1 << j) | (1 << k));
                        dfs(newmask, cur + zudui[p][j][k]);
                    }
            }
    };

    dfs(full, 0);
    return best;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    if (n % 3 != 0)
    {
        cout << 0 << endl;
        return 0;
    }
    for (int i = 0; i < n; i++)
        cin >> danda[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> moqi[i][j];

    preprocess();
    long long ans = DP();
    cout << ans << endl;
    return 0;
}