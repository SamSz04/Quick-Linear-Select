#ifndef LINEARSELECT_H
#define LINEARSELECT_H

#include <vector>
#include <algorithm>  // For std::nth_element

int findMedian(std::vector<int>& arr, int left, int num)
{
    // 使用std::nth_element在指定范围内重新排列元素,确保第num/2位置的元素处于排序后它应有的位置
    // 同时保证左边的元素不大于它,右边的元素不小于它。
    std::nth_element(arr.begin() + left, arr.begin() + left + num / 2, arr.begin() + left + num);
    return arr[left + num / 2];     // 返回该位置的元素作为中位数
}

int partition(std::vector<int>& arr, int left, int right, int pivot)
{
    auto it = std::find(arr.begin() + left, arr.begin() + right, pivot);
    std::swap(*it, arr[right]);
    int storeIndex = left;
    for (int i = left; i < right; i++)
    {
        if (arr[i] < pivot)
        {   // 遍历子数组,把小于枢纽的元素移到数组的左边
            std::swap(arr[i], arr[storeIndex]);
            storeIndex++;
        }
    }
    std::swap(arr[storeIndex], arr[right]);     // 把枢纽元素交换回它应有的位置,即所有小于它的元素之后
    return storeIndex;
}

int linearSelect(std::vector<int>& arr, int left, int right, int k, int groupSize) {
    if (left == right) {
        return arr[left];
    }

    int n = right - left + 1;        // 当前子数组的长度
    std::vector<int> medians((n + groupSize - 1) / groupSize);
    for (int i = 0; i < n / groupSize; i++)  // 遍历数组,每5个元素为一组,计算每组的中位数并存储在medians向量中
    {
        medians[i] = findMedian(arr, left + i * groupSize, groupSize);
    }
    if (n % groupSize != 0)     // 如果数组长度不是5的倍数,为剩余元素计算中位数
    {
        medians[n / groupSize] = findMedian(arr, left + (n / groupSize) * groupSize, n % groupSize);
    }
    // 选择中位数数组的中位数作为pivot是为了保证分割的两个子数组大小相对均衡,避免极端不平衡的情况,这是算法保持O(n)复杂度的关键。
    int medianOfMedians = (medians.size() == 1) ? medians[0] : linearSelect(medians, 0, medians.size() - 1, medians.size() / 2, groupSize);
    // 这种方法通过递归地确保枢纽是一个好的中位数,避免了传统Quick Select中可能遇到的最坏情况(例如已排序的数组或pivot选择不当导致的极端不平衡)
    int pivotIndex = partition(arr, left, right, medianOfMedians);

    if (k == pivotIndex)
    {
        return arr[k];
    }
    else if (k < pivotIndex)
    {
        return linearSelect(arr, left, pivotIndex - 1, k, groupSize);
    }
    else
    {
        return linearSelect(arr, pivotIndex + 1, right, k, groupSize);
    }
}

#endif //LINEARSELECT_H