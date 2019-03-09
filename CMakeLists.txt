cmake_minimum_required(VERSION 3.13)
project(philosophers)

set(CMAKE_CXX_STANDARD 17)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthreads")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCE_FILES src/main.cpp src/Philosopher.cpp src/Philosopher.h src/Fork.cpp src/Fork.h src/DiningTable.cpp src/DiningTable.h src/RandomIntGenerator.cpp src/RandomIntGenerator.h src/Logger.h)

add_executable(philosophers ${SOURCE_FILES})