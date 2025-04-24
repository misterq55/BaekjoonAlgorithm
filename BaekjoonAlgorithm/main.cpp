#include <iostream>
#include <vector>
using namespace std;

void generateRootedTree(vector<vector<int>>& adj, vector<vector<int>>& tree, vector<bool>& visited, const int u)
{
    visited[u] = true;

    for (int v : adj[u])
    {
        if (!visited[v])
        {
            tree[u].push_back(v);
            generateRootedTree(adj, tree, visited, v);
        }
    }
}

void generateDP(vector<vector<int>>& tree, vector<int>& dp, const int r)
{
    dp[r] = 1;

    vector<int>& children = tree[r];

    if (children.empty())
    {
        return;
    }
    
    for (int child : children)
    {
        generateDP(tree, dp, child);
        dp[r] += dp[child];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, r, q;
    cin >> n >> r >> q;

    vector<vector<int>> adj(n + 1);
    vector<vector<int>> tree(n + 1);
    vector<int> dp(n + 1, 0);
    vector<bool> visited(n + 1, false);
    
    for (int i = 1; i <= n - 1; ++i)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    generateRootedTree(adj, tree, visited, r);
    generateDP(tree, dp, r);

    for (int i = 1; i <= q; ++i)
    {
        int u;
        cin >> u;

        cout << dp[u] << "\n";
    }
    
    return 0;
}
