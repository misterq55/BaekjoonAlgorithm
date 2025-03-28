#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t = 0;

    cin >> t;

    for (int i = 0; i < t; ++i)
    {
        int n = 0, k = 0;
        cin >> n >> k;

        vector<int> delay(n + 1);
        for (int j = 1; j <= n; ++j)
        {
            cin >> delay[j];
        }
        
        vector<pair<int, vector<int>>> graph(n + 1);
        for (int j = 1; j <= k; ++j)
        {
            int x = 0, y = 0;
            cin >> x >> y;
            graph[x].second.push_back(y);
            graph[y].first++;
        }

        int w = 0;
        cin >> w;

        vector<int> constructTime(n + 1, 0);
        queue<int> q;

        for (int j = 1; j <= n; ++j)
        {
            if (graph[j].first == 0)
            {
                q.push(j);
                constructTime[j] = delay[j];
            }
        }

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            for (const int& num : graph[current].second)
            {
                constructTime[num] = max(constructTime[num], delay[num] + constructTime[current]);
                
                graph[num].first--;
                if (graph[num].first == 0)
                {
                    q.push(num);
                }
            }
        }

        cout << constructTime[w] << "\n";
    }
    
    return 0;
}
