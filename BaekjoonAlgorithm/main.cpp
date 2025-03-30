#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void Merge(vector<int>& nums, int left, int mid, int right)
{
    vector<int> leftBuffer(nums.begin() + left, nums.begin() + mid);
    vector<int> rightBuffer(nums.begin() + mid, nums.begin() + right);

    int i = 0, j = 0, k = left;
    while (i < leftBuffer.size() && j < rightBuffer.size())
    {
        if (leftBuffer[i] <= rightBuffer[j])
        {
            nums[k++] = leftBuffer[i++];
        }
        else
        {
            nums[k++] = rightBuffer[j++];
        }
    }

    while (i < leftBuffer.size())
    {
        nums[k++] = leftBuffer[i++];
    }

    while (j < rightBuffer.size())
    {
        nums[k++] = rightBuffer[j++];
    }
}

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

    int mergeSize = 1;

    while (mergeSize < n)
    {
        for (int i = 0; i < n; i += mergeSize * 2)
        {
            int left = i;
            int right = min(i + mergeSize * 2, n);
            int mid = min(i + mergeSize, n);

            Merge(nums, left, mid, right);
        }

        mergeSize *= 2;
    }

    for (int i = 0; i < n; ++i)
    {
        cout << nums[i] << "\n";
    }
    
    return 0;
}
