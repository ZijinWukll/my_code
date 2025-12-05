#include <iostream>
using namespace std;
typedef long long ll;
const int MAX = 2000005;
ll a, b;
int n;
ll mod = 998244353;
ll fac[MAX], inv[MAX];

ll fast(ll base, ll exp, ll mod)
{
    ll result = 1;
    base = base % mod;
    while (exp > 0)
    {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

// 预处理阶乘和逆元
void init()
{
    fac[0] = 1;
    for (int i = 1; i < MAX; i++)
        fac[i] = (fac[i - 1] * i) % mod;
    inv[MAX - 1] = fast(fac[MAX - 1], mod - 2, mod);
    for (int i = MAX - 2; i >= 0; i--)
        inv[i] = (inv[i + 1] * (i + 1)) % mod;
}

ll zuhe(ll a, ll b, ll mod)
{
    if (b < 0 || b > a)
        return 0;
    return fac[a] * inv[b] % mod * inv[a - b] % mod;
}

int main()
{
    init();
    cin >> a >> b >> n;
    ll s[1000], t[1000];
    for (int i = 0; i < n; i++)
        cin >> s[i] >> t[i];
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 0 || t[i] == 0)
            cout << 0 << endl;
        else
        {
            ll sum = s[i] + t[i];
            ll comb = zuhe(sum - 2, s[i] - 1, mod);
            ll ans = comb * fast(a, s[i] - 1, mod) % mod * fast(b, t[i] - 1, mod) % mod;
            cout << ans << endl;
        }
    }
    return 0;
}