#include <iostream>
typedef long long ll;
int main()
{
    ll day;
    ll money = 0;
    std::cin >> day;
    ll sum = 0;
    ll same = 0;
    for (ll i = 1; day - sum >= i; i++)
    {
        sum = sum + i;
        same = same + 1;
    }
    ll more = day - sum;
    for (ll j = 1; j < same + 1; j++)
    {
        money = money + j * j;
    }
    money = money + more * (same + 1);
    std::cout << money;
    return 0;
}
