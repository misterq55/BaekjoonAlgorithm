#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    
    vector<vector<pair<int, int>>> tree(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        int index;
        cin >> index;
        
        while (true)
        {
            int node;
            cin >> node;
            
            if (node == -1)
            {
                break;
            }

            int weight;
            cin >> weight;

            tree[index].push_back(make_pair(weight, node));
        }
    }
    
    vector<pair<int, int>> data = {{0, 1}};
    vector<int> distances;
    int ans = 0;

    for (int i = 0; i < 2; ++i)
    {
        priority_queue<pair<int, int>> pq;
        distances = move(vector<int>(n + 1, -1));
    
        pq.push(data[i]);
        distances[data[i].second] = 0;
        
        while (!pq.empty())
        {
            const pair<int, int> curr = pq.top();
            pq.pop();

            for (const pair<int, int>& node : tree[curr.second])
            {
                if (distances[node.second] == -1)
                {
                    distances[node.second] = distances[curr.second] + node.first;
                    pq.push(node);
                }
            }
        }

        int maxDistIndex = 0;
        int maxDist = 0;
        for (int j = 1; j <= n; ++j)
        {
            const int distance = distances[j];
            if (distance > maxDist)
            {
                maxDist = distance;
                maxDistIndex = j;
            }
        }

        ans = maxDist;

        data.push_back({0, maxDistIndex});
    }

    cout << ans << "\n";
    
    return 0;
}
