#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n = 0, m = 0, start = 0;
    
    cin >> n >> m >> start;

    const int INF = 2147483647;
    vector<vector<pair<int, int>>> graph(n + 1);
    vector<int> distances(n + 1, INF);
    
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(make_pair(w, v));
    }

    distances[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({0,start});
    
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        for (const auto& pair : graph[u])
        {
            int v = pair.second;
            int w = pair.first;

            if (distances[v] > distances[u] + w)
            {
                distances[v] = distances[u] + w;
                pq.push({distances[v], v});
            }
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        if (distances[i] == INF)
        {
            cout << "INF" << "\n";
        }
        else
        {
            cout << distances[i] << "\n";    
        }
    }
    
    return 0;
}
