#include <iostream>
using namespace std;
int main()
{
    int x[3] = {1, 2, 5};
    int *p, *q;

    int sum;
    for (p = &x[0], q = &x[2], sum = 0; p <= q; p++)
    {
        sum += *p;
    }
    cout << sum;
    return 0;
}