cmake_minimum_required(VERSION 3.10)

project(CFoodProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

# Enable testing and find GoogleTest
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add main project executable
add_executable(CFoodProject
    ${PROJECT_SOURCE_DIR}/src/CFood.cpp
    ${PROJECT_SOURCE_DIR}/src/file.cpp
    ${PROJECT_SOURCE_DIR}/src/Parser.cpp
    ${PROJECT_SOURCE_DIR}/src/Recipe.cpp
    ${PROJECT_SOURCE_DIR}/src/EventListener.cpp
)

# Add the test executable
add_executable(runUnitTests
    ${PROJECT_SOURCE_DIR}/tests/tests.cpp
)

# Link Google Test and pthread to the test executable
target_link_libraries(runUnitTests ${GTEST_LIBRARIES} pthread)

# Add test to CTest
add_test(NAME runUnitTests COMMAND runUnitTests)

# Coverage reporting
option(COVERAGE "Enable coverage reporting" ON)
if(COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()

# Custom target for coverage
add_custom_target(coverage
    COMMAND ${CMAKE_MAKE_PROGRAM} runUnitTests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMAND lcov --capture --directory . --output-file coverage.info
    COMMAND lcov --remove coverage.info '/usr/*' --output-file coverage.info
    COMMAND lcov --list coverage.info
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running tests and generating coverage report"
)
