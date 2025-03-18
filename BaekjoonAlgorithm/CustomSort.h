#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <map>
#include <set>
#include <stack>

class CBJSort
{
public:
	static std::vector<int> Sort(const std::vector<int>& nums);
private:
	static std::vector<int> bubbleSort(const std::vector<int>& nums);
	static std::vector<int> selectionSort(const std::vector<int>& nums);
	static std::vector<int> insertSort(const std::vector<int>& nums);
	static std::vector<int> countingSort(const std::vector<int>& nums);
	static std::vector<int> mergeSort(const std::vector<int>& nums);
	static void mergesort_nonrecursive(std::vector<int>& nums);
	static void mergesort_recursive(std::vector<int>& nums, const int left, const int right);
	static void merge(std::vector<int>& nums, const int left, const int mid, const int right);
	static std::vector<int> quickSort(const std::vector<int>& nums);
	static void quickSort_nonrecursive(std::vector<int>& nums);
	static void quickSort_recursive(std::vector<int>& nums, int left, int right);
};