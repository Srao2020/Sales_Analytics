/*
Created by: Shreya Rao
Date: May 2025
Description: Implementation of the ProductTracker class.
Uses a hash map and min-heap to efficiently compute top-selling products.
*/

#include "ProductTracker.h"
#include <algorithm>

void ProductTracker::update(const std::string& productID, int quantity) {
    sales[productID] += quantity;
}

std::vector<std::pair<std::string, int>> ProductTracker::getTopK(int k) {
    auto cmp = [](auto& a, auto& b) { return a.second > b.second; };
    std::priority_queue<
        std::pair<std::string, int>,
        std::vector<std::pair<std::string, int>>,
        decltype(cmp)
    > minHeap(cmp);

    for (const auto& entry : sales) {
        minHeap.push(entry);
        if (minHeap.size() > k)
            minHeap.pop();
    }

    std::vector<std::pair<std::string, int>> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top());
        minHeap.pop();
    }
    std::reverse(result.begin(), result.end());
    return result;
}
