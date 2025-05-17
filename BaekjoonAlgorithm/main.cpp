#include <iostream>
#include <vector>
using namespace std;

class CUnionFind
{
public:
    CUnionFind() {}
    ~CUnionFind() {}

public:
    void Initialize(int n)
    {
        parent.resize(n + 1);
        for (int i = 1; i <= n; i++)
        {
            parent[i] = i;
        }
    }
    
    int Find(int p)
    {
        if  (parent[p] != p)
        {
            return Find(parent[p]);
        }

        return p;
    }

    void Union(int p, int q)
    {
        p = Find(p);
        q = Find(q);

        if (p != q)
        {
            parent[p] = q;
        }
    }

private:
    vector<int> parent;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    CUnionFind unionFind;
    int ans = 0;
    
    int n, m;
    cin >> n >> m;

    unionFind.Initialize(n);
    
    int truth;
    cin >> truth;

    if (truth == 0)
    {
        cout << m << "\n";
        return 0;
    }
    
    vector<int> truthArr;

    int prevTruthNum = 0;
    for (int i = 0; i < truth; ++i)
    {
        int truthNum;
        cin >> truthNum;

        if (i != 0)
        {
            unionFind.Union(prevTruthNum, truthNum);
        }
        
        prevTruthNum = truthNum;
    }

    for (int i = 0; i < m; ++i)
    {
        int party;
        cin >> party;

        int prevPartyNum = 0;
        for (int j = 0; j < party; ++j)
        {
            int partyNum;
            cin >> partyNum;

            if (partyNum != -1)
            {
                unionFind.Union(prevPartyNum, partyNum);
            }

            prevPartyNum = partyNum;
        }
    }

    cout << ans << "\n";
    
    return 0;
}
