#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> boardStartWithWhite(n + 1, vector<int>(m + 1, 0));
    vector<vector<int>> boardStartWithBlack(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i)
    {
        string s;
        cin >> s;
        
        for (int j = 1; j <= m; ++j)
        {
            boardStartWithWhite[i][j] = boardStartWithWhite[i - 1][j] + boardStartWithWhite[i][j - 1] - boardStartWithWhite[i - 1][j - 1];
            boardStartWithBlack[i][j] = boardStartWithBlack[i - 1][j] + boardStartWithBlack[i][j - 1] - boardStartWithBlack[i - 1][j - 1];
            
            if ((i + j) % 2 == 0)
            {
                if (s[j - 1] == 'B')
                {
                    boardStartWithWhite[i][j] += 1;
                }
                else if (s[j - 1] == 'W')
                {
                    boardStartWithBlack[i][j] += 1;
                }    
            }
            else
            {
                if (s[j - 1] == 'B')
                {
                    boardStartWithBlack[i][j] += 1;
                }
                else if (s[j - 1] == 'W')
                {
                    boardStartWithWhite[i][j] += 1;
                }
            }
        }
    }

    int minValue = 2147483647;
    for (int i = k; i <= n; ++i)
    {
        for (int j = k; j <= m; ++j)
        {
            const int y = i - k;
            const int x = j - k;
            const int blackMinValue = boardStartWithBlack[i][j] - boardStartWithBlack[y][j] - boardStartWithBlack[i][x] + boardStartWithBlack[y][x];
            const int whiteMinValue = boardStartWithWhite[i][j] - boardStartWithWhite[y][j] - boardStartWithWhite[i][x] + boardStartWithWhite[y][x];
            const int tempMinValue = min(blackMinValue, whiteMinValue); 
            minValue = min(tempMinValue, minValue);
        }
    }

    cout << minValue << "\n";

    return 0;
}
