#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<int> nums(n);
    vector<int> dp(n + 1, 1);

    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= i; ++j)
        {
            if (nums[j - 1] < nums[i - 1])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    int masLength = 0;
    for (int i = 1; i <= n; ++i)
    {
        masLength = max(masLength, dp[i]);
    }

    cout << masLength << "\n";
    
    return 0;
}
