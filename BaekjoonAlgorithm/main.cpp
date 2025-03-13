#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cstdlib>
using namespace std;

class CBJHashTable
{
public:
	CBJHashTable()
	{
		HashTable.resize(HashValue);	
	}
	
	~CBJHashTable() {}

public:
	void Insert(int value)
	{
		const int hashKey = GetHashKey(value);

		list<int>& foundList = HashTable[hashKey];

		for (const int& foundValue : foundList)
		{
			if (foundValue == value)
			{
				return;
			}
		}
		
		foundList.push_back(value);
	}

	int Find(int value)
	{
		const int hashKey = GetHashKey(value);

		list<int>& foundList = HashTable[hashKey];

		for (const int& foundValue : foundList)
		{
			if (foundValue == value)
			{
				return 1;
			}
		}
		
		return 0;
	}

private:
	int GetHashKey(int value)
	{
		int hashKey = value % HashValue;
		if (hashKey < 0)
		{
			hashKey *= -1;
		}

		return hashKey;
	}
	
private:
	const int HashValue = 100007; 
	vector<list<int>> HashTable;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	CBJHashTable HashTable;

	int n = 0;
	cin >> n;
	cin.ignore();

	for (int i = 0; i < n; ++i)
	{
		int num;
		cin >> num;
		HashTable.Insert(num);
	}

	int m = 0;
	cin >> m;
	cin.ignore();

	for (int i = 0; i < m; ++i)
	{
		int num;
		cin >> num;
		cout << HashTable.Find(num) << " ";
	}

	cout << "\n";

	return 0;
}