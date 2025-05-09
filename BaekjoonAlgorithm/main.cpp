#include <iostream>
#include <string>
#include <vector>
using namespace std;

void BackTrack(vector<string>& equations, string& equation, const int targetNum, int& sum)
{
    if (targetNum <= sum)
    {
        if (targetNum == sum)
        {
            equations.push_back(equation);
        }
        
        return;
    }

    for (int i = 1; i <= 3; ++i)
    {
        equation += (sum == 0 ? "" : "+") + to_string(i);
        sum += i;
        BackTrack(equations, equation, targetNum, sum);
        sum -= i;
        if (sum != 0) equation.pop_back();
        equation.pop_back();
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<string> equations;
    string equation;

    int sum = 0;

    BackTrack(equations, equation, n, sum);

    const int size = static_cast<int>(equations.size());
    if (size < k)
    {
        cout << -1 << "\n";
    }
    else
    {
        cout << equations[k - 1] << "\n";
    }
    
    return 0;
}
