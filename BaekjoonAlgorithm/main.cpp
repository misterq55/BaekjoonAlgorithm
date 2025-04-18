#include <iostream>
#include <vector>
using namespace std;

class Robot
{
public:
    Robot() {}
    ~Robot() {}

public:
    void SetUpInitialInfo(const int r, const int c, const int d)
    {
        Pos.first = r;
        Pos.second = c;
        DirIndex = d;
    }
    
    void SetUpRoomInfo(const int n, const int m, vector<vector<int>>&& room)
    {
        Row = n;
        Col = m;
        Room = room;
    }

    void StartClean()
    {
        while (true)
        {
            const int y = Pos.first;
            const int x = Pos.second;

            // 1
            if (Room[y][x] == 0)
            {
                Room[y][x] = 2;
                CleanCount++;
            }
        
            bool bisClean = true;
            for (int i = 0; i < 4; ++i)
            {
                const pair<int, int> dir = GetDirection(i);
                const int ny = y + dir.first;
                const int nx = x + dir.second;
                if (Room[ny][nx] == 0)
                {
                    bisClean = false;
                }
            }
        
            // 2
            if (bisClean)
            {
                const pair<int, int> dir = GetDirection(DirIndex);
                const int ny = y - dir.first;
                const int nx = x - dir.second;
                if (Room[ny][nx] != 1)
                {
                    Pos.first = ny;
                    Pos.second = nx;
                    continue;
                }
                else
                {
                    break;
                }
            }
        
            // 3
            else
            {
                ChangeDirection();
                const pair<int, int> dir = GetDirection(DirIndex);
                const int ny = y + dir.first;
                const int nx = x + dir.second;
                if (Room[ny][nx] == 0)
                {
                    Pos.first = ny;
                    Pos.second = nx;
                    continue;
                }
            }
        }
    }

    int GetCleanCount()
    {
        return CleanCount;
    }

private:
    void ChangeDirection()
    {
        DirIndex = (DirIndex - 1 + 4) % 4; 
    }

    pair<int, int> GetDirection(const int index)
    {
        return Directons[index];
    }
    
private:
    pair<int, int> Pos;
    int DirIndex = 0;
    vector<pair<int, int>> Directons = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    vector<vector<int>> Room;
    int Row;
    int Col;
    int CleanCount = 0;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    Robot robot;
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> room(vector<vector<int>> (n, vector<int>(m)));

    int r, c, d;
    cin >> r >> c >> d;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> room[i][j];
        }
    }

    robot.SetUpInitialInfo(r, c, d);
    robot.SetUpRoomInfo(n, m, move(room));

    robot.StartClean();
    cout << robot.GetCleanCount() << "\n";
    
    return 0;
}
