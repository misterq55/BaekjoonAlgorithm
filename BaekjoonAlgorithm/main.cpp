#include <limits>
#include <iostream>
#include <vector>
using namespace std;

int CaculateSum(const vector<vector<int>>& field, const vector<int>& nums)
{
    int sum = 0;

    const int numsSize = static_cast<int>(nums.size());

    for (int i = 0; i < numsSize; ++i)
    {
        for (int j = i + 1; j < numsSize; ++j)
        {
            const int y = nums[i];
            const int x = nums[j];
            sum += (field[y][x] + field[x][y]);
        }
    }

    return sum;
}

void BackTrack(const vector<vector<int>>& field, vector<int>& start, vector<int>& link, vector<bool>& visited, const int maxLevel, int& minDifference, const int startIdx)
{
    const int size = static_cast<int>(field.size()) - 2;
    
    if (static_cast<int>(start.size()) == maxLevel)
    {
        const int startSum = CaculateSum(field, start);

        for (int i = 1; i <= size; ++i)
        {
            if (!visited[i])
            {
                link.push_back(i);
            }
        }
        
        const int linkSum = CaculateSum(field, link);
        link.clear();
        
        minDifference = min(minDifference, abs(linkSum - startSum));

        return;
    }

    for (int i = startIdx; i <= size; ++i)
    {
        if (visited[i])
        {
            continue;
        }

        visited[i] = true;
        start.push_back(i);

        BackTrack(field, start, link, visited, maxLevel, minDifference, i + 1);
        
        start.pop_back();
        visited[i] = false;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> field(n + 2, vector<int>(n + 2, -1));
    vector<bool> visited(n + 1, false);

    const int maxLevel = n / 2;
    vector<int> start;
    vector<int> link;
    
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            cin >> field[i][j];
        }
    }

    int minDifference = static_cast<int>(std::numeric_limits<int>::max());

    BackTrack(field, start, link, visited, maxLevel, minDifference, 1);

    cout << minDifference << "\n";
    
    return 0;
}
