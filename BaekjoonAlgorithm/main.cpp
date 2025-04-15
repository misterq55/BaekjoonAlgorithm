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
    int curDirIndex = 0;
    vector<pair<int, char>> commands;
    pair<int, int> snakeHead = {1, 1};
    pair<int, int> snakeTail = {1, 1};

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            field[i][j] = 0;
        }
    }

    field[snakeHead.first][snakeHead.second] = 1;

    for (int i = 1; i <= k; ++i)
    {
        int row, col;
        cin >> row >> col;
        field[row][col] = 2;
    }

    cin >> l;

    commands = vector<pair<int, char>>(l + 1);

    for (int i = 1; i <= l; ++i)
    {
        cin >> commands[i].first >> commands[i].second;
    }

    // move
    bool gameOver = false;
    int count = 0;
    int currCommandIndex = 1;

    while (!gameOver)
    {
        int seconds = commands[currCommandIndex].first;
        char directionCommand = commands[currCommandIndex].second;

        while (true)
        {
            count++;
            const pair<int, int>& direction = directions[curDirIndex];

            if (field[snakeHead.first + direction.first][snakeHead.second + direction.second] == 0)
            {   
                field[snakeTail.first + direction.first][snakeTail.second + direction.second] = 1;
                field[snakeTail.first][snakeTail.second] = 0;
                snakeTail.first += direction.first;
                snakeTail.second += direction.second;
            }
            else if (field[snakeHead.first + direction.first][snakeHead.second + direction.second] == 1
                || field[snakeHead.first + direction.first][snakeHead.second + direction.second] == -1)
            {
                gameOver = true;
                break;
            }

            field[snakeHead.first + direction.first][snakeHead.second + direction.second] = 1;
            snakeHead.first += direction.first;
            snakeHead.second += direction.second;
            
            seconds--;
            if (seconds == 0)
            {
                switch (directionCommand)
                {
                case 'D':
                    curDirIndex = (curDirIndex + 1 + 4) % 4; 
                    break;
                case 'L':
                    curDirIndex = (curDirIndex - 1 + 4) % 4;
                    break;
                default:
                    break;
                }
                currCommandIndex++;
                break;
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
