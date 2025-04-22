#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isPossible(const vector<long long>& budgetRequest, const long long possibleBudget, const long long budget)
{
    const int size = static_cast<int>(budgetRequest.size());
    long long sum = 0;
    for (int i = 0; i < size; ++i)
    {
        sum += (budgetRequest[i] > possibleBudget ? possibleBudget : budgetRequest[i]);
    }
    
    return budget >= sum;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    long long n, m;
    cin >> n;

    vector<long long> budgetRequest(n, 0);
    for (int i = 0; i < n; ++i)
    {
        cin >> budgetRequest[i];
    }

    cin >> m;
    
    long long left = 0;
    long long right = *max_element(budgetRequest.begin(), budgetRequest.end());
    long long ans = 0;

    while (left <= right)
    {
        const long long mid = left + (right - left) / 2;
        if (isPossible(budgetRequest, mid, m))
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
