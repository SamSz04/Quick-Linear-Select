#ifndef QUICKSELECT_H
#define QUICKSELECT_H

#include <vector>
#include <cstdlib>

int partition(std::vector<int>& arr, int left, int right)
// 随机选择一个pivot元素,根据这个pivot将数组分为两部分:左侧所有元素都不大于pivot,右侧所有元素都不小于pivot。
{
    int pivotIndex = left + std::rand() % (right - left + 1);
    int pivot = arr[pivotIndex];
    std::swap(arr[pivotIndex], arr[right]);  // 把pivot移到末尾
    int storeIndex = left;
    for (int i = left; i < right; i++) {
        if (arr[i] < pivot) {
            std::swap(arr[i], arr[storeIndex]);
            storeIndex++;
        }
    }
    std::swap(arr[storeIndex], arr[right]);  // 把pivot移到最终正确的位置
    return storeIndex;  // 返回pivot的位置
}

int quickSelect(std::vector<int>& arr, int left, int right, int k)
{
    if (left == right)      // 说明子数组只有一个元素,直接返回该元素
    {
        return arr[left];
    }

    int pivotIndex = partition(arr, left, right);

    if (k == pivotIndex)
    {
        return arr[k];      // 说明第k小的元素已经找到，直接返回
    }
    else if (k < pivotIndex)
    {
        return quickSelect(arr, left, pivotIndex - 1, k);
    } else
    {
        return quickSelect(arr, pivotIndex + 1, right, k);
    }
}

#endif //QUICKSELECT_H