#include <iostream>
#include <stack>
#include <unordered_map>
using namespace std;

bool IsOperator(const char& c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string s;
    cin >> s;

    string expression;
    
    unordered_map<char, int> opPri = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, };

    stack<char> st;
    
    for (const char& c : s)
    {
        if (IsOperator(c))
        {
            while (!st.empty() && opPri[st.top()] >= opPri[c])
            {
                expression += st.top();
                st.pop();
            }
            st.push(c);
        }
        else if (c == '(')
        {
            st.push(c);
        }
        else if (c == ')')
        {
            while (st.top() != '(')
            {
                expression += st.top();
                st.pop();
            }
            st.pop();
        }
        else
        {
            expression += c;
        }
    }

    while (!st.empty())
    {
        expression += st.top();
        st.pop();
    }

    cout << expression << "\n";
    
    return 0;
}
