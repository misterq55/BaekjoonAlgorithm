#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int INF = 2147483647;

int Dijkstra(const vector<vector<pair<int, int>>>& graph,const int n, const int start, const int end)
{
    vector<int> dist(n + 1, INF);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<>> pq;

    pq.push(make_pair(0, start));
    while (!pq.empty())
    {
        const int cost = pq.top().first;
        const int u = pq.top().second;
        pq.pop();

        if (dist[u] < cost) continue;

        for (const auto &pair : graph[u])
        {
            const int w = pair.first;
            const int v = pair.second;

            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    return dist[end];
}

int CheckInfinity(const int startValue, const int centerValue, const int endValue)
{
    return (startValue == INF || centerValue == INF || endValue == INF) ? INF : startValue + centerValue + endValue;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n = 0, m = 0, v1 = 0, v2 = 0;
    
    
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n + 1, vector<pair<int, int>>());
    
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(w, v);
        graph[v].emplace_back(w, u);
    }

    cin >> v1 >> v2;

    int value1 = CheckInfinity(Dijkstra(graph, n, 1, v1), Dijkstra(graph, n, v1, v2), Dijkstra(graph, n, v2, n));
    int value2 = CheckInfinity(Dijkstra(graph, n, 1, v2), Dijkstra(graph, n, v2, v1), Dijkstra(graph, n, v1, n));

    int ans = value1 == INF ? -1 : min(value1, value2);
    
    cout << ans << "\n";
    
    return 0;
}
