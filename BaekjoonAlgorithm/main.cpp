#include <iostream>
#include <queue>
#include <vector>
using namespace std;

static const int INF = static_cast<int>(1e9);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n + 1);
    vector<int> distances(n + 1, INF);
    vector<int> parents(n + 1, -1);

    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({w, v});
    }

    int start, end;
    cin >> start >> end;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    pq.push({0, start});
    distances[start] = 0;
    
    while (!pq.empty())
    {
        const pair<int, int> curr = pq.top();
        pq.pop();

        const int u = curr.second;
        const int cost = curr.first;

        if (distances[u] < cost)
        {
            continue;
        }

        for (const pair<int, int>& node : graph[u])
        {
            const int w = node.first;
            const int v = node.second;

            if (distances[v] > distances[u] + w)
            {
                parents[v] = u;
                distances[v] = distances[u] + w;
                pq.push({distances[v], v});
            }
        }
    }

    cout << distances[end] << "\n";

    int count = 0;
    int index = end;
    vector<int> cities;
    while (index != start)
    {
        ++count;
        cities.push_back(index);
        index = parents[index];
    }

    ++count;
    cities.push_back(start);

    cout << count << "\n";
    
    const int size = static_cast<int>(cities.size());
    for (int i = size - 1; i >= 0; --i)
    {
        cout << cities[i] << " ";
    }
    cout << "\n";
    
    return 0;
}
