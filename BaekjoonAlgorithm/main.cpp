#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> field(n + 2, vector<int>(m + 2, -1));
    vector<vector<vector<int>>> distance(n + 2, vector<vector<int>>(m + 2, vector<int>(2, -1)));

    for (int i = 1; i <= n; ++i)
    {
        string s;
        cin >> s;
        
        for (int j = 1; j <= m; ++j)
        {
            field[i][j] = s[j - 1] - '0';
        }
    }

    vector<pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, };
    queue<tuple<int, int, int>> q;

    q.push({1, 1, 0});
    distance[1][1][0] = 1;

    while (!q.empty())
    {
        const tuple<int, int, int> p = q.front();
        q.pop();

        const int y = get<0>(p);
        const int x = get<1>(p);
        const int broken = get<2>(p);

        for (const auto d : directions)
        {
            const int ny = y + d.first;
            const int nx = x + d.second;

            if (field[ny][nx] == 0)
            {
                if (distance[ny][nx][broken] == -1)
                {
                    distance[ny][nx][broken] = distance[y][x][broken] + 1;
                    q.push({ny, nx, broken});
                }
            }
            else if (field[ny][nx] == 1 && broken == 0 && distance[ny][nx][broken] == -1)
            {
                distance[ny][nx][1] = distance[y][x][0] + 1;
                q.push({ny, nx, 1});
            }
        }
    }

    const int dist1 = distance[n][m][0];
    const int dist2 = distance[n][m][1];

    if (dist1 == -1 && dist2 == -1) cout << -1 << "\n";
    else if (dist1 == -1) cout << dist2 << "\n";
    else if (dist2 == -1) cout << dist1 << "\n";
    else cout << min(dist1, dist2) << "\n";

    return 0;
}
