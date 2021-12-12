cmake_minimum_required(VERSION 3.20)
project(dev)

set(CMAKE_CXX_STANDARD 11)

add_executable(dev anomaly_detection_util.cpp anomaly_detection_util.h  AnomalyDetector.h SimpleAnomalyDetector.h
        timeseries.cpp timeseries.h SimpleAnomalyDetector.cpp  MainTrain.cpp minCircle.cpp minCircle.h
        HybridAnomalyDetector.h HybridAnomalyDetector.cpp)


