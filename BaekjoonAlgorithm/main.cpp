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

		Heap[CurrentIndex] = num;
		heapifyUp(CurrentIndex);
		CurrentIndex++;
	}

	int Pop()
	{
		if (isEmpty())
		{
			return 0;
		}

		const int result = Heap[0];
		Heap[0] = Heap[--CurrentIndex];
		heapifyDown();
		
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
	void heapifyUp(const int index)
	{
		int childIndex = index;
		
		while (childIndex > 0)
		{
			int parentIndex = (childIndex - 1) / 2;
			if (Heap[parentIndex] > Heap[childIndex])
			{
				swap(Heap[childIndex], Heap[parentIndex]);
				childIndex = parentIndex;
			}
			else
			{
				break;
			}
		}
	}
	
	void heapifyDown()
	{
		int parentIndex = 0;

		while (true)
		{
			int leftChildIndex = parentIndex * 2 + 1;
			int rightChildIndex = parentIndex * 2 + 2;
			
			int minChildIndex = parentIndex;
			if (leftChildIndex < CurrentIndex && Heap[leftChildIndex] < Heap[minChildIndex])
			{
				minChildIndex = leftChildIndex;
			}

			if (rightChildIndex < CurrentIndex && Heap[rightChildIndex] < Heap[minChildIndex])
			{
				minChildIndex = rightChildIndex;
			}

			if (minChildIndex == parentIndex)
			{
				break;
			}
			
			swap(Heap[parentIndex], Heap[minChildIndex]);
			parentIndex = minChildIndex;
		}
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
		MinHeap.Push(num);

		if (num == 0)
		{
			cout << MinHeap.Pop() << "\n";
		}
	}

	void PrintSolution(const string& question)
	{
		
	}

private:
	CBJMinHeap MinHeap;
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