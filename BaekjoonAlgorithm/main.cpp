#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

void deleteFromTree(const int curr, vector<pair<int, vector<int>>>& tree, queue<int>& q)
{
    vector<int>& children = tree[curr].second;
    for (const int child : children)
    {
        if (tree[child].first != -1)
        {
            q.push(child);
        }
    }

    int parent = tree[curr].first;
    vector<int>& childrenFromParent = tree[parent].second;
    childrenFromParent.erase(remove(childrenFromParent.begin(), childrenFromParent.end(), curr), childrenFromParent.end());
    tree[curr].first = -1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<pair<int, vector<int>>> tree(n);
    for (int i = 0; i < n; ++i)
    {
        int node;
        cin >> node;

        if (node == -1)
        {
            node = i;
        }

        if (node != i)
        {
            tree[node].second.push_back(i);
        }
        tree[i].first = node;
    }

    int toDelete;
    cin >> toDelete;

    queue<int> q;
    deleteFromTree(toDelete, tree, q);
    
    while (!q.empty())
    {
        const int curr = q.front();
        q.pop();

        deleteFromTree(curr, tree, q);
    }
    
    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        if (tree[i].first != -1 && tree[i].second.empty())
        {
            count++;
        }
    }

    cout << count << "\n";
    
    return 0;
}
