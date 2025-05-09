#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

void BackTrack(const vector<int>& romanNums, unordered_map<int, bool>& visited, const int maxLevel, const int level, const int num, const int start, int& count)
{
    if (level == maxLevel)
    {
        if (!visited[num])
        {
            count++;
            visited[num] = true;
        }
        
        return;
    }

    for (int i = start; i < 4; ++i)
    {
        const int sum = num + romanNums[i];
        BackTrack(romanNums, visited, maxLevel, level + 1, sum, i, count);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<int> romanNums = {1, 5, 10, 50};
    unordered_map<int, bool> visited;

    int count = 0;
    BackTrack(romanNums, visited, n, 0, 0, 0, count);

    cout << count << "\n";
    
    return 0;
}
