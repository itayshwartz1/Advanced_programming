cmake_minimum_required(VERSION 3.20)
project(ex6)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(dev anomaly_detection_util.cpp anomaly_detection_util.h  AnomalyDetector.h SimpleAnomalyDetector.h
        timeseries.cpp timeseries.h SimpleAnomalyDetector.cpp  minCircle.cpp minCircle.h
        HybridAnomalyDetector.h HybridAnomalyDetector.cpp commands.h CLI.cpp CLI.h Server.h Server.cpp MainTrain.cpp
        )


