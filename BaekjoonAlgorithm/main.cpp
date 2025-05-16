#include <iostream>
#include <vector>
using namespace std;

static int INF = static_cast<int>(1e9);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, r;
    cin >> n >> m >> r;
    vector<int> items(n + 1, 0);
    vector<vector<int>> distances(n + 1, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= n; ++i)
    {
        cin >> items[i];
    }

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (i != j)
            {
                distances[i][j] = INF;
            }
        }
    }
    
    for (int i = 0; i < r; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        distances[u][v] = distances[v][u] = w;
    }

    for (int k = 1; k <= n; ++k)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                distances[i][j] = min(distances[i][j], distances[i][k] + distances[k][j]);
            }
        }
    }

    int maxValue = 0;
    for (int i = 1; i <= n; ++i)
    {
        int itemsSum = 0;
        for (int j = 1; j <= n; ++j)
        {
            if (distances[i][j] <= m)
            {
                itemsSum += items[j];
            }
        }
        maxValue = max(maxValue, itemsSum);
    }

    cout << maxValue << "\n";
    
    return 0;
}
