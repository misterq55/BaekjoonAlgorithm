#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CBJMinHeap
{
public:
	CBJMinHeap()
	{
		Heap.resize(Capacity);
	}
	
	~CBJMinHeap() {}

public:
	void Push(const int num)
	{
		if (isFull())
		{
			resize();	
		}

		Heap[CurrentIndex++] = num;
		
		heapify();
	}

	int Pop()
	{
		if (isEmpty())
		{
			return 0;
		}

		const int result = Heap[0];
		Heap[0] = Heap[CurrentIndex - 1];
		CurrentIndex--;
		heapify();
		
		return result;
	}

private:
	bool isFull() const
	{
		return CurrentIndex == (Capacity - 1);
	}

	bool isEmpty() const
	{
		return CurrentIndex == 0;
	}
	
	void resize()
	{
		vector<int> tempHeap(Capacity * 2);

		for (int i = 0; i < Capacity; i++)
		{
			tempHeap[i] = Heap[i];
		}

		Capacity *= 2;
		
		Heap = move(tempHeap);
	}

private:
	void heapify()
	{
		// TODO
	}
	
private:
	vector<int> Heap;
	int Capacity = 10;
	int CurrentIndex = 0;
};

class CBJSolution
{
public:
	CBJSolution() {}
	virtual ~CBJSolution() {}

public:
	void PrintSolution(const int& num)
	{
		AbsoluteValueHeap.Push(num);

		if (num == 0)
		{
			cout << AbsoluteValueHeap.Pop() << "\n";
		}
	}

	void PrintSolution(const string& question)
	{
		
	}

private:
	CBJMinHeap AbsoluteValueHeap;
	int ZeroCounter = 0;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	CBJSolution solution;

	int questionNum = 0;
	cin >> questionNum;
	cin.ignore();

	for (int i = 0; i < questionNum; ++i)
	{
		int question;
		cin >> question;
		solution.PrintSolution(question);
	}

	return 0;
}