# unit_test/CMakeLists.txt

# Set the source files for your unit tests
set(TEST_SOURCES
    unit_tests.cpp
)

# Create the unit_tests executable and link it to the doctest library
add_executable(unit_tests ${TEST_SOURCES})
target_link_libraries(unit_tests PRIVATE production_line_ui_library)  # Link with the new library
target_include_directories(unit_tests PRIVATE ${DOCTEST_DIR})
