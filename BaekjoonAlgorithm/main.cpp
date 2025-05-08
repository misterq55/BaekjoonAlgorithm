#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

void BackTrack(vector<vector<int>>& combination, vector<int>& indexes, vector<bool>& visited, const int maxLevel, const int level, const int start)
{
    if (level == maxLevel)
    {
        combination.push_back(indexes);
        return;
    }

    for (int i = start; i < 25; ++i)
    {
        if (visited[i])
        {
            continue;
        }

        visited[i] = true;
        indexes.push_back(i);
        BackTrack(combination, indexes, visited, maxLevel, level + 1, i + 1);
        indexes.pop_back();
        visited[i] = false;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    const int n = 5;

    vector<vector<char>> field(n + 2, vector<char>(n + 2, ' '));
    // vector<vector<bool>> visited(n + 2, vector<bool>(n + 2, false));
    vector<char> result;

    vector<int> indexes;
    vector<bool> visted(n * n, false);

    vector<vector<int>> combination;
    const int maxLevel = 7;
    
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            cin >> field[i][j];
        }
    }

    int count = 0;

    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    
    BackTrack(combination, indexes, visted, maxLevel, 0, 0);
    for (const auto& v : combination)
    {
        unordered_map<int, bool> indexVisited;

        queue<int> q;
        q.push(v[0]);
        indexVisited[v[0]] = true;

        int sCount = 0;
        while (!q.empty())
        {
            const int curr = q.front();
            q.pop();

            const int y = curr / n + 1;
            const int x = curr % n + 1;

            if (field[y][x] == 'S')
            {
                sCount++;
            }

            for (const auto& direction : directions)
            {
                const int ny = y + direction.first;
                const int nx = x + direction.second;

                if (field[ny][nx] == ' ')
                {
                    continue;
                }
                
                const int adj = (ny - 1) * n + nx - 1;
                if (find(v.begin(), v.end(), adj) == v.end())
                {
                    continue;    
                }
                
                if (!indexVisited[adj])
                {
                    indexVisited[adj] = true;
                    q.push(adj);
                }
            }
        }

        if (indexVisited.size() == 7 && sCount >= 4)
        {
            count++;
        }
    }
    
    cout << count << "\n";
    
    return 0;
}
