#include <iostream>
#include <vector>
using namespace std;

void RecursiveMakeStars(vector<vector<char>>& field, const int level, const int startY, const int startX,
                        const int height, const int width, const int endEdgeY, const int endEdgeX)
{
    int y = startY;
    int x = startX;

    if (level == 1)
    {
        x--;
        field[y][x--] = '*';
        field[y++][x] = '*';
        field[y++][x] = '*';
        field[y][x] = '*';

        return;
    }

    while (x > endEdgeX)
    {
        field[y][x--] = '*';
    }

    while (y < height - 1)
    {
        field[y++][x] = '*';
    }

    while (x < width - 1)
    {
        field[y][x++] = '*';
    }

    while (y > endEdgeY)
    {
        field[y--][x] = '*';
    }

    RecursiveMakeStars(field, level - 1, y + 1, x, height - 2, width - 2, endEdgeY + 2, endEdgeX + 2);
}

vector<string> MakeStringStars(const vector<vector<char>>& field, const int height, const int width)
{
    vector<string> result;
    for (int i = 0; i < height; ++i)
    {
        string s;
        for (int j = 0; j < width; ++j)
        {
            s += field[i][j];
        }
        
        s.erase(s.find_last_not_of(' ') + 1);
        result.push_back(s);
    }

    return move(result);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    if (n == 1)
    {
        cout << "*" << "\n";
        return 0;
    }

    const int height = n * 3 + (n - 1);
    const int width = (n - 1) * 4 + 1;
    vector<vector<char>> field(height, vector<char>(width, ' '));

    RecursiveMakeStars(field, n, 0, width - 1, height, width, 1, 0);
    vector<string> result = MakeStringStars(field, height, width);

    for (const string& s : result)
    {
        cout << s << "\n";
    }

    return 0;
}
