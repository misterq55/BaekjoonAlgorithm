#include <iostream>
#include <map>
#include <vector>
using namespace std;

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

    void Eat()
    {
        EatCount++;
        if (Size == EatCount)
        {
            Size++;
        }
    }

    int GetCandidateSize() const
    {
        return static_cast<int>(PreyCandiates.size());
    }

private:
    int Size = 2;
    int EatCount = 0;
    pair<int, int> Pos = {0, 0};
    vector<pair<int, int>> PreyCandiates;
};

void Input(vector<vector<int>>& field, int n)
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            cin >> field[i][j];
        }
    }
}

void Output(vector<vector<int>>& field, int n)
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            cout << field[i][j] << " ";
        }
        cout << "\n";
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
    vector<vector<int>> distances(n + 2, vector<int>(n + 2, -1));
    BabyShark babyShark;
    
    Input(field, n);

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (field[i][j] == 9)
            {
                babyShark.SetPos(i, j);
            }
        }
    }

    return 0;
}
