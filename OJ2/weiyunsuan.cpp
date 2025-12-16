#include <iostream>
#include <string>
using namespace std;

unsigned int A, T, seed = 3, B = 998244353, X, Y;
inline void PRG()
{
    if (A <= 332748117)
        A = A * seed;
    else if (A <= 665496235)
        A = A * seed - B;
    else
        A = A * seed - (B << 1);
}
inline void GetDLRC(unsigned int &D, int &L, int &R, char &C)
{
    PRG();
    D = A & (A << 3);
    PRG();
    L = A & 0x1F, R = (A >> 3) & 0x1F;
    if (L > R)
        L ^= R ^= L ^= R;
    C = (A & 1) ? 'R' : 'C';
    L++;
    R++;
}
unsigned int Reverse(unsigned int n, unsigned int l, unsigned int r)
{
    // 待写
    unsigned int temp = 0; // l到r位是1
    for (int i = l; i <= r; i++)
    {
        temp |= (1 << i - 1); // 有第一位到第r位
    }
    unsigned int tiqu = n & temp; // 有第一位到第r位
    unsigned int reversed = 0;
    tiqu = tiqu >> (l - 1);
    for (unsigned int i = 0; i < r - l + 1; i++)
    {
        reversed = (reversed << 1) | (tiqu & 1);
        tiqu >>= 1;
    }

    unsigned int cleared = n & (~temp);
    unsigned int ans = cleared | (reversed << l - 1);
    return ans;
}
unsigned int Count(unsigned int n, unsigned int l, unsigned int r)
{

    // 待写
    unsigned int ans = 0;
    for (unsigned int i = l - 1; i <= r - 1; i++)
    {
        if ((n >> i) & 1)
            ans++;
    }
    return ans;
}
int main()
{
    unsigned int d;
    int l, r;
    char c;

    cin >> T >> A;

    while (T--)
    {
        GetDLRC(d, l, r, c);
        if (c == 'R')
        {
            /* YOUR CODE */
            unsigned int ans = Reverse(d, l, r);
            X ^= ans;
        }
        if (c == 'C')
        {
            /* YOUR CODE */
            unsigned int ans = Count(d, l, r);
            Y ^= ans;
        }
    }

    cout << X << " " << Y << endl;

    return 0;
}