#include <iostream>

int main()
{
    int k;
    std::cin >> k;
    long long i;
    double ans;
    for (i = 1; ans <= k; i++)
    {
        ans = ans + 1.0 / i;
    }
    std::cout << i - 1;
    return 0;
}
