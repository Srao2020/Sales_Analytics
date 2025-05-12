/*
Created by: Shreya Rao
Date: May 2025
Description: Main program that runs the sales simulation and benchmarking in one executable.
Includes performance metrics and ASCII bar charts for analysis.
*/

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include "SalesStreamSimulator.h"
#include "AnalyticsEngine.h"
#include "ProductTracker.h"

struct SaleSummary {
    std::string productID;
    int quantity;
};

// STL-only fallback (for benchmark comparison)
std::vector<std::pair<std::string, int>> stlTopProducts(const std::vector<SaleSummary>& sales, int k) {
    std::unordered_map<std::string, int> count;
    for (const auto& s : sales)
        count[s.productID] += s.quantity;

    std::vector<std::pair<std::string, int>> vec(count.begin(), count.end());
    std::sort(vec.begin(), vec.end(), [](auto& a, auto& b) {
        return b.second > a.second;
    });

    if (vec.size() > k) vec.resize(k);
    return vec;
}

// Clamp bar length and generate ASCII bars
std::string makeBar(double value, double scale = 1.0) {
    int length = static_cast<int>(value * scale);
    return std::string(std::min(length, 80), '|');
}

// Print graph to terminal
void printGraph(const std::string& label, const std::vector<int>& x, const std::vector<double>& y, double scale, const std::string& unit) {
    std::cout << "\n--- " << label << " ---\n";
    for (size_t i = 0; i < x.size(); ++i) {
        std::cout << x[i] << ": " << std::setw(8) << std::fixed << std::setprecision(2) << y[i] << " " << unit << " "
                  << makeBar(y[i], scale) << "\n";
    }
}

// Runs the performance benchmark
void runBenchmark() {
    std::cout << "\n=== Running Benchmark ===\n";

    std::vector<int> sizes = {100, 500, 1000, 2000, 5000};
    std::vector<double> heapTimes, stlTimes, throughputs, latencies_us;

    for (int saleCount : sizes) {
        SalesStreamSimulator sim;
        ProductTracker tracker;
        std::vector<SaleSummary> sales;

        for (int i = 0; i < saleCount; ++i) {
            Sale s = sim.generateSale();
            sales.push_back({s.productID, s.quantity});
        }

        auto startHeap = std::chrono::high_resolution_clock::now();
        for (const auto& s : sales)
            tracker.update(s.productID, s.quantity);
        auto top = tracker.getTopK(5);
        auto endHeap = std::chrono::high_resolution_clock::now();
        double heapTimeMs = std::chrono::duration<double, std::milli>(endHeap - startHeap).count();

        auto startSTL = std::chrono::high_resolution_clock::now();
        auto stlTop = stlTopProducts(sales, 5);
        auto endSTL = std::chrono::high_resolution_clock::now();
        double stlTimeMs = std::chrono::duration<double, std::milli>(endSTL - startSTL).count();

        double seconds = heapTimeMs / 1000.0;
        double throughput = saleCount / seconds;
        double latencyMicro = (heapTimeMs * 1000.0) / saleCount;

        heapTimes.push_back(heapTimeMs);
        stlTimes.push_back(stlTimeMs);
        throughputs.push_back(throughput);
        latencies_us.push_back(latencyMicro);
    }

    printGraph("Heap Tracker Time", sizes, heapTimes, 2.0, "ms");
    printGraph("STL Tracker Time", sizes, stlTimes, 2.0, "ms");
    printGraph("Throughput", sizes, throughputs, 0.01, "ops/sec");
    printGraph("Latency", sizes, latencies_us, 0.05, "μs");
}

// Runs the real-time simulation and logs to CSV
void runSimulation() {
    SalesStreamSimulator simulator;
    AnalyticsEngine engine;

    std::string filePath = "/Users/25rao/CLionProjects/Realtime_sales_analytics/sales_log.csv";
    std::ofstream logFile(filePath);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file.\n";
        return;
    }

    logFile << "timestamp,productID,quantity,price\n";

    std::cout << "Starting real-time sales stream...\n";

    for (int i = 0; i < 100; ++i) {
        Sale sale = simulator.generateSale();
        engine.processSale(sale);
        logFile << sale.timestamp << "," << sale.productID << ","
                << sale.quantity << "," << sale.price << "\n";

        if (i % 10 == 0) {
            std::cout << "\n--- Top Products ---\n";
            engine.printTopProducts(5);
            std::cout << "\n--- Trend Alerts ---\n";
            engine.printTrends();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    logFile.close();
    std::cout << "\nSales log saved to: " << filePath << "\n";
}

int main() {
    std::cout << "Choose an option:\n";
    std::cout << "1. Run simulation\n";
    std::cout << "2. Run benchmark\n";
    std::cout << "> ";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        runSimulation();
    } else if (choice == 2) {
        runBenchmark();
    } else {
        std::cout << "Invalid option.\n";
    }

    return 0;
}
