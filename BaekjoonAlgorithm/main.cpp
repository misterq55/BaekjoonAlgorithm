#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

void BackTrack(const vector<vector<int>>& field, vector<int>& charCounter,
               vector<pair<int, int>>& directions, const int level, int& maxCount, pair<int, int> pos)
{
    maxCount = max(maxCount, level);
    
    for (const auto& direction : directions)
    {
        const int ny = pos.first + direction.first;
        const int nx = pos.second + direction.second;

        const int& nCh = field[ny][nx];
        if (nCh == -1)
        {
            continue;
        }

        if (!charCounter[nCh])
        {
            charCounter[nCh]++;
            BackTrack(field, charCounter, directions, level + 1, maxCount, {ny, nx});
            charCounter[nCh]--;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> charCounter(26, 0);
    vector<vector<int>> field(n + 2, vector<int>(m + 2, -1));
    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    for (int i = 1; i <= n; ++i)
    {
        string s;
        cin >> s;
        for (int j = 1; j <= m; ++j)
        {
            field[i][j] = s[j - 1] - 'A';
        }
    }

    int maxCount = 0;
    charCounter[field[1][1]]++;
    BackTrack(field, charCounter, directions, 1, maxCount, {1, 1});
    charCounter[field[1][1]]--;

    cout << maxCount << "\n";

    return 0;
}
