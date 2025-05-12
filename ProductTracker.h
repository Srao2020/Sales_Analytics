/*
Created by: Shreya Rao
Date: May 2025
Description: Header for the ProductTracker class.
Maintains a count of sales per product and returns the top K selling products using a min-heap.
*/

#pragma once
#include <unordered_map>
#include <queue>
#include <string>
#include <vector>

class ProductTracker {
public:
    void update(const std::string& productID, int quantity);
    std::vector<std::pair<std::string, int>> getTopK(int k);

private:
    std::unordered_map<std::string, int> sales;
};
