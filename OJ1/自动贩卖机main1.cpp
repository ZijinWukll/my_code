#include <iostream>
#include <vector>

using namespace std;

int main()
{
	unsigned int n, M;
	cout << "输入个数：";
	cin >> n;
	const unsigned int N = n;
	cout << "输入钱：";
	cin >> M;
	vector<unsigned int> goods(N);
	for (unsigned int i = 0; i < N; i++)
	{
		unsigned int price;
		cin >> price;
		goods[i] = price;
	}

	unsigned int min1 = goods[0];
	for (unsigned int i = 0; i < N; i++)
	{
		if (goods[i] < min1)
		{
			min1 = goods[i];
		}
	}

	if (min1 > M)
	{
		cout << "-1";
	}
	else if (min1 <= M)
	{

		for (int j = 0;;)
		{
			if (min1 > M)
			{
				break;
			}
			if (goods[j] <= M)
			{
				M = M - goods[j];
				cout << j + 1 << " ";
				j++;
				while (j == N)
				{
					j = 0;
				}
			}
			else if (goods[j] > M)
			{
				j++;
				while (j == N)
				{
					j = 0;
				}
			}
		}
	}
	return 0;
}