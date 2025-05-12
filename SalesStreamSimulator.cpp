/*
Created by: Shreya Rao
Date: May 2025
Description: Implementation of the SalesStreamSimulator class.
Generates random Apple product sales (e.g., iPhone, MacBook) with realistic categories and prices.
*/

#include "SalesStreamSimulator.h"
#include <chrono>
#include <cstdlib>
#include <ctime>

SalesStreamSimulator::SalesStreamSimulator() {
    productIDs = {
        "iPhone 15", "iPhone 15 Pro Max",
        "MacBook Air", "MacBook Pro 16\"",
        "iPad Pro", "iPad Mini",
        "AirPods Pro", "AirPods Max",
        "Apple Watch Series 9", "Apple Watch Ultra 2",
        "Apple TV 4K", "HomePod Mini"
    };

    categories = {
        "Phone", "Phone",
        "Laptop", "Laptop",
        "Tablet", "Tablet",
        "Audio", "Audio",
        "Wearable", "Wearable",
        "Media", "Smart Home"
    };

    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

Sale SalesStreamSimulator::generateSale() {
    Sale s;
    int index = std::rand() % productIDs.size();
    s.productID = productIDs[index];
    s.category = categories[index];
    s.quantity = 1 + std::rand() % 3;

    // Assign realistic prices
    if (s.productID == "iPhone 15") s.price = 799.0;
    else if (s.productID == "iPhone 15 Pro Max") s.price = 1199.0;
    else if (s.productID == "MacBook Air") s.price = 999.0;
    else if (s.productID == "MacBook Pro 16\"") s.price = 2499.0;
    else if (s.productID == "iPad Pro") s.price = 1099.0;
    else if (s.productID == "iPad Mini") s.price = 499.0;
    else if (s.productID == "AirPods Pro") s.price = 249.0;
    else if (s.productID == "AirPods Max") s.price = 549.0;
    else if (s.productID == "Apple Watch Series 9") s.price = 399.0;
    else if (s.productID == "Apple Watch Ultra 2") s.price = 799.0;
    else if (s.productID == "Apple TV 4K") s.price = 129.0;
    else if (s.productID == "HomePod Mini") s.price = 99.0;
    else s.price = 500.0; // fallback

    s.timestamp = std::chrono::system_clock::now().time_since_epoch() / std::chrono::seconds(1);
    return s;
}
