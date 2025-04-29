#include <iostream>
#include <vector>
using namespace std;

void printResult(const vector<int>& result)
{
    for (const auto& num : result)
    {
        cout << num << " ";
    }

    cout << "\n";
}

void backTracking(const vector<int>& nums, vector<int>& result, const int size, const int m, const int level, const int num)
{
    if (level == m - 1)
    {
        printResult(result);
        return;
    }
    
    const int nextLevel = level + 1;
    
    for (int i = 0; i < size; ++i)
    {
        if (nums[i] < num)
        {
            continue;
        }
        
        result.emplace_back(nums[i]);
        backTracking(nums, result, size, m, nextLevel, nums[i]);
        result.pop_back();
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> nums;
    vector<int> result;

    for (int i = 1; i <= n; ++i)
    {
        nums.push_back(i);
    }

    backTracking(nums, result, n, m, -1, 0);

    return 0;
}
