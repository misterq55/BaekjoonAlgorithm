#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector<vector<int>> field;
vector<vector<bool>> visited;
vector<vector<bool>> finished;
vector<pair<int, int>> direction = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int convertInput(const char c)
{
    switch (c)
    {
    case 'U':
        return 0;
        break;
    case 'D':
        return 1;
        break;
    case 'L':
        return 2;
        break;
    case 'R':
        return 3;
        break;
    default:
        return -1;
        break;
    }
}

bool dfs(int i, int j)
{
    visited[i][j] = true;

    const pair<int, int> dir = direction[field[i][j]];
    const int y = i + dir.first;
    const int x = j + dir.second;

    bool result = false;
    
    if (!visited[y][x])
    {
        result = dfs(y, x);
    }
    else if (!finished[y][x])
    {
        result = true;
    }
    
    finished[i][j] = true;

    return result;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    field = vector<vector<int>>(n + 2, vector<int>(m + 2, -1));
    visited = vector<vector<bool>>(n + 2, vector<bool>(m + 2, false));
    finished = vector<vector<bool>>(n + 2, vector<bool>(m + 2, false));
    
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            char c;
            cin >> c;

            field[i][j] = convertInput(c);
        }
    }

    int count = 0;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (!visited[i][j])
            {
                if (dfs(i, j))
                {
                    count++;
                }
            }
        }
    }

    cout << count << "\n";

    return 0;
}
