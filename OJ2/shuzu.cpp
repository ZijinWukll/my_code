#include <iostream>
typedef long long ll;
using namespace std;

ll F(ll n)
{
    if (n % 4 == 0)
        return n * (n + 4) / 4;
    if (n % 4 == 1)
        return (n + 1) * (n + 1) / 4;
    if (n % 4 == 2)
        return (n + 2) * (n + 2) / 4;
    if (n % 4 == 3)
        return (n + 1) * (n + 1) / 4;
}
int main()
{
    int T;
    ll arr[T][2];
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cin >> arr[i][j];
        }
    }
    for (int i = 0; i < T; i++)
    {
        ll answer = F(arr[i][1]) - F(arr[i][0] - 1);

        cout << answer % 1000000007 << endl;
    }
    return 0;
}
