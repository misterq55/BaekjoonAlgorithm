#include <iostream>
#include <vector>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n = 0, m = 0, start = 0, end = 0;

	cin >> n;
	vector<int> nums(n);
	
	cin >> m;
	
	for (int i = 0; i < n; ++i)
	{
		cin >> nums[i];
	}

	int answer = 0;

	int sum = 0;

	while (end < n)
	{
		sum += nums[end];
		
		while (sum > m)
		{
			sum -= nums[start];
			start++;
		}
		
		end++;

		if (sum == m)
		{
			answer++;
		}
	}

	cout << answer << "\n";

	return 0;
}