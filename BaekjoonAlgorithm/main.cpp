#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct GraphCompare
{
    bool operator()(const vector<int>& p1, const vector<int>& p2)
    {
        return p1.size() > p2.size();
    }
};

int dfs(vector<pair<int, vector<int>>>& graph, vector<bool>& visited, const int index)
{
    visited[index] = true;
    graph[index].first = 1;
    
    for (const auto& v : graph[index].second)
    {
        if (!visited[v])
        {
            graph[index].first += dfs(graph, visited, v);
        }
    }

    return graph[index].first;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<pair<int, vector<int>>> graph(n + 1);
    vector<int> result(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        graph[v].second.push_back(u);
    }

    int maxValue = 0;
    for (int i = 1; i <= n; ++i)
    {
        vector<bool> visited(n + 1, false);
        result[i] = dfs(graph, visited, i);
        maxValue = max(maxValue, result[i]);
    }

    for (int i = 1; i <= n; ++i)
    {
        if (result[i] == maxValue)
        {
            cout << i << " ";
        }
    }

    cout << "\n";
    
    return 0;
}
