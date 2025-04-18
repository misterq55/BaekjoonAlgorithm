#include <iostream>
#include <map>
#include <vector>
using namespace std;

class FireBall
{
public:
    FireBall() {}
    FireBall(const int n, const int r, const int c, const int m, const int s, const int d)
        : MapSize(n), Pos({r, c}), Mass(m), Speed(s), DirIndex(d)
    {}
    ~FireBall() {}

public:
    void Move()
    {
        const pair<int, int> dir = Directions[DirIndex];
        Pos.second = (Pos.second + dir.second * (Speed % MapSize) + MapSize) % MapSize;
        Pos.first = (Pos.first + dir.first * (Speed % MapSize) + MapSize) % MapSize;
    }

    pair<int, int> GetPos() const
    {
        return Pos;
    }

    FireBall& operator+=(const FireBall& b)
    {
        Mass += b.Mass;
        Speed += b.Speed;

        return *this;
    }

    int GetMass() const
    {
        return Mass;
    }

    int GetSpeed() const
    {
        return Speed;
    }
    
    int GetDirIndex() const
    {
        return DirIndex;
    }
    
private:
    pair<int, int> Pos = {0, 0};
    int MapSize = 0;
    int Mass = 0;
    int DirIndex = 0;
    int Speed = 0;
    vector<pair<int, int>> Directions = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> field(n, vector<int>(n));
    vector<FireBall> fireballs;
    
    for (int i = 0; i < m; ++i)
    {
        int r, c, ms, d, s;
        cin >> r >> c >> ms >> s >> d;

        fireballs.emplace_back(n, r, c, ms, s, d);
    }

    for (int i = 0; i < k; ++i)
    {
        // 움직임
        map<pair<int, int>, vector<int>> collisionMap;
        const int size = static_cast<int>(fireballs.size());
        for (int j = 0; j < size; ++j)
        {
            fireballs[j].Move();
            const pair<int, int> pos = fireballs[j].GetPos();
            collisionMap[pos].emplace_back(j);
        }

        vector<FireBall> newFireballs;
        // 충돌 확인 후 융합
        for (auto collision : collisionMap)
        {
            pair<int, int> pos = collision.first;
            vector<int> collisionIndice = collision.second;
            const int collisionSize = static_cast<int>(collisionIndice.size());
            if (collisionSize == 0)
            {
                continue;
            }
            else if (collisionSize == 1)
            {
                newFireballs.emplace_back(fireballs[collisionIndice[0]]);
            }
            else
            {
                bool bDirCheckFalg = true;
                for (int j = 1; j < collisionSize; ++j)
                {
                    fireballs[collisionIndice[0]] += fireballs[collisionIndice[j]];
                    if (fireballs[collisionIndice[j]].GetDirIndex() % 2 != fireballs[collisionIndice[j - 1]].GetDirIndex() % 2)
                    {
                        bDirCheckFalg = false;
                    }
                }

                // 융합된 파이어볼 분할
                int newR = pos.first;
                int newC = pos.second;
                int newMass = fireballs[collisionIndice[0]].GetMass() / 5;
                int newSpeed = fireballs[collisionIndice[0]].GetSpeed() / collisionSize;
                int newDirIndex = bDirCheckFalg ? 0 : 1;
                for (int j = 0; j < 4; ++j)
                {
                    if (newMass != 0)
                    {
                        newFireballs.emplace_back(n, newR,newC,newMass,newSpeed,j * 2 + newDirIndex);
                    }
                }
            }
        }

        collisionMap.clear();
        fireballs = move(newFireballs);
    }

    const int size = static_cast<int>(fireballs.size());
    for (int i = 1; i < size; ++i)
    {
        fireballs[0] += fireballs[i];
    }

    const int ans = fireballs.empty() ? 0 : fireballs[0].GetMass();
    cout << ans << "\n";

    return 0;
}
