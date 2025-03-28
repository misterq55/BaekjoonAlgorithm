#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n = 0, m = 0;
    
    cin >> n >> m;

    vector<pair<int, vector<int>>> graphs(n + 1, pair<int, vector<int>>());
    vector<int> result;
    
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        graphs[u].second.push_back(v);
        graphs[v].first++;
    }

    queue<int> q;
    
    for (int i = 1; i <= n; ++i)
    {
        const pair<int, vector<int>>& graph = graphs[i];
        if (graph.first == 0)
        {
            q.push(i);
        }
    }

    while (!q.empty())
    {
        const int current = q.front();
        result.emplace_back(current);
        q.pop();

        for (const int next : graphs[current].second)
        {
            pair<int, vector<int>>& nextGraph = graphs[next];
            nextGraph.first--;

            if (nextGraph.first == 0)
            {
                q.push(next);
            }
        }
    }

    for (const int next : result)
    {
        cout << next << " ";
    }
    
    cout << "\n";
    
    return 0;
}
