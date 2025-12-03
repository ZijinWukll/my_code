#include <iostream>
#include <vector>
using namespace std;

bool yes(vector<long long> &input)
{
	int n = input.size();
	if (n < 3)
		return false;
	int max = 0;
	while (max + 1 < n && input[max] < input[max + 1])
	{
		max++;
	}
	if (max == 0 || max == n - 1)
		return false;
	while (input[max] > input[max + 1] && max < n - 1)
	{
		max++;
	}
	return max == n - 1;
}
int main()
{
	int n;
	cin >> n;

	vector<long long> input(n);
	for (int i = 0; i < n; i++)
	{
		cin >> input[i];
	}
	if (yes(input) == true)
		cout << "Yes\n";
	else
		cout << "No\n";
	return 0;
}