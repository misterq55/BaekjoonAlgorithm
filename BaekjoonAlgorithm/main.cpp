#include <iostream>
#include <vector>
using namespace std;

bool isPromising(vector<int>& row, int n)
{
    for (int i = 0; i < n; ++i)
    {
        
    }
}

void NQueen(vector<vector<int>>& field, int n, int level, int pos, int& count)
{
    if (level == n)
    {
        count++;   
    }

    for (int i = 0; i < n; ++i)
    {
        
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> field(n, vector<int>(n, 0));
    int count = 0;
    
    return 0;
}
