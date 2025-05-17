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
        parent.resize(n);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }
    
    int Find(int p)
    {
        if (p != parent[p])
        {
            parent[p] = Find(p);
        }
        return parent[p];
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

    int ans = 0;
    
    int n, m;
    cin >> n >> m;

    int truth;
    cin >> truth;

    if (truth == 0)
    {
        cout << m << "\n";
        return 0;
    }
    
    vector<int> truthArr;

    for (int i = 0; i < truth; ++i)
    {
        int truthNum;
        cin >> truthNum;
        truthArr.push_back(truthNum);
    }

    for (int i = 0; i < m; ++i)
    {
        int partyPeopleNum;
        cin >> partyPeopleNum;

        for (int j = 0; j < partyPeopleNum; ++j)
        {
            int partyPeopleNum;
            cin >> partyPeopleNum;

            if (find(truthArr.begin(), truthArr.end(), partyPeopleNum) != truthArr.end())
            {
                ans++;
            }
        }
    }

    cout << m - ans << "\n";
    
    return 0;
}
