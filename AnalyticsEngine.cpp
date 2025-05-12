/*
Created by: Shreya Rao
Date: May 2025
Description: Implementation of the AnalyticsEngine class.
Manages the overall analysis by combining product tracking and trend detection.
*/

#include "AnalyticsEngine.h"
#include <iostream>

AnalyticsEngine::AnalyticsEngine() : tracker(), window(10) {}

void AnalyticsEngine::processSale(const Sale& sale) {
    tracker.update(sale.productID, sale.quantity);
    window.recordSale(sale.productID);
}

void AnalyticsEngine::printTopProducts(int k) {
    auto top = tracker.getTopK(k);
    for (const auto& [product, qty] : top) {
        std::cout << product << ": " << qty << " sold\n";
    }
}

void AnalyticsEngine::printTrends() {
    auto hot = window.detectTrends();
    for (const auto& product : hot) {
        std::cout << "Spike in: " << product << "\n";
    }
}
