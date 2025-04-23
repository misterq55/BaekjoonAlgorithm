#include <iostream>
#include <stack>
#include <vector>
using namespace std;

enum E_OrderType
{
    Preorder, Inorder, Postorder,
};

void dfs(const vector<pair<char, pair<char, char>>>& tree, const int index, const E_OrderType order)
{
    const char ch = static_cast<char>(index + 'A');
    
    if (ch == '.')
    {
        return;
    }

    switch (order)
    {
        case Preorder:
            {
                cout << ch;

                const int leftIndex = tree[index].second.first - 'A';
                dfs(tree, leftIndex, order);

                const int rightIndex = tree[index].second.second - 'A';
                dfs(tree, rightIndex, order);
            }
            break;
        case Inorder:
            {
                const int leftIndex = tree[index].second.first - 'A';
                dfs(tree, leftIndex, order);
                
                cout << ch;
                
                const int rightIndex = tree[index].second.second - 'A';
                dfs(tree, rightIndex, order);
            }
            break;
        case Postorder:
            {
                const int leftIndex = tree[index].second.first - 'A';
                dfs(tree, leftIndex, order);

                const int rightIndex = tree[index].second.second - 'A';
                dfs(tree, rightIndex, order);

                cout << ch;
            }
            break;
        default:
            break;
    }
    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<pair<char, pair<char, char>>> tree(n);

    for (int i = 0; i < n; ++i)
    {
        char parent, leftChild, rightChild;
        cin >> parent >> leftChild >> rightChild;

        tree[parent - 'A'].second.first = leftChild;
        tree[parent - 'A'].second.second = rightChild;

        if (leftChild != '.')
        {
            tree[leftChild - 'A'].first = parent;
        }

        if (rightChild != '.')
        {
            tree[rightChild - 'A'].first = parent;
        }
    }

    stack<int> st;

    st.push(0);
    
    dfs(tree, 0, Preorder);
    cout << "\n";
    
    dfs(tree, 0, Inorder);
    cout << "\n";
    
    dfs(tree, 0, Postorder);
    cout << "\n";
    
    return 0;
}
