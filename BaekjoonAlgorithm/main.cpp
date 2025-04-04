#include <iostream>
#include <queue>
#include <vector>
using namespace std;

static const int INF = 2147483647;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> map(n + 2, vector<int>(m + 2, INF));
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    vector<pair<int, int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    vector<vector<pair<int, vector<pair<int, int>>>>> graphs(n + 2, vector<pair<int, vector<pair<int, int>>>>(m + 2)); 

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            cin >> map[i][j];
        }
    }

    dp[1][1] = 1;
    
    graphs[1][1].first = 0;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            for (const auto& dir : dirs)
            {
                const int ny = i + dir.first;
                const int nx = j + dir.second;

                if (map[i][j] > map[ny][nx])
                {
                    graphs[i][j].second.push_back({ny, nx});
                    graphs[ny][nx].first++;
                }
            }
        }
    }

    queue<pair<int, int>> q;
    
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (graphs[i][j].first == 0)
            {
                q.push({i, j});
            }
        }
    }

    while (!q.empty())
    {
        const int y = q.front().first;
        const int x = q.front().second;
        
        q.pop();

        for (const auto& coord : graphs[y][x].second)
        {
            const int ny = coord.first;
            const int nx = coord.second;
            graphs[ny][nx].first--;

            if (graphs[ny][nx].first == 0)
            {
                q.push({ny, nx});
            }
            
            dp[ny][nx] += dp[y][x];
        }
    }
    
    cout << dp[n][m] << "\n";
    
    return 0;
}
