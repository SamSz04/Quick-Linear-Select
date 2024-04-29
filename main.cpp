#include "utils.h"

int main()
{
    // 1.三组不同规模的数据集
    std::vector<int> sizes = {1000, 10000, 100000};
    for (int size : sizes) {
        measurePerformance(size, "random");
        measurePerformance(size, "nearlySorted");
        measurePerformance(size,"reversed");
    }

    std::vector<int> arr(1000);
    for (int i = 0; i < 1000; i++) {
        arr[i] = i;
    }
    for (int i = 0; i < 1000; i += 20) {
        if (i + 1 < 1000) std::swap(arr[i], arr[i + 1]);
    }

    std::vector<int> groupSizes = {3, 5, 7, 10, 12, 15}; // 测试不同的组大小
    for (int groupSize : groupSizes) {
        auto start = std::chrono::high_resolution_clock::now();
        int median = linearSelect(arr, 0, 999, 333, groupSize);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::nano> elapsed = end - start;
        std::cout << "Group Size " << groupSize << ": " << elapsed.count() << " nanoseconds" << std::endl;
    }

    return 0;
}
