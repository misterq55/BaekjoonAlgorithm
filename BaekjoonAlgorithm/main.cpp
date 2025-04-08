#include <iostream>
#include <vector>
using namespace std;

int Find(vector<int>& parent, int value)
{
    if (parent[value] != value)
    {
        parent[value] = Find(parent, parent[value]);
    }

    return parent[value];
}

void Union(vector<int>& parent, int x, int y)
{
    x = Find(parent, x);
    y = Find(parent, y);

    if (x != y)
    {
        parent[x] = y;
    }    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> parent(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        parent[i] = i;
    }
    
    for (int i = 0; i < m; ++i)
    {
        int x, y;
        cin >> x >> y;
        Union(parent, x, y);
    }

    int root = Find(parent, 1);

    int count = 0;
    for (int i = 2; i <= n; ++i)
    {
        if (Find(parent, i) == root)
        {
            ++count;
        }
    }

    cout << count << "\n";
    
    return 0;
}
