#include <iostream>
#include <queue>
#include <vector>
using namespace std;

bool checkChunk(const int i, const int j, const char find, const vector<vector<char>>& map, vector<vector<bool>>& visited)
{
    if (visited[i][j] || map[i][j] != find)
    {
        return false;
    }
    
    vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    queue<pair<int, int>> q;
    q.push(make_pair(i, j));
    visited[i][j] = true;

    while (!q.empty())
    {
        pair<int, int> current = q.front();
        const int y = current.first;
        const int x = current.second;

        for (const auto& dir : dirs)
        {
            const int ny = y + dir.first;
            const int nx = x + dir.second;
            if (!visited[ny][nx] && map[ny][nx] == find)
            {
                visited[ny][nx] = true;
                q.push(make_pair(ny, nx));
            }
        }
                
        q.pop();
    }
    
    return true;
}

void changeColor(const int i, const int j, const char fromColor, const char toColor, vector<vector<char>>& map)
{
    if (map[i][j] != fromColor)
    {
        return;
    }
    
    vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    queue<pair<int, int>> q;
    q.push(make_pair(i, j));
    map[i][j] = toColor;

    while (!q.empty())
    {
        pair<int, int> current = q.front();
        const int y = current.first;
        const int x = current.second;

        for (const auto& dir : dirs)
        {
            const int ny = y + dir.first;
            const int nx = x + dir.second;
            if (map[ny][nx] == fromColor)
            {
                map[ny][nx] = toColor;
                q.push(make_pair(ny, nx));
            }
        }
                
        q.pop();
    }
}

int countChunk(const int n, const vector<vector<char>>& map, vector<vector<bool>>& visited)
{
    int count = 0;
    
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (checkChunk(i, j, 'R', map, visited)) ++count;
            if (checkChunk(i, j, 'B', map, visited)) ++count;
            if (checkChunk(i, j, 'G', map, visited)) ++count;
        }
    }

    return count;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<vector<char>> map(n + 2, vector<char>(n + 2, -1));
    vector<vector<bool>> visited(n + 2, vector<bool>(n + 2, false));
    
    for (int i = 1; i <= n; ++i)
    {
        string s;
        cin >> s;

        for (int j = 1; j <= n; ++j)
        {
            map[i][j] = s[j - 1];
        }
    }

    int count = countChunk(n, map, visited);

    cout << count << " ";

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            changeColor(i, j, 'R', 'G', map);
            visited[i][j] = false;
        }
    }

    count = countChunk(n, map, visited);

    cout << count << "\n";
    
    return 0;
}
