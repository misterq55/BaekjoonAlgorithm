#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<int> r(n + 1, 0);
    vector<int> g(n + 1, 0);
    vector<int> b(n + 1, 0);
    vector<vector<int>> dp(n + 1, vector<int>(3 + 1, 0));

    for (int i = 1; i <= n; ++i)
    {
        cin >> r[i] >> g[i] >> b[i];
    }
    
    dp[1][1] = r[1];
    dp[1][2] = g[1];
    dp[1][3] = b[1];
    
    for (int i = 2; i <= n; i++)
    {
        dp[i][1] = r[i] + min(dp[i - 1][2], dp[i - 1][3]);
        dp[i][2] = g[i] + min(dp[i - 1][1], dp[i - 1][3]);
        dp[i][3] = b[i] + min(dp[i - 1][1], dp[i - 1][2]);
    }

    cout << min(min(dp[n][1], dp[n][2]), dp[n][3]) << "\n";
    
    return 0;
}
