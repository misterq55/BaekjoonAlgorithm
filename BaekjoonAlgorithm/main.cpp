#include <iostream>
#include <string>
#include <vector>
#include "CustomSort.h"
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string question;
	getline(cin, question);

	vector<int> nums;

	for (const auto& ch : question)
	{
		nums.push_back(ch - '0');
	}

	const vector<int> result = CBJSort::Sort(nums);
	string str;
	for (const auto& num : result)
	{
		str.append(to_string(num));
	}
	
	cout << str << "\n";

	return 0;
}