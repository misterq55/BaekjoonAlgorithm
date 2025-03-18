#include "CustomSort.h"

std::vector<int> CBJSort::Sort(const std::vector<int>& nums)
{
    std::vector<int> result;

    const size_t size = result.size();
    // result = bubbleSort(nums);
    // result = insertSort(nums);
    // result = selectionSort(nums);
    // result = quickSort(nums);
    // result = countingSort(nums);
    result = mergeSort(nums);

    return result;
}

std::vector<int> CBJSort::bubbleSort(const std::vector<int>& nums)
{
    std::vector<int> result = nums;

    const size_t size = result.size();
    for (size_t i = 0; i < size - 1; ++i)
    {
        for (size_t j = 0; j < size - i - 1; ++j)
        {
            if (result[j] > result[j + 1])
            {
                std::swap(result[j], result[j + 1]);
            }
        }
    }

    return move(result);
}

std::vector<int> CBJSort::selectionSort(const std::vector<int>& nums)
{
    std::vector<int> result = nums;

    const size_t size = result.size();
    for (size_t i = 0; i < size - 1; i++)
    {
        size_t minIndex = i;

        for (size_t j = i + 1; j < size; ++j)
        {
            if (result[j] < result[minIndex])
            {
                minIndex = j;
            }
        }

        std::swap(result[i], result[minIndex]);
    }

    return move(result);
}

std::vector<int> CBJSort::insertSort(const std::vector<int>& nums)
{
    std::vector<int> result = nums;

    const size_t size = result.size();
    for (size_t i = 1; i < size; ++i)
    {
        int temp = result[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && result[j] > temp)
        {
            result[j + 1] = result[j];
            j--;
        }

        result[j + 1] = temp;
    }

    return move(result);
}

std::vector<int> CBJSort::countingSort(const std::vector<int>& nums)
{
    int countBuffer[10001] = {0};
    for (const auto& num : nums)
    {
        countBuffer[num]++;
    }

    std::vector<int> result;
    for (int i = 0; i < 10001; ++i)
    {
        for (int j = 0; j < countBuffer[i]; ++j)
        {
            result.push_back(i);
        }
    }

    return result;
}

std::vector<int> CBJSort::mergeSort(const std::vector<int>& nums)
{
    std::vector<int> result = nums;
    // mergesort_recursive(result, 0, static_cast<int>(result.size()) - 1);
    mergesort_nonrecursive(result);
    return result;
}

void CBJSort::mergesort_nonrecursive(std::vector<int>& nums)
{
    int mergeSize = 1;

    while (mergeSize < nums.size())
    {
        for (size_t i = 0; i < nums.size(); i += mergeSize * 2)
        {
            const int left = i;
            const int mid = std::min(i + mergeSize - 1, nums.size() - 1);
            const int right = std::min(i + mergeSize * 2 - 1, nums.size() - 1);
            merge(nums, left, mid, right);
        }

        mergeSize *= 2;
    }
}

void CBJSort::mergesort_recursive(std::vector<int>& nums, const int left, const int right)
{
    if (left >= right)
    {
        return;
    }

    const int mid = (left + right) / 2;

    mergesort_recursive(nums, left, mid);
    mergesort_recursive(nums, mid + 1, right);
    merge(nums, left, mid, right);
}

void CBJSort::merge(std::vector<int>& nums, const int left, const int mid, const int right)
{
    int i = 0, j = 0, k = left;

    std::vector<int> leftNums = std::vector<int>(nums.begin() + left, nums.begin() + mid + 1);
    std::vector<int> rightNums = std::vector<int>(nums.begin() + mid + 1, nums.begin() + right + 1);

    while (i < leftNums.size() && j < rightNums.size())
    {
        if (leftNums[i] > rightNums[j])
        {
            nums[k++] = leftNums[i++];
        }
        else
        {
            nums[k++] = rightNums[j++];
        }
    }

    while (i < leftNums.size())
    {
        nums[k++] = leftNums[i++];
    }

    while (j < rightNums.size())
    {
        nums[k++] = rightNums[j++];
    }
}

std::vector<int> CBJSort::quickSort(const std::vector<int>& nums)
{
    std::vector<int> result = nums;

    const size_t size = result.size();

    // 재귀
    // quickSort_recursive(result, 0, size - 1);
    quickSort_nonrecursive(result);

    return result;
}

void CBJSort::quickSort_nonrecursive(std::vector<int>& nums)
{
    std::stack<std::pair<int, int>> stack;
    stack.push(std::pair<int, int>(0, nums.size() - 1));

    while (!stack.empty())
    {
        const std::pair<int, int> top = stack.top();
        stack.pop();

        int left = top.first;
        int right = top.second;

        const size_t pivotIndex = (left + right) / 2;
        const int pivotValue = nums[pivotIndex];
        const int originalLeft = left;
        const int originalRight = right;

        while (left <= right)
        {
            while (nums[left] < pivotValue) left++;
            while (nums[right] > pivotValue) right--;

            if (left <= right)
            {
                std::swap(nums[right], nums[left]);
                left++;
                right--;
            }
        }

        if (originalLeft < right) stack.push(std::make_pair(originalLeft, right));
        if (left < originalRight) stack.push(std::make_pair(left, originalRight));
    }
}

void CBJSort::quickSort_recursive(std::vector<int>& nums, int left, int right)
{
    const size_t size = nums.size();
    if (left >= right)
    {
        return;
    }

    const size_t pivotIndex = (left + right) / 2;
    const int pivotValue = nums[pivotIndex];
    const int originalLeft = left;
    const int originalRight = right;

    while (left <= right)
    {
        while (nums[left] < pivotValue) left++;
        while (nums[right] > pivotValue) right--;

        if (left <= right)
        {
            std::swap(nums[right], nums[left]);
            left++;
            right--;
        }
    }

    quickSort_recursive(nums, originalLeft, right);
    quickSort_recursive(nums, left, originalRight);
}
