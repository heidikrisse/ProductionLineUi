cmake_minimum_required(VERSION 3.5)

project(production_line_ui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add paths to Paho MQTT header files and libraries
set(PAHO_MQTT_CPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/paho.mqtt.cpp")
set(PAHO_MQTT_C_DIR "${CMAKE_CURRENT_SOURCE_DIR}/paho.mqtt.c")

# Add PahoMQTT subdirectories
add_subdirectory(${PAHO_MQTT_C_DIR})
add_subdirectory(${PAHO_MQTT_CPP_DIR})

# Include directories
include_directories(include)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt5Charts)

set(PROJECT_SOURCES
        main.cpp
        src/mainwindow.cpp
        include/mainwindow.h
        mainwindow.ui
        include/mqtt_client.h
        src/mqtt_client.cpp
        include/json.hpp
        include/json_parser.h
        src/json_parser.cpp
        include/doctest.h
        json_examples/line1.json
        json_examples/line2.json
        json_examples/line3.json
        json_examples/camera1.json
        json_examples/camera2.json
        json_examples/camera3.json
        resources/images/toggleBtn_on.png
        resources/images/toggleBtn_off.png
        resources/resources.qrc
        include/mqtt_main_window_bridge.h
        src/mqtt_main_window_bridge.cpp
)

set(CMAKE_AUTORCC ON)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(production_line_ui
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources/resources.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET production_line_ui APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(production_line_ui SHARED
            ${PROJECT_SOURCES}
            resources/resources.qrc
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(production_line_ui
            ${PROJECT_SOURCES}
            resources/resources.qrc
        )
    endif()
endif()

target_link_libraries(production_line_ui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts paho-mqtt3a paho-mqttpp3)

set_target_properties(production_line_ui PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS production_line_ui
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(production_line_ui resources/resources.qrc)
endif()

# Option to enable or disable unit tests
option(ENABLE_UNIT_TESTS "Enable unit tests" ON)

# Add unit_test directory as subdirectory if unit tests are enabled
if(ENABLE_UNIT_TESTS)
    add_subdirectory(unit_test)
endif()
