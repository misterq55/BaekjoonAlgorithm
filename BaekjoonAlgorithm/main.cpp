#include <iostream>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string s, bomb;
    cin >> s;
    cin >> bomb;

    size_t pos;

    while ((pos = s.find(bomb)) != string::npos)
    {
        s.erase(pos, bomb.length());
    }

    cout << (s.empty() ? "FRULA" : s) << "\n";
    
    return 0;
}
