#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <random>
#include "quickselect.h"
#include "linearselect.h"

// Utility to generate random array
std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, size);
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// Utility to generate nearly sorted array
std::vector<int> generateNearlySortedArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    // Introduce slight disorder
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 0; i < size; i += 20) {
        if (i + 1 < size) std::swap(arr[i], arr[i + 1]);
    }
    return arr;
}

// Utility to generate reverse sorted array
std::vector<int> generateReversedArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    std::reverse(arr.begin(), arr.end());
    return arr;
}

// Function to measure the performance
void measurePerformance(int size, const std::string& type) {
    std::vector<int> arr;
    if (type == "random")
    {
        arr = generateRandomArray(size);
    }
    else if (type == "nearlySorted")
    {
        arr = generateNearlySortedArray(size);
    }
    else if (type == "reversed")
    {
        arr = generateReversedArray(size);
    }

    std::vector<int> copy = arr; // Make a copy for fair comparison

    auto start = std::chrono::high_resolution_clock::now();
    int kthElement = quickSelect(arr, 0, arr.size() - 1, size / 3);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Quick Select on " << type << " data of size " << size << ": " << elapsed.count() << " nanoseconds." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    kthElement = linearSelect(copy, 0, copy.size() - 1, size / 3, 5);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Linear Select on " << type << " data of size " << size << ": " << elapsed.count() << " nanoseconds." << std::endl;
}

#endif //UTILS_H