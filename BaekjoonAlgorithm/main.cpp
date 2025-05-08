#include <iostream>
#include <vector>
using namespace std;

void PrintResult(const vector<int>& result)
{
    for (const auto& num : result)
    {
        cout << num << " ";
    }

    cout << "\n";
}

void BackTrack(const vector<int>& nums, vector<bool>& visited, vector<int>& result, const int maxLevel, const int level, const int start)
{
    if (level == maxLevel)
    {
        PrintResult(result);
        
        return;
    }

    const int size = static_cast<int>(nums.size());

    for (int i = start; i < size; ++i)
    {
        if (visited[i])
        {
            continue;
        }

        visited[i] = true;
        result.emplace_back(nums[i]);
        BackTrack(nums, visited, result, maxLevel, level + 1, i + 1);
        result.pop_back();
        visited[i] = false;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    const int maxLevel = 6;
    
    while (true)
    {
        int n;
        cin >> n;

        if (n == 0)
        {
            break;
        }

        vector<int> nums(n);
        vector<int> result;
        vector<bool> visited(n, false);
        
        for (int i = 0; i < n; ++i)
        {
            cin >> nums[i];
        }
        
        BackTrack(nums, visited, result, maxLevel, 0, 0);
        cout << "\n";
    }
    
    return 0;
}
