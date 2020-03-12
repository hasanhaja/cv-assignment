cmake_minimum_required(VERSION 3.15)
project(cv_assignment)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

add_executable(cv_assignment main.cpp)

target_link_libraries(cv_assignment ${OpenCV_LIBS})