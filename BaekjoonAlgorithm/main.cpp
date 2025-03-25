#include <iostream>
#include <queue>
#include <vector>
using namespace std;

bool zeroCheck(const int& m, const int& n, const vector<vector<int>>& tomatoField)
{
    bool isZero = true;
    for (int i = 1; i < m + 1; ++i)
    {
        for (int j = 1; j < n + 1; ++j)
        {
            if (tomatoField[i][j] == 0)
            {
                isZero = false;
                break;
            }
        }
    }

    return isZero;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n = 0, m = 0;

    cin >> n >> m;
    cin.ignore();

    vector<vector<int>> tomatoField(m + 2, vector<int>(n + 2, -1));
    vector<vector<int>> maxDay(m + 2, vector<int>(n + 2, -1));
        
    for (int i = 1; i < m + 1; ++i)
    {
        for (int j = 1; j < n + 1; ++j)
        {
            cin >> tomatoField[i][j];
        }
    }

    if (zeroCheck(m, n, tomatoField))
    {
        cout << 0 << "\n";
        return 0;
    }

    vector<pair<int, int>> direction = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    queue<pair<int, int>> queue;

    for (int i = 1; i < m + 1; ++i)
    {
        for (int j = 1; j < n + 1; ++j)
        {
            if (tomatoField[i][j] == 1)
            {
                queue.push({i, j});
                maxDay[i][j] = 0;
            }
        }
    }
    
    while (!queue.empty())
    {
        pair<int, int> currentPos = queue.front();
        queue.pop();
        
        for (const auto &dir : direction)
        {
            int i = currentPos.first + dir.first;
            int j = currentPos.second + dir.second;

            if (tomatoField[i][j] == 0)
            {
                queue.push({i, j});
                tomatoField[i][j] = 1;

                maxDay[i][j] = maxDay[currentPos.first][currentPos.second] + 1;
            }
        }
    }

    if (!zeroCheck(m, n, tomatoField))
    {
        cout << -1 << "\n";
        return 0;
    }

    int answer = -1;
    for (int i = 1; i < m + 1; ++i)
    {
        for (int j = 1; j < n + 1; ++j)
        {
            answer = max(maxDay[i][j] , answer);
        }
    }

    cout << answer << "\n";
    
    return 0;
}
