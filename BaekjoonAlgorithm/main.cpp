#include <iostream>
#include <vector>
using namespace std;

void TopDown(vector<int>& dp, vector<vector<int>>& employees, const int emplyee)
{
    for (const auto& root : employees[emplyee])
    {
        dp[root] += dp[emplyee];
        TopDown(dp, employees, root);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> employees(n + 1);
    vector<int> dp(n + 1, 0);
    for (int i = 1; i <= n; ++i)
    {
        int boss;
        cin >> boss;
        if (boss == -1)
        {
            continue;
        }
        
        employees[boss].push_back(i);
    }

    vector<int> weights(m + 1);
    for (int i = 1; i <= m; ++i)
    {
        int employee;
        int w;
        cin >> employee >> w;
        dp[employee] += w;
    }

    TopDown(dp, employees, 1);

    for (int i = 1; i <= n; ++i)
    {
        cout << dp[i] << " ";
    }
    
    cout << "\n";

    return 0;
}
