/*
Created by: Shreya Rao
Date: May 2025
Description: Implementation of the SlidingWindow class.
Detects short-term spikes in product activity within a sliding time window.
*/

#include "SlidingWindow.h"
#include <chrono>

SlidingWindow::SlidingWindow(int seconds) : windowSize(seconds) {}

void SlidingWindow::recordSale(const std::string& productID) {
    long now = std::chrono::system_clock::now().time_since_epoch() / std::chrono::seconds(1);
    saleLog.emplace_back(productID, now);
    freq[productID]++;

    while (!saleLog.empty() && (now - saleLog.front().second > windowSize)) {
        freq[saleLog.front().first]--;
        if (freq[saleLog.front().first] == 0) freq.erase(saleLog.front().first);
        saleLog.pop_front();
    }
}

std::vector<std::string> SlidingWindow::detectTrends() {
    std::vector<std::string> hot;
    for (const auto& p : freq) {
        if (p.second >= 5) hot.push_back(p.first);
    }
    return hot;
}
