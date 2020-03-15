cmake_minimum_required(VERSION 3.15)
project(cv_assignment)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

add_executable(cv_assignment src/main.cpp src/utilities/display.h src/utilities/display.cpp src/utilities/aliases.h src/Runner.cpp src/Runner.h src/Detector.cpp src/Detector.h src/utilities/result.h src/utilities/input.h src/Event.h)

target_link_libraries(cv_assignment ${OpenCV_LIBS})