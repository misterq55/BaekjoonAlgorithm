#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> dp(100001, 0);

    for (int i = 0; i < n; ++i)
    {
        int w, v;
        cin >> w >> v;

        dp[w] = max(dp[w], v);
    }

    for (int i = 0; i < k; ++i)
    {
        if (dp[i] != 0)
        {
            
        }
    }

    cout << dp[k] << "\n";
    
    return 0;
}
