#include <iostream>
#include <queue>
#include <vector>
using namespace std;

pair<int, int> findLongestDistance(const vector<vector<pair<int, int>>>& tree, const int n, const int node)
{
    vector<int> distances(n + 1, -1);
    queue<int> q;
    q.push(node);
    distances[node] = 0;

    while (!q.empty())
    {
        const int u = q.front();
        q.pop();
        const vector<pair<int, int>> &adj = tree[u];

        for (const auto edge : adj)
        {
            const int v = edge.first;
            if (distances[v] == -1)
            {
                distances[v] = distances[u] + edge.second;
                q.push(v);
            }
        }
    }

    pair<int, int> maxDistNode = {0, 0};
    for (int i = 1; i <= n; ++i)
    {
        if (maxDistNode.second < distances[i])
        {
            maxDistNode.second = distances[i];
            maxDistNode.first = i;
        }
    }

    return move(maxDistNode);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<vector<pair<int, int>>> tree(n + 1);
    

    for (int i = 1; i <= n - 1; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;

        tree[u].push_back(make_pair(v, w));
        tree[v].push_back(make_pair(u, w));
    }

    pair<int, int> n1 = findLongestDistance(tree, n, 1);
    pair<int, int> n2 = findLongestDistance(tree, n, n1.first);

    cout << n2.second << "\n";
    
    return 0;
}
