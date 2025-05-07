#include <iostream>
#include <vector>
using namespace std;

void BackTrack(const vector<int>& cards, vector<bool>& visited, const int maxCardNum, const int maxNum, const int level, int& sum, int& ans)
{
    if (sum > maxNum)
    {
        return;
    }
    
    if (level == maxCardNum)
    {
        ans = max(sum, ans);
        return;
    }
    
    const int size = static_cast<int>(cards.size());
    for (int i = 0; i < size; ++i)
    {
        if (visited[i])
        {
            continue;
        }
        
        visited[i] = true;
        sum += cards[i];
        BackTrack(cards, visited, maxCardNum, maxNum, level + 1, sum, ans);
        sum -= cards[i];
        visited[i] = false;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> cards(n);
    
    int maxCardNum = 3;

    for (int i = 0; i < n; ++i)
    {
        cin >> cards[i];
    }

    int sum = 0;
    int ans = 0;
    vector<bool> visited(n , false);
    BackTrack(cards, visited, maxCardNum, m, 0, sum, ans);

    cout << ans << "\n";
    
    return 0;
}
