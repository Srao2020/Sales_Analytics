# Real-Time Sales Analytics (Apple Products Edition)

This project simulates real-time sales of Apple products and performs performance benchmarking using advanced data structures in C++. The goal is to track top-selling products and detect short-term sales spikes efficiently, while measuring throughput and latency of the system.

---

## How to Use

You’ll be prompted to choose:
```
Choose an option:
1. Run simulation
2. Run benchmark
```

---

## Products Simulated

The simulator randomly generates sales from this list of Apple-style products:

| Product                  | Category     | Price ($) |
|--------------------------|--------------|-----------|
| iPhone 15               | Phone        | 799       |
| iPhone 15 Pro Max       | Phone        | 1199      |
| MacBook Air             | Laptop       | 999       |
| MacBook Pro 16"         | Laptop       | 2499      |
| iPad Pro                | Tablet       | 1099      |
| iPad Mini               | Tablet       | 499       |
| AirPods Pro             | Audio        | 249       |
| AirPods Max             | Audio        | 549       |
| Apple Watch Series 9    | Wearable     | 399       |
| Apple Watch Ultra 2     | Wearable     | 799       |
| Apple TV 4K             | Media        | 129       |
| HomePod Mini            | Smart Home   | 99        |

---

## Simulation Output Explained

When you choose Option 1: Run simulation, the program:

- Simulates 100 real-time sales (with 0.1s delay between each)
- Logs each sale to:  
  /Users/25rao/CLionProjects/Realtime_sales_analytics/sales_log.csv

### Terminal Output:

Every 10 sales, you’ll see:

Top Products  
Lists the 5 best-selling products based on unit quantity.

```
--- Top Products ---
iPhone 15: 18 sold
MacBook Air: 15 sold
iPad Pro: 12 sold
...
```

Trend Alerts  
Flags products that sold 5+ units in the last 10 seconds (spike detection).

```
--- Trend Alerts ---
Spike in: AirPods Pro
Spike in: iPad Mini
```

This simulates how retailers track flash trends in real time.

---

## Benchmark Output Explained

When Option 2: Run benchmark is selected, the program:

1. Simulates batches of 100, 500, 1000, 2000, and 5000 sales
2. Processes the same sales data using two methods:
    - A heap-based tracker (priority queue and hashmap)
    - A basic STL-only tracker using `unordered_map` and `sort()`
3. Measures four key performance metrics:
    - **Heap Time**: Time (in milliseconds) required by the heap-based method
    - **STL Time**: Time required by the STL method
    - **Throughput**: Sales processed per second (operations per second)
    - **Latency**: Average time to process one sale (in microseconds)

All results are displayed as ASCII bar graphs in the terminal for clarity and comparison.

### Sample ASCII Graph Output

```
--- Heap Tracker Time ---
100:    0.08 ms  ||||
500:    0.31 ms  |||||||||||
1000:   0.55 ms  |||||||||||||||||

--- STL Tracker Time ---
100:    0.10 ms  ||||||
500:    0.46 ms  ||||||||||||||||
1000:   0.88 ms  ||||||||||||||||||||||

--- Throughput ---
100:  1250000.00 ops/sec  ||||||||||||||||||||||||||||||||||
500:  1610000.00 ops/sec  ||||||||||||||||||||||||||||||||||||||||||

--- Latency ---
100:  0.64 μs  ||
500:  0.62 μs  ||
1000: 0.55 μs  |||
```

### How to Interpret the Graphs

Each bar graph uses vertical bars (`|`) to represent the magnitude of a measurement. The more bars printed, the higher the value being measured. Here's how each graph reflects system performance:

- **Heap Tracker Time vs. STL Tracker Time**: These graphs show the total processing time (in milliseconds) for each method. As the number of sales increases, the STL method's bars grow longer more quickly, reflecting its slower scaling. In contrast, the heap-based method shows smaller increases, indicating better efficiency and scalability.

- **Throughput**: This graph reflects how many operations are completed per second. Longer bars mean higher throughput and better system performance. Throughput generally increases with larger data sets up to a point, then stabilizes or drops if the algorithm can't keep up.

- **Latency**: This graph shows how much time (in microseconds) each individual sale takes to process. Lower latency means faster response per operation. In the ASCII graph, shorter bars are better—indicating that the system is processing each sale quickly.

The comparison across all four graphs illustrates both the absolute performance and the scaling behavior of the two implementations. The heap-based tracker demonstrates faster execution time, better throughput, and lower latency than the STL-based version, especially as data volumes grow. These visual representations make performance trends easy to observe directly in the terminal.

---

## File Structure

```
/Realtime_sales_analytics/
├── main.cpp                # Runs simulation and benchmarks
├── SalesStreamSimulator.*  # Generates fake Apple-style sales
├── AnalyticsEngine.*       # Manages top products and trends
├── ProductTracker.*        # Heap-based tracker for top sellers
├── SlidingWindow.*         # Time-windowed trend detection
├── sales_log.csv           # Output of simulation
├── README.md               # You're here!
```

