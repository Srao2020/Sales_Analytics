/*
Created by: Shreya Rao
Date: May 2025
Description: Header for the SlidingWindow class.
Tracks recent sales in a fixed time window to detect sudden increases in product activity.
*/

#pragma once
#include <deque>
#include <unordered_map>
#include <vector>
#include <string>
#include <ctime>

class SlidingWindow {
public:
    SlidingWindow(int seconds);
    void recordSale(const std::string& productID);
    std::vector<std::string> detectTrends();

private:
    int windowSize;
    std::deque<std::pair<std::string, long>> saleLog;
    std::unordered_map<std::string, int> freq;
};
