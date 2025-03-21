#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n = 0;

	cin >> n;
	vector<int> nums(n);
	
	for (int i = 0; i < n; ++i)
	{
		cin >> nums[i];
	}

	sort(nums.begin(), nums.end());
	
	int left = 0, right = n - 1;
	int answerLeft = left, answerRight = right;
	int minValue = 2000000000;
	
	while (left < right)
	{
		int sum = nums[left] + nums[right];
		int value = abs(sum);

		if (value <= minValue)
		{
			minValue = value;
			answerLeft = left;
			answerRight = right;	
		}

		if (sum > 0)
		{
			right--;
		}
		else
		{
			left++;
		}
	}

	cout << nums[answerLeft] << " " << nums[answerRight] << "\n";

	return 0;
}