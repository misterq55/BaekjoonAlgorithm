#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void dfs(const vector<pair<int, pair<int, pair<int, int>>>>& tree, vector<vector<int>>& widthVec, int& counter, const int n, const int index)
{
    if (index == -1)
    {
        return;
    }

    const int depth = tree[index].first;
    const int left = tree[index].second.second.first;
    const int right = tree[index].second.second.second;
    
    dfs(tree, widthVec, counter, n, left);
    widthVec[depth].push_back(++counter);
    dfs(tree, widthVec, counter, n, right);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    vector<pair<int, pair<int, pair<int, int>>>> tree(n + 1);
    
    for (int i = 1; i <= n; ++i)
    {
        int node, left, right;
        cin >> node >> left >> right;
        
        tree[node].second.second.first = left;
        tree[node].second.second.second = right;
        
        if (left != -1)
        {
            tree[left].second.first = node;
        }
        
        if (right != -1)
        {
            tree[right].second.first = node;
        }
    }

    int root = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (tree[i].second.first == 0)
        {
            root = i;
            break;
        }
    }

    int maxDepth = 0;
    queue<int> q;
    tree[root].first = 1;
    q.push(root);

    while (!q.empty())
    {
        const int curr = q.front();
        q.pop();

        const int depth = tree[curr].first;
        const int left = tree[curr].second.second.first;
        const int right = tree[curr].second.second.second;

        maxDepth = max(maxDepth, depth);
        
        if (left != -1)
        {
            tree[left].first = depth + 1;
            q.push(left);
        }

        if (right != -1)
        {
            tree[right].first = depth + 1;
            q.push(right);
        }
    }

    vector<vector<int>> widthVec(maxDepth + 1);
    int counter = 0;
    dfs(tree, widthVec, counter, n, root);

    pair<int, int> result;
    for (int i = 1; i <= maxDepth; ++i)
    {
        if (widthVec[i].empty())
        {
            continue;
        }
        
        if (result.second < widthVec[i].back() - widthVec[i].front() + 1)
        {
            result.first = i;
            result.second = widthVec[i].back() - widthVec[i].front() + 1;
        }
    }

    cout << result.first << ' ' << result.second << "\n";
    
    return 0;
}
