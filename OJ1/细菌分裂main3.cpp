#include <iostream>
using namespace std;

long long fast(long long base, long long exp, long long mod) // 快速幂函数！记住它
{

	long long result = 1;
	base = base % mod;
	while (exp > 0)
	{
		if (exp % 2 == 1)
		{
			result = (result * base) % mod;
		}
		base = (base * base) % mod;
		exp = exp / 2;
	}
	return result;
}
int main()
{
	long long a;
	long long b;
	cin >> a >> b;
	long long number = a * fast(2, b, 1000000007);
	long long answer = number % 1000000007;
	cout << answer;
	return 0;
}