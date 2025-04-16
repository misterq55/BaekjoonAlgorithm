#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

enum E_MoveDir
{
    Up,
    Down,
    Left,
    Right,
};

void move(vector<vector<int>> field, const int n, const E_MoveDir dir)
{
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
    vector<pair<int, int>> startPos = {{n, 1}, {1, 0}, {0, n}, {0, 1}};

    int count = n;

    const pair<int, int> start = startPos[dir];
    
    for (int i = 1; i <= n; ++i)
    {
        vector<int> line;
        for (int j = 1; j <= n; ++j)
        {
            line.push_back(field[i][j]);
        }
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

    move(field, n, E_MoveDir::Up);
    
    return 0;
}
