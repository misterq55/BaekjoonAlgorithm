#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int numIndex = 0;
    int val = 0;

    for (int i = 1; i <= 3; ++i)
    {
        string s;
        cin >> s;
        
        int tempVal = atoi(s.c_str());
        if (tempVal > 0)
        {
            val = tempVal;
            numIndex = i;
        }
    }

    const int nextIndex = 4 - numIndex;
    const int ansIndex = val + nextIndex;

    if (ansIndex % 15 == 0) cout << "FizzBuzz" << "\n";
    else if (ansIndex % 3 == 0) cout << "Fizz" << "\n";
    else if (ansIndex % 5 == 0) cout << "Buzz" << "\n";
    else cout << ansIndex << "\n";

    return 0;
}
