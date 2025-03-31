#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t = 0;

    cin >> t;

    vector<int> nums(t);

    int maxNum = 0;
    
    for (int i = 0; i < t; ++i)
    {
        cin >> nums[i];
        maxNum = max(maxNum, nums[i]);
    }

    vector<long long> dp(maxNum + 1, 0);
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4;

    for (int i = 4; i < maxNum + 1; ++i)
    {
        dp[i] = (dp[i - 3] + dp[i - 2] + dp[i - 1]) % 1000000009;
    }

    for (int i = 0; i < t; ++i)
    {
        cout << dp[nums[i]] << "\n";
    }
    
    return 0;
}
