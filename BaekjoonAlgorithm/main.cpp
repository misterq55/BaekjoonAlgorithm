#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool isPossible(const vector<int>& coordinates, const long long mid, const int m)
{
    int count = 1;
    int lastPos = coordinates[0];

    const int size = static_cast<int>(coordinates.size());
    for (int i = 1; i < size; ++i)
    {
        if (coordinates[i] - lastPos >= mid)
        {
            count++;
            lastPos = coordinates[i];
        }
    }

    return count >= m;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> coordinates(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> coordinates[i];
    }

    sort(coordinates.begin(), coordinates.end());
    
    long long left = 1, right = coordinates.back() - coordinates.front(), ans = 0;

    while (left <= right)
    {
        long long mid = left + (right - left) / 2;

        if (isPossible(coordinates, mid, m))
        {
            ans = mid;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    cout << ans << "\n";

    return 0;
}
