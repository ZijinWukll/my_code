#include <iostream>
#include <algorithm>
using namespace std;
int a[100005];

int game(int *a, int n)
{
    sort(a, a + n);

    return a[n / 2];
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    cout << game(a, n) << endl;
    return 0;
}
