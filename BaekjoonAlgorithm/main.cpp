#include <iostream>
#include <vector>
using namespace std;

bool isValid(const string& str)
{
    const int size = static_cast<int>(str.size());
    if (size == 0)
    {
        return false;
    }

    if (str[0] >= 'A' && str[0] <= 'Z' || str[0] == '_')
    {
        return false;
    }

    const int lastIndex = size - 1;
    if (str[lastIndex] == '_')
    {
        return false;
    }

    int underBarCount = 0;
    int upperCaseCount = 0;

    for (int i = 0; i < size; ++i)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            ++upperCaseCount;
        }

        if (str[i] == '_')
        {
            if (str[i + 1] == '_')
            {
                return false;
            }
            
            ++underBarCount;
        }
    }

    if (underBarCount > 0 && upperCaseCount > 0)
    {
        return false;
    }

    return true;
}

bool isParsingPoint(const bool isJava, const char ch)
{
    if (isJava)
    {
        return ch == '_';
    }

    return ch >= 'A' && ch <= 'Z';
}

void correctParsedStr(const bool isJava, string& parsedStr)
{
    if (isJava)
    {
        parsedStr.erase(0, 1);
        parsedStr[0] -= ('a' - 'A');
    }
    else
    {
        parsedStr[0] += ('a' - 'A');
        parsedStr = "_" + parsedStr;
    }
}

void parsingString(const string str, vector<string>& parsedStr, const int offset, const int size)
{
    parsedStr.push_back(str.substr(offset, size));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string s;
    cin >> s;

    if (!isValid(s))
    {
        cout << "Error!" << "\n";
        return 0;
    }

    const bool bisJava = s.find("_") != string::npos;

    vector<string> parsedStr;

    const int size = static_cast<int>(s.length());
    int prevIndex = 0;
    for (int i = 0; i < size; ++i)
    {
        const char ch = s[i];
        
        if (isParsingPoint(bisJava, ch))
        {
            parsingString(s, parsedStr, prevIndex, i - prevIndex);
            prevIndex = i;
        }
    }

    parsingString(s, parsedStr, prevIndex, size - prevIndex);

    const int parsedSize = static_cast<int>(parsedStr.size());

    for (int i = 1; i < parsedSize; ++i)
    {
        correctParsedStr(bisJava, parsedStr[i]);
    }

    string ans;
    for (int i = 0; i < parsedSize; ++i)
    {
        ans += parsedStr[i];
    }

    cout << ans << "\n";
    
    return 0;
}
