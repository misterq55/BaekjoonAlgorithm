#include <iostream>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string s, bomb, result;
    cin >> s;
    cin >> bomb;

    const int size = static_cast<int>(s.length());
    const size_t boomSize = bomb.length();
    
    for (const char& c : s)
    {
        result += c;

        if (result.size() >= boomSize)
        {
            bool bisBomb = true;

            for (int i = 0; i < boomSize; ++i)
            {
                if (result[result.size() - boomSize + i] != bomb[i])
                {
                    bisBomb = false;
                    break;
                }
            }

            if (bisBomb)
            {
                for (int i = 0; i < boomSize; ++i)
                {
                    result.pop_back();
                }
            }
        }
    }

    cout << (result.empty() ? "FRULA" : result) << "\n";
    
    return 0;
}
