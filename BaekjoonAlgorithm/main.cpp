#include <queue>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool IsInRange(const int num)
{
    return num >= 0 && num < 100001;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, k;
    cin >> n >> k;

    if (n == k)
    {
        cout << 0 << "\n";
        cout << n << "\n";
        return 0;
    }

    vector<int> distance(100001, 0);
    vector<int> prevNum(100001, 0);
    
    queue<int> q;
    
    q.push(n);
    distance[n] = 0;
    
    while (!q.empty())
    {
        const int curr = q.front();
        q.pop();

        vector<int> nums{curr - 1, curr + 1, curr * 2};
        for (int i = 0; i < 3; ++i)
        {
            const int& num = nums[i];
            if (IsInRange(num))
            {
                if (!distance[num])
                {
                    distance[num] = distance[curr] + 1;
                    prevNum[num] = curr;
                    q.push(num);
                }
            }    
        } 
    }

    cout << distance[k] << "\n";

    int index = k;

    vector<int> result;
    result.push_back(n);
    
    while (index != n)
    {
        result.push_back(index);
        index = prevNum[index];
    }
    
    reverse(result.begin() + 1, result.end());

    for (const int& num : result)
    {
        cout << num << " ";
    }
    
    cout << "\n";
    
    return 0;
}
