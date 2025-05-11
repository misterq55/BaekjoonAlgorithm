#include <deque>
#include <iostream>
#include <deque>
#include <unordered_map>
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
        return 0;
    }

    vector<int> distance(100001, 1e9);
    vector<int> additionalSecond = {1, 1, 0};
    
    deque<int> dq;
    
    dq.push_back(n);
    distance[n] = 0;
    
    while (!dq.empty())
    {
        const int curr = dq.front();
        dq.pop_front();

        vector<int> nums{curr - 1, curr + 1, curr * 2};
        for (int i = 0; i < 3; ++i)
        {
            const int& num = nums[i];
            if (IsInRange(num))
            {
                const int& additional = additionalSecond[i];
                if (distance[num] > distance[curr] + additional)
                {
                    distance[num] = distance[curr] + additional;
                    additional == 0 ? dq.push_front(num) : dq.push_back(num);
                }
            }    
        } 
    }

    cout << distance[k] << "\n";
    
    return 0;
}
