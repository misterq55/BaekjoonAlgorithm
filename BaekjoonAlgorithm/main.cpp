#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool IsValid(const vector<char>& result)
{
    int vowels = 0;
    int consonants = 0;
    
    for (const char& c : result)
    {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        {
            ++vowels;
        }
        else
        {
            ++consonants;
        }
    }

    return vowels >= 1 && consonants >= 2;
}

void PrintResult(const vector<char>& result)
{
    for (const char& c : result)
    {
        cout << c;
    }
    
    cout << "\n";
}

void BackTrack(const vector<char>& passwords, vector<char>& result, const int c, const int& l, const int level, const int start)
{
    if (l == level)
    {
        if (IsValid(result))
        {
            PrintResult(result);
        }
        
        return;
    }

    for (int i = start; i < c; i++)
    {
        result.push_back(passwords[i]);
        BackTrack(passwords, result, c, l, level + 1, i + 1);
        result.pop_back();
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int l, c;
    cin >> l >> c;

    vector<char> passwords(c);
    vector<bool> visited(c);
    vector<char> result;

    for (int i = 0; i < c; ++i)
    {
        cin >> passwords[i];
    }

    sort(passwords.begin(), passwords.end());

    BackTrack(passwords, result, c, l, 0, 0);
    
    return 0;
}
