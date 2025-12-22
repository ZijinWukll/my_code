#include <iostream>
using namespace std;
bool isprime(int n)
{
    if (n == 2)
    {
        return true;
    }
    else if (n <= 1)
    {
        return false;
    }
    for (int i = 2; i < n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int n;
    n = 6;
    while (1)
    {
        bool find = false;
        for (int a = 2; a <= n / 2; a++)
        {
            int b = n - a;
            if (isprime(a) && isprime(b))
            {
                find = true;
            }
        }
        if (find)
            n += 2;
        else
            break;
    }
    return 0;
}