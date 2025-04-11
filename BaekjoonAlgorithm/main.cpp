#include <iostream>
#include <vector>
using namespace std;

bool dfs(int u, vector<int>& students, vector<bool>& visited, vector<bool>& finished)
{
    visited[u] = true;

    int v = students[u];

    bool result = true;
    if (!visited[v])
    {
        result = dfs(v, students, visited, finished);
    }
    else
    {
        if (!finished[v])
        {
            result = false;
        }
    }

    finished[u] = true;

    return result;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;
        vector<int> students(n + 1);
        vector<bool> visited(n + 1, false);
        vector<bool> finished(n + 1, false);

        for (int i = 1; i <= n; ++i)
        {
            cin >> students[i];
        }

        int count = 0;
        
        for (int i = 1; i <= n; ++i)
        {
            if (!visited[i])
            {
                if (dfs(i, students, visited, finished))
                {
                    count++;
                }
            }
        }
        
        cout << count << "\n";
    }
    
    return 0;
}
