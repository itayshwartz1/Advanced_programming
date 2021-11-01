cmake_minimum_required(VERSION 3.20)
project(dev)

set(CMAKE_CXX_STANDARD 11)
add_executable(dev anomaly_detection_util.cpp anomaly_detection_util.h  AnomalyDetector.h SimpleAnomalyDetector.h
        TimeSeries.cpp TimeSeries.h TimeSeriesTest.cpp TimeSeriesTest.h)



