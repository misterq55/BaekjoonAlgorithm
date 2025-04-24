#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#include <cmath>
using namespace std;

vector<tuple<int, int, vector<int>>> preProcess(const vector<vector<pair<int, int>>>& tree, const int n, const int max_k, const int node)
{
    vector<tuple<int, int, vector<int>>> preProcessedData(n + 1, make_tuple(-1, -1, vector<int>(max_k + 1, -1)));
    queue<int> q;
    q.push(node);
    get<0>(preProcessedData[node]) = 0;
    get<1>(preProcessedData[node]) = 0;
    get<2>(preProcessedData[node])[0] = node;

    while (!q.empty())
    {
        const int u = q.front();
        q.pop();
        const vector<pair<int, int>>& adj = tree[u];

        for (const auto edge : adj)
        {
            const int v = edge.first;
            const int distance = get<1>(preProcessedData[v]);
            if (distance == -1)
            {
                get<0>(preProcessedData[v]) = get<0>(preProcessedData[u]) + 1;
                get<1>(preProcessedData[v]) = get<1>(preProcessedData[u]) + edge.second;
                get<2>(preProcessedData[v])[0] = u;
                q.push(v);
            }
        }
    }

    return preProcessedData;
}

void preProcessBinaryLifting(vector<tuple<int, int, vector<int>>>& preProcessedData, const int n, const int max_k)
{
    for (int k = 1; k <= max_k; ++k)
    {
        for (int i = 1; i <= n; ++i)
        {
            vector<int>& parent = get<2>(preProcessedData[i]);
            if (parent[k - 1] != -1)
            {
                parent[k] = get<2>(preProcessedData[parent[k - 1]])[k - 1];
            }
        }
    }
}

int findLCA(const vector<tuple<int, int, vector<int>>>& preProcessedData, const int max_k, int u,  int v)
{
    if (get<0>(preProcessedData[u]) < get<0>(preProcessedData[v]))
    {
        swap(u, v);
    }

    for (int k = max_k; k >= 0; k--)
    {
        if (get<0>(preProcessedData[u]) - get<0>(preProcessedData[v]) >= (1 << k))
        {
            u = get<2>(preProcessedData[u])[k];
        }
    }
    
    if (u == v)
    {
        return u;
    }

    for (int k = max_k; k >= 0; k--)
    {
        if (get<2>(preProcessedData[u])[k] != -1 && get<2>(preProcessedData[u])[k] != get<2>(preProcessedData[v])[k])
        {
            u = get<2>(preProcessedData[u])[k];
            v = get<2>(preProcessedData[v])[k];
        }
    }

    return get<2>(preProcessedData[u])[0];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, max_k;
    cin >> n;
    max_k = static_cast<int>(ceil(log2(n)));

    vector<vector<pair<int, int>>> tree(n + 1);

    for (int i = 1; i <= n - 1; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;

        tree[u].push_back(make_pair(v, w));
        tree[v].push_back(make_pair(u, w));
    }

    cin >> m;

    vector<tuple<int, int, vector<int>>> preProcessedData = preProcess(tree, n, max_k, 1);
    preProcessBinaryLifting(preProcessedData, n, max_k);
    
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        cin >> u >> v;

        const int lca = findLCA(preProcessedData, max_k, u, v);
        cout << get<1>(preProcessedData[u]) + get<1>(preProcessedData[v]) - 2 * get<1>(preProcessedData[lca]) << "\n";
    }
    
    return 0;
}
