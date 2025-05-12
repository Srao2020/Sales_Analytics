/*
Created by: Shreya Rao
Date: May 2025
Description: Header for the AnalyticsEngine class.
Processes incoming sales, tracks top products, and detects trends.
*/

#pragma once
#include "SalesStreamSimulator.h"
#include "ProductTracker.h"
#include "SlidingWindow.h"

class AnalyticsEngine {
public:
    AnalyticsEngine();
    void processSale(const Sale& sale);
    void printTopProducts(int k);
    void printTrends();

private:
    ProductTracker tracker;
    SlidingWindow window;
};
