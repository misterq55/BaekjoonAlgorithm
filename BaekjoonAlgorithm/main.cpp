#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n = 0, m = 0, start = 0, end = 0;
    const int INF = 2147483647;
    
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n + 1);
    vector<int> distance(n + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back(make_pair(w, v));
    }

    cin >> start >> end;

    distance[start] = 0;
    pq.push(make_pair(0, start));

    while (!pq.empty())
    {
        int cost = pq.top().first;
        int u = pq.top().second;

        pq.pop();

        if (distance[u] < cost)
        {
            continue;
        }
        
        for (auto& pair : graph[u])
        {
            int w = pair.first;
            int v = pair.second;
            if (distance[v] > distance[u] + w)
            {
                distance[v] = distance[u] + w;
                pq.push(make_pair(distance[v], v));
            }
        }
    }

    cout << distance[end] << "\n";
    
    return 0;
}
