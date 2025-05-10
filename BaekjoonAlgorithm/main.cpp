#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

long long CalcNums(vector<long long> nums, vector<long long> opVec)
{
    int priNum = 0;
    for (const auto& op : opVec)
    {
        if (op >= 2)
        {
            priNum++;
        }
    }
    
    int index = 0;
    while (priNum > 0)
    {
        const long long& op = opVec[index];
        if (op >= 2)
        {
            priNum--;
            if (op == 2)
            {
                nums[index] = nums[index] * nums[index + 1];
            }
            else if (op == 3)
            {
                if (nums[index] < 0)
                {
                    nums[index] = -(-nums[index] / nums[index + 1]);
                }
                else
                {
                    nums[index] = nums[index] / nums[index + 1];   
                }
            }
            
            nums.erase(nums.begin() + index + 1);
            opVec.erase(opVec.begin() + index);
        }
        else
        {
            index++;
        }

        if (index >= static_cast<int>(opVec.size()))
        {
            break;
        }
    }

    index = 0;
    
    while (!opVec.empty())
    {
        const long long& op = opVec[index];
        if (op == 0)
        {
            nums[index] = nums[index] + nums[index + 1];
        }
        else if (op == 1)
        {
            nums[index] = nums[index] - nums[index + 1];
        }
            
        nums.erase(nums.begin() + index + 1);
        opVec.erase(opVec.begin() + index);
    }
    
    return nums[0];
}

void BackTrack(vector<long long>& nums, vector<long long>& opVec, unordered_map<long long, long long>& ops, long long& maxValue, long long& minValue)
{
    if (nums.size() == opVec.size() + 1)
    {
        maxValue = max(CalcNums(nums, opVec), maxValue);
        minValue = min(CalcNums(nums, opVec), minValue);

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

        opVec.push_back(i);
        op--;
        BackTrack(nums, opVec, ops, maxValue, minValue);
        op++;
        opVec.pop_back();
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
    vector<long long> opVec;
    
    BackTrack(nums, opVec, ops, maxValue, minValue);

    cout << maxValue << "\n";
    cout << minValue << "\n";

    return 0;
}
