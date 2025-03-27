#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n = 0, m = 0;
    
    cin >> n >> m;

    vector<vector<int>> snail(n + 2, vector<int>(n + 2, -1));
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            snail[i][j] = 0;
        }
    }

    vector<pair<int, int>> direction = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int currentDirectionIndex = 0;

    int numValue = n * n;
    int y = 1, x = 1, answerY = 0, answerX = 0;

    while (numValue > 0)
    {
        if (numValue == m)
        {
            answerY = y;
            answerX = x;
        }
        
        snail[y][x] = numValue;

        pair<int, int> currentDirection = direction[currentDirectionIndex];
        if (snail[y + currentDirection.first][x + currentDirection.second] == 0)
        {
            y += currentDirection.first;
            x += currentDirection.second;
        }
        else
        {
            currentDirectionIndex++;
            if (currentDirectionIndex == static_cast<int>(direction.size()))
            {
                currentDirectionIndex = 0;
            }

            pair<int, int> newDirection = direction[currentDirectionIndex];
            y += newDirection.first;
            x += newDirection.second;
        }
        
        numValue--;
    }

    for (int i = 1; i < n + 1; ++i)
    {
        for (int j = 1; j < n + 1; ++j)
        {
            cout << snail[i][j] << " ";
        }
        
        cout << "\n";
    }

    cout << answerY << " " << answerX << "\n";
    
    return 0;
}
