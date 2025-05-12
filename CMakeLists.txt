cmake_minimum_required(VERSION 3.30)
project(Realtime_sales_analytics)

set(CMAKE_CXX_STANDARD 20)

add_executable(Realtime_sales_analytics main.cpp
        SalesStreamSimulator.cpp
        SalesStreamSimulator.h
        AnalyticsEngine.cpp
        AnalyticsEngine.h
        ProductTracker.cpp
        ProductTracker.h
        SlidingWindow.cpp
        SlidingWindow.h
)
