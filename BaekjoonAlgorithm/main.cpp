#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <map>
#include <set>
using namespace std;

class CBJSolution
{
public:
	CBJSolution() {}
	~CBJSolution() {}

public:
	void EnterData(const string& data)
	{
		Data0.emplace(data, Index);
		Data1.emplace(Index++, data);
	}

	string FindData(const string& data)
	{
		if (isNumber(data))
		{
			return Data1[stoi(data)];
		}
		else
		{
			return to_string(Data0[data]);
		}
	}

private:
	bool isNumber(const string& data)
	{
		if (data.empty())
		{
			return false;
		}

		return isdigit(data[0]);
	}
	
private:
	map<string, int> Data0;
	map<int, string> Data1;
	int Index = 1;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	CBJSolution solution;
	
	unsigned int n = 0, m = 0;
	cin >> n;
	cin >> m;
	cin.ignore();

	for (unsigned int i = 0; i < n; ++i)
	{
		string data;
		getline(cin, data);
		solution.EnterData(data);
	}

	for (unsigned int i = 0; i < m; ++i)
	{
		string question;
		getline(cin, question);
		cout << solution.FindData(question) << "\n";
	}

	return 0;
}