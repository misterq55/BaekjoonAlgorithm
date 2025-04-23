#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

bool cycleCheck(const int node, unordered_map<int, pair<vector<int>, vector<int>>>& tree, unordered_map<int, bool>& visited, unordered_map<int, bool>& finished)
{
    bool bisCycle = false;

    visited[node] = true;
    vector<int>& adj = tree[node].second;

    for (const int& next : adj)
    {
        if (!visited[next])
        {
            bisCycle = cycleCheck(next, tree, visited, finished);
        }
        else if (!finished[next])
        {
            bisCycle = true;
        }
    }

    finished[node] = true;
    
    return bisCycle;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int k = 0;
    unordered_map<int, pair<vector<int>, vector<int>>> tree;
    
    while (true)
    {
        int u, v;
        cin >> u >> v;

        if (u == 0 && v == 0)
        {
            unordered_map<int, bool> visited;
            unordered_map<int, bool> finished;
            
            bool bisTree = true;
            int rootCounter = 0;
            
            for (const auto& node : tree)
            {
                const vector<int>& inDegree = node.second.first;
                if (inDegree.empty())
                {
                    rootCounter++;
                }

                if (inDegree.size() > 1)
                {
                    bisTree = false;
                    break;
                }

                if (!visited[node.first])
                {
                    if (cycleCheck(node.first, tree, visited, finished))
                    {
                        bisTree = false;
                        break;
                    }
                }
            }

            if (rootCounter > 1)
            {
                bisTree = false;
            }

            const string strTree = bisTree ? "" : " not";
            cout << "Case " << ++k << " is" << strTree << " a tree." << "\n";
            
            tree.clear();
        }
        else
        {
            vector<int>& outDegree = tree[u].second;
            outDegree.push_back(v);

            vector<int>& inDegree = tree[v].first;
            inDegree.push_back(u);
        }

        if (u == -1 && v == -1)
        {
            break;
        }
    }
    
    return 0;
}
