#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

class CEgg
{
public:
    CEgg() {}
    CEgg(const int durability, const int weight)
        : Durability(durability), Weight(weight)
    {}
    ~CEgg() {}

public:
    bool IsBroken() const { return bIsBroken; }

    friend void CrashEggs(CEgg&, CEgg& );
    friend void RestoreEggs(CEgg&, CEgg& );

private:
    int Durability = 0;
    int Weight = 0;
    bool bIsBroken = false;
};

void CrashEggs(CEgg& egg1, CEgg& egg2)
{
    egg1.Durability -= egg2.Weight;
    egg2.Durability -= egg1.Weight;

    if (egg1.Durability <= 0)
    {
        egg1.bIsBroken = true;
    }

    if (egg2.Durability <= 0)
    {
        egg2.bIsBroken = true;
    }
}

void RestoreEggs(CEgg& egg1, CEgg& egg2)
{
    egg1.Durability += egg2.Weight;
    egg2.Durability += egg1.Weight;

    if (egg1.Durability > 0)
    {
        egg1.bIsBroken = false;
    }

    if (egg2.Durability > 0)
    {
        egg2.bIsBroken = false;
    }
}

int CalcCounter(const vector<CEgg>& eggs)
{
    int counter = 0;
    for (const CEgg& egg : eggs)
    {
        if (egg.IsBroken())
        {
            counter++;
        }
    }
    
    return counter;
}

void BackTrack(vector<CEgg>& eggs, const int maxLevel, int& count, const int index)
{
    if (index == maxLevel)
    {
        count = max(count, CalcCounter(eggs));
        
        return;
    }

    if (eggs[index].IsBroken())
    {
        return BackTrack(eggs, maxLevel, count, index + 1);
    }

    bool hasTarget = false;
    
    for (int i = 0; i < maxLevel; ++i)
    {
        if (index == i || eggs[i].IsBroken())
        {
            continue;
        }

        hasTarget = true;
        
        CrashEggs(eggs[index], eggs[i]);
        BackTrack(eggs, maxLevel, count, index + 1);
        RestoreEggs(eggs[index], eggs[i]);
    }

    if (!hasTarget)
    {
        return BackTrack(eggs, maxLevel, count, index + 1);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<CEgg> eggs;
    
    for (int i = 0; i < n; i++)
    {
        int s, w;
        cin >> s >> w;
        
        eggs.emplace_back(s, w);
    }

    int count = 0;

    BackTrack(eggs, n, count, 0);

    cout << count << "\n";
    
    return 0;
}
