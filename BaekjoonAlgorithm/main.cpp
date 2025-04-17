#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

enum E_MoveDir
{
    Up,
    Down,
    Left,
    Right,
};

int move(vector<vector<int>>& field, const int n, const E_MoveDir dir)
{
    int maxValue = 0;
    const bool bisHorizontal = dir >= 2;
    const bool bisPrograded = dir % 2 == 0;

    for (int i = 1; i <= n; ++i)
    {
        vector<int> line;
        for (int j = 1; j <= n; ++j)
        {
            int y = i;
            int x = j;

            if (!bisHorizontal)
            {
                y = j;
                x = i;
            }

            if (field[y][x] != 0)
            {
                line.push_back(field[y][x]);
            }
        }

        if (!bisPrograded)
        {
            reverse(line.begin(), line.end());    
        }
        
        vector<int> merged;
        for (int j = 0; j < static_cast<int>(line.size()); ++j)
        {
            if (j + 1 < static_cast<int>(line.size()) && line[j] == line[j + 1])
            {
                merged.push_back(line[j] * 2);
                ++j;
            }
            else
            {
                merged.push_back(line[j]);
            }
        }

        merged.resize(n, 0);
        
        for (int j = 1; j <= n; ++j)
        {
            int y = i;
            int x = j;

            int index = bisPrograded ? j - 1 : n - j;
            
            if (!bisHorizontal)
            {
                y = j;
                x = i;
            }

            field[y][x] = merged[index];
            maxValue = max(maxValue, field[y][x]);
        }
    }

    return maxValue;
}

void dfs(vector<vector<int>> field, int& maxValue, int depth, const int n)
{
    if (n == 1)
    {
        maxValue = field[1][1];
        return;
    }
    
    if (depth == 0)
    {
        return;
    }

    for (int i = 0; i < 4; ++i)
    {
        vector<vector<int>> copiedField = field;
        int curMax = move(copiedField, n, static_cast<E_MoveDir>(i));

        if (copiedField == field)
        {
            continue;
        }

        maxValue = max(maxValue, curMax);
        dfs(copiedField, maxValue, depth - 1, n);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> field(n + 2, vector<int>(n + 2, -1));
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            cin >> field[i][j];
        }
    }

    int depth = 5;
    int maxValue = 0;
    dfs(field, maxValue, depth, n);
    
    cout << maxValue << "\n";
    
    return 0;
}
