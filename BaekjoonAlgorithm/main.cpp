#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CBJCircularQueue
{
public:
	CBJCircularQueue()
	{
		Buffer.resize(Capacity);
	}
	~CBJCircularQueue() {}

public:
	void Enqueue(const int num)
	{
		Rear = (Rear + 1) % Capacity;
		Buffer[Rear] = num;
		Size++;
	}

	int Dequeue()
	{
		Front = (Front + 1) % Capacity;
		return GetFront();
	}

	int GetSize()
	{
		return Size;
	}

	int IsEmpty()
	{
		return Front == Rear ? 1 : 0;
	}

	int GetFront()
	{
		if (IsEmpty()) return -1;
		return Buffer[Front];
	}

	int GetRear()
	{
		if (IsEmpty()) return -1;
		return Buffer[Rear];
	}

private:
	bool isFull()
	{
		return Rear == Size - 1;
	}

	void resize()
	{
		Capacity *= 2;
		Buffer.resize(Capacity);
	}

private:
	vector<int> Buffer;
	int Front = 0;
	int Rear = 0;
	int Capacity = 10;
	int Size = 0;
};

class CBJCommandParser
{
public:
	CBJCommandParser() {}
	virtual ~CBJCommandParser() {}
	
public:
	vector<string> parseCommand(const string& cmd)
	{
		vector<string> result;
		string delimiter = " ";

		size_t foundPos = cmd.find(delimiter);
		string queueCommand = cmd.substr(0, foundPos);
		string arg = cmd.substr(foundPos + 1);

		result.emplace_back(queueCommand);
		result.emplace_back(arg);
		
		return move(result);
	}
};

class CBJSolution
{
public:
	CBJSolution() {}
	virtual ~CBJSolution() {}

public:
	void PrintSolution(const string& cmd)
	{
		vector<string> parsedCmd = CommandParser.parseCommand(cmd);
		runQueue(parsedCmd);
	}

private:
	void runQueue(const vector<string>& parsedCmd)
	{
		if (parsedCmd.empty())
		{
			return;
		}

		const string& queueCmd = parsedCmd[0];

		if (queueCmd == "push")
		{
			const string arg = parsedCmd[1];
			const int num = stoi(arg);
			CircularQueue.Enqueue(num);
		}
		else if (queueCmd == "pop")
		{
			cout << CircularQueue.Dequeue() << "\n";
		}
		else if (queueCmd == "size")
		{
			cout << CircularQueue.GetSize() << "\n";
		}
		else if (queueCmd == "empty")
		{
			cout << CircularQueue.IsEmpty() << "\n";
		}
		else if (queueCmd == "front")
		{
			cout << CircularQueue.GetFront() << "\n";
		}
		else if (queueCmd == "back")
		{
			cout << CircularQueue.GetRear() << "\n";
		}
	}

private:
	CBJCommandParser CommandParser;
	CBJCircularQueue CircularQueue;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int questionNum = 0;
	cin >> questionNum;
	cin.ignore();

	CBJSolution solution;
	
	for (int i = 0; i < questionNum; ++i)
	{
		string question;
		getline(cin, question);
		solution.PrintSolution(question);
	}

	return 0;
}