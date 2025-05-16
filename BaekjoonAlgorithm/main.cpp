#include <iostream>
#include <vector>
using namespace std;

void RecursiveMakeStars(vector<vector<char>>& field, const int level, const int startY, const int startX)
{
    if (level == 3)
    {
        field[startY][startX] = '*';
        field[startY + 1][startX - 1] = field[startY + 1][startX + 1] = '*';
        field[startY + 2][startX - 2] = field[startY + 2][startX - 1] = field[startY + 2][startX] = field[startY + 2][startX + 1] = field[startY + 2][startX + 2] = '*';
        return;
    }

    RecursiveMakeStars(field, level / 2, startY, startX);
    RecursiveMakeStars(field, level / 2, startY + level / 2, startX - level / 2);
    RecursiveMakeStars(field, level / 2, startY + level / 2, startX + level / 2);
}

void PrintStars(const vector<vector<char>>& field)
{
    for (const auto& row : field)
    {
        for (const auto& col : row)
        {
            cout << col;
        }
        
        cout << "\n";
    }
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

    const int height = n;
    const int width = n * 2 - 1;
    vector<vector<char>> field(height, vector<char>(width, ' '));

    RecursiveMakeStars(field, n, 0, n - 1);
    PrintStars(field);

    return 0;
}
