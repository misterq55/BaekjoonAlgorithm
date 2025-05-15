#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<int> nums(n + 1);
    priority_queue<int, vector<int>, greater<>> minHeap;
    priority_queue<int> maxHeap;
    
    for (int i = 1; i <= n; ++i)
    {
        cin >> nums[i];

        if (maxHeap.empty() || nums[i] <= maxHeap.top())
        {
            maxHeap.push(nums[i]);
        }
        else
        {
            minHeap.push(nums[i]);
        }
        
        if (maxHeap.size() > minHeap.size() + 1)
        {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }

        if (minHeap.size() > maxHeap.size())
        {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
        
        cout << maxHeap.top() << '\n';
    }
    
    return 0;
}
