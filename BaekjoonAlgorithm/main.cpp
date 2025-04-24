#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

void backTracking(vector<long long> nums, vector<pair<char, int>>& ops, long long& maxNum, long long& minNum)
{
    if (nums.size() == 1)
    {
        maxNum = max(maxNum, nums[0]);
        minNum = min(minNum, nums[0]);
        
        return;
    }

    for (pair<char, int>& op : ops)
    {
        vector<long long> newNums;
        if (op.second <= 0)
        {
            continue;
        }
        
        long long newNum = 0;
        switch (op.first)
        {
            case '+':
                newNum = nums[0] + nums[1];
                break;
            case '-':
                newNum = nums[0] - nums[1];
                break;
            case '*':
                newNum = nums[0] * nums[1];
                break;
            case '/':
                if (nums[0] < 0)
                {
                    newNum = -(-nums[0] / nums[1]);
                }
                else
                {
                    newNum = nums[0] / nums[1];
                }
                break;
            default:
                break;
        }

        op.second--;

        newNums.push_back(newNum);

        const int size = static_cast<int>(nums.size());
        for (int i = 2; i < size; ++i)
        {
            newNums.push_back(nums[i]);
        }

        backTracking(newNums, ops, maxNum, minNum);
        op.second++;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<long long> nums(n);
    vector<pair<char, int>> ops {{'+', 0}, {'-', 0}, {'*', 0}, {'/', 0}};
    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }

    for (pair<char, int>& op : ops)
    {
        int count;
        cin >> count;
        op.second = count;
    }

    long long maxNum = -1e9;
    long long minNum = 1e9;

    backTracking(nums, ops, maxNum, minNum);
    
    cout << maxNum << "\n";
    cout << minNum << "\n";
    
    return 0;
}
