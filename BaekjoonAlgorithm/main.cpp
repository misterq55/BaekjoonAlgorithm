#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<int> Dijkstra(const vector<vector<pair<int, int>>>& graph, const int start)
{
    const int INF = static_cast<int>(1e9);
    vector<int> distances(graph.size(), INF);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, start});
    distances[start] = 0;

    while (!pq.empty())
    {
        const pair<int, int> current = pq.top();
        pq.pop();

        const int cost = current.first;
        const int u = current.second;

        if (cost > distances[u])
        {
            continue;
        }

        for (const pair<int, int>& node : graph[u])
        {
            const int v = node.second;
            const int w = node.first;

            if (distances[v] > distances[u] + w)
            {
                distances[v] = distances[u] + w;
                pq.push(node);
            }
        }
    }

    return move(distances);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, x;
    cin >> n >> m >> x;

    vector<vector<pair<int, int>>> graph0(n + 1), graph1(n + 1);
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph0[u].push_back({w, v});
        graph1[v].push_back({w, u});
    }

    vector<int> fromX = Dijkstra(graph0, x);
    vector<int> toX = Dijkstra(graph1, x);

    int maxValue = 0;
    for (int i = 1; i <= n; ++i)
    {
        maxValue = max(maxValue, fromX[i] + toX[i]);
    }

    cout << maxValue << "\n";
    
    return 0;
}
