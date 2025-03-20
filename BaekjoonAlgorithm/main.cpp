#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n = 0, k = 0, start = 0, end = 0;

	cin >> n;
	vector<int> nums(n);
	
	cin >> k;
	
	for (int i = 0; i < n; ++i)
	{
		cin >> nums[i];
	}

	int answer = 0;

	unordered_map<int, int> duplicatedCount;
	
	while (end < n)
	{
		int count = ++duplicatedCount[nums[end]];

		while (count > k)
		{
			--duplicatedCount[nums[start]];
			start++;
			count = duplicatedCount[nums[end]];
		}
		
		end++;

		answer = max(answer, end - start);
	}

	cout << answer << "\n";

	return 0;
}