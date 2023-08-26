# unit_test/CMakeLists.txt

# Specify minimum CMake version and project name
cmake_minimum_required(VERSION 3.5)

project(unit_tests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include files for unit testing
set(TEST_SOURCES
    unit_tests.cpp
    ../include/json_parser.h
    ../src/json_parser.cpp
    ../include/mqtt_client.h
    ../src/mqtt_client.cpp
    ../include/doctest.h
)

# Executable for running unit tests
add_executable(unit_tests ${TEST_SOURCES})

# Link Qt libraries
target_link_libraries(unit_tests PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts paho-mqtt3a paho-mqttpp3)

# Include directories
target_include_directories(unit_tests PRIVATE ../include)
