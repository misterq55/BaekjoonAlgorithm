#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, k, l;
    cin >> n >> k;

    vector<vector<int>> field(n + 2, vector<int>(n + 2, -1));
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            field[i][j] = 0;
        }
    }

    for (int i = 1; i <= k; ++i)
    {
        int row, col;
        cin >> row >> col;
        field[row][col] = 2;
    }

    cin >> l;

    int curDirIndex = 0;
    queue<pair<int, char>> commandQ;
    for (int i = 1; i <= l; ++i)
    {
        int x;
        char c;
        cin >> x >> c;
        commandQ.push({x, c});
    }

    // head start
    queue<pair<int, int>> q;
    q.push({1, 1});
    field[q.back().first][q.back().second] = 1;
    
    // move
    bool gameOver = false;
    int count = 0;

    while (!gameOver)
    {
        for (int time = 1; ; ++time)
        {
            count++;
            const pair<int, int>& direction = directions[curDirIndex];
            const pair<int, int> snakeHead = q.back();
            const pair<int, int> newPos = {snakeHead.first + direction.first, snakeHead.second + direction.second};

            if (field[newPos.first][newPos.second] == 0)
            {
                field[newPos.first][newPos.second] = 1;
                q.push(newPos);
                
                const pair<int, int> snakeTail = q.front();
                field[snakeTail.first][snakeTail.second] = 0;
                q.pop();
            }
            else if (field[newPos.first][newPos.second] == 2)
            {
                field[newPos.first][newPos.second] = 1;
                q.push(newPos);
            }
            else if (field[snakeHead.first + direction.first][snakeHead.second + direction.second] == 1
                || field[snakeHead.first + direction.first][snakeHead.second + direction.second] == -1)
            {
                gameOver = true;
                break;
            }

            if (!commandQ.empty() && commandQ.front().first == time)
            {
                char dirCommand = commandQ.front().second;
                if (dirCommand == 'D')
                    curDirIndex = (curDirIndex + 1 + 4) % 4;
                else if (dirCommand == 'L')
                    curDirIndex = (curDirIndex -1 + 4) % 4;

                commandQ.pop();
            }
        }

        if (gameOver)
        {
            break;
        }
    }

    cout << count << "\n";
    
    return 0;
}
