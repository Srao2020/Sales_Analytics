/*
Created by: Shreya Rao
Date: May 2025
Description: Header for the SalesStreamSimulator class.
Generates random simulated Apple-style product sales in real-time.
*/

#pragma once
#include <string>
#include <vector>

struct Sale {
    std::string productID;  // e.g., "iPhone 15"
    std::string category;   // e.g., "Phone"
    int quantity;
    double price;
    long timestamp;
};

class SalesStreamSimulator {
public:
    SalesStreamSimulator();
    Sale generateSale();

private:
    std::vector<std::string> productIDs;
    std::vector<std::string> categories;
};
