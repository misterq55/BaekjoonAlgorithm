#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<bool> visited(n + 1, false);
    
    vector<vector<pair<int, int>>> nodes(n + 1);
    for (int i = 1; i <= m; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        nodes[a].push_back(make_pair(c, b));
        nodes[b].push_back(make_pair(c, a));
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    for (const auto& edge : nodes[1])
    {
        pq.push(edge);
    }

    visited[1] = true;
    
    int count = 0;
    int weight = 0;

    while (!pq.empty())
    {
        pair<int, int> current = pq.top();
        pq.pop();

        if (visited[current.second])
        {
            continue;
        }

        weight += current.first;
        visited[current.second] = true;
        count++;

        if (count == n - 1)
        {
            break;
        }

        for (const auto& edge : nodes[current.second])
        {
            pq.push(edge);
        }
    }

    cout << weight << "\n";
    
    return 0;
}
