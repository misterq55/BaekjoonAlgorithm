#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<pair<int, int>> lectures(n);
    for (int i = 0; i < n; ++i)
    {
        int temp;
        cin >> temp;
        cin >> lectures[i].second;
        cin >> lectures[i].first;
    }

    sort(lectures.begin(), lectures.end(), [](pair<int, int> a, pair<int, int> b)
    {
        return a.second < b.second;
    });

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push(lectures[0]);
    
    for (int i = 1; i < n; ++i)
    {
        pair<int, int> current = pq.top();
        if (current.first <= lectures[i].second)
        {
            pq.pop();
        }

        pq.push(lectures[i]);
    }

    cout << pq.size() << "\n";
    
    return 0;
}
