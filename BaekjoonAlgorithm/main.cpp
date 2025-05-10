#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

void BackTrack(vector<long long> nums, unordered_map<long long, long long>& ops, long long& maxValue, long long& minValue)
{
    if (nums.size() == 1)
    {
        maxValue = max(nums[0], maxValue);
        minValue = min(nums[0], minValue);

        return;
    }

    const long long opSize = static_cast<long long>(ops.size());
    for (long long i = 0; i < opSize; ++i)
    {
        long long& op = ops[i];
        if (op == 0)
        {
            continue;
        }

        long long newNum = 0;
        switch (i)
        {
        case 0:
            newNum = nums[0] + nums[1];
            break;
        case 1:
            newNum = nums[0] - nums[1];
            break;
        case 2:
            newNum = nums[0] * nums[1];
            break;
        case 3:
            if (nums[0] < 0)
            {
                newNum = (-(-nums[0]) / nums[1]);   
            }
            else
            {
                newNum = nums[0] / nums[1];
            }
            break;
        default:
            break;
        }

        vector<long long> newNums;
        newNums.push_back(newNum);

        const long long numSize = static_cast<long long>(nums.size());
        for (long long j = 2; j < numSize; ++j)
        {
            newNums.push_back(nums[j]);
        }
        
        op--;
        BackTrack(newNums, ops, maxValue, minValue);
        op++;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    long long n;
    cin >> n;

    vector<long long> nums(n);
    for (long long i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }

    unordered_map<long long, long long> ops = {{0, 0}, {1, 0}, {2, 0}, {3, 0},};
    for (long long i = 0; i < 4; ++i)
    {
        cin >> ops[i];
    }

    long long maxValue = -1e9, minValue = 1e9;
    BackTrack(nums, ops, maxValue, minValue);

    cout << maxValue << "\n";
    cout << minValue << "\n";

    return 0;
}
