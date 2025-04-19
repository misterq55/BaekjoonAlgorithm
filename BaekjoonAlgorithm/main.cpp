#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

struct FishInfo
{
    int Distance = 0;
    pair<int, int> Pos = {0, 0};

    FishInfo() {}
    FishInfo(int distance, pair<int, int> pos)
        : Distance(distance), Pos(pos)
    {}
};

struct CompareFish
{
    bool operator()(const FishInfo& fishA, const  FishInfo& fishB) const
    {
        if (fishA.Distance != fishB.Distance)
        {
            return fishA.Distance > fishB.Distance;
        }

        if (fishA.Pos.first != fishB.Pos.first)
        {
            return fishA.Pos.first > fishB.Pos.first;
        }

        return fishA.Pos.second > fishB.Pos.second;
    }
};

class BabyShark
{
public:
    BabyShark(){}
    
    ~BabyShark(){}

public:
    void SetPos(const int y, const int x)
    {
        Pos = {y, x};
    }

    pair<int, int> GetPos()
    {
        return Pos;
    }

    void Eat()
    {
        const FishInfo fishInfo = PreyCandidatePQ.top();
        Steps += fishInfo.Distance;
        Pos = fishInfo.Pos;

        PreyCandidatePQ = move(priority_queue<FishInfo, vector<FishInfo>, CompareFish>());
        
        EatCount++;
        if (Size == EatCount)
        {
            EatCount = 0;
            Size++;
        }
    }

    int GetCandidateSize() const
    {
        return static_cast<int>(PreyCandidatePQ.size());
    }

    void EatCandidates(FishInfo fishInfo)
    {
        PreyCandidatePQ.push(fishInfo);
    }

    int GetSize()
    {
        return Size;
    }
    
    int GetSteps()
    {
        return Steps;
    }
    
private:
    pair<int, int> Pos = {0, 0};
    int Size = 2;
    int EatCount = 0;
    priority_queue<FishInfo, vector<FishInfo>, CompareFish> PreyCandidatePQ;
    int Steps = 0;
};

void Initialize(vector<vector<int>>& field, BabyShark& BabyShark, int n)
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            cin >> field[i][j];

            if (field[i][j] == 9)
            {
                BabyShark.SetPos(i, j);
                field[i][j] = 0;
            }
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
    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    BabyShark babyShark;
    
    Initialize(field, babyShark, n);
    
    while (true)
    {
        vector<vector<int>> distances(n + 2, vector<int>(n + 2, 0));
        vector<vector<bool>> visited(n + 2, vector<bool>(n + 2, false));
        queue<pair<int, int>> q;

        q.push(babyShark.GetPos());

        while (!q.empty())
        {
            pair<int, int> pos = q.front();
            const int y = pos.first;
            const int x = pos.second;

            q.pop();
            
            for (const auto& direction : directions)
            {
                const int ny = y + direction.first;
                const int nx = x + direction.second;
                const int fishSize = field[ny][nx];

                if (fishSize > -1 && fishSize <= babyShark.GetSize() && !visited[ny][nx])
                {
                    visited[ny][nx] = true;
                    distances[ny][nx] = distances[y][x] + 1;
                    q.push({ny, nx});

                    if (fishSize > 0 && fishSize < babyShark.GetSize())
                    {
                        FishInfo fish(distances[ny][nx], {ny, nx});
                        babyShark.EatCandidates(fish);
                    }
                }
            }
        }

        if (babyShark.GetCandidateSize() <= 0)
        {
            break;
        }

        babyShark.Eat();
        const int by = babyShark.GetPos().first;
        const int bx = babyShark.GetPos().second;

        field[by][bx] = 0;
    }
    
    cout << babyShark.GetSteps() << "\n";

    return 0;
}
