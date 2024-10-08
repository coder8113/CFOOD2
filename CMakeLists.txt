cmake_minimum_required(VERSION 3.10)

project(CFoodProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for header files
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/lib/test_library
)

add_definitions(-DUNICODE -D_UNICODE)

# Define the main executable for the project
add_executable(CFoodProject
    ${PROJECT_SOURCE_DIR}/src/CFood.cpp
    ${PROJECT_SOURCE_DIR}/src/Console.cpp
    ${PROJECT_SOURCE_DIR}/src/file.cpp
    ${PROJECT_SOURCE_DIR}/src/Parser.cpp
    ${PROJECT_SOURCE_DIR}/src/Recipe.cpp
    ${PROJECT_SOURCE_DIR}/src/EventListener.cpp
    ${PROJECT_SOURCE_DIR}/src/Menu.cpp
    ${PROJECT_SOURCE_DIR}/src/Util.cpp
)

# Define the test executable
add_executable(tests
    ${PROJECT_SOURCE_DIR}/src/tests.cpp
    ${PROJECT_SOURCE_DIR}/src/Console.cpp
    ${PROJECT_SOURCE_DIR}/src/file.cpp        # Include source files needed for the test
    ${PROJECT_SOURCE_DIR}/src/Parser.cpp
    ${PROJECT_SOURCE_DIR}/src/Recipe.cpp
    ${PROJECT_SOURCE_DIR}/src/EventListener.cpp
    ${PROJECT_SOURCE_DIR}/src/Menu.cpp
    ${PROJECT_SOURCE_DIR}/src/Util.cpp
    
)

# Add tests
enable_testing()

add_test(
    NAME tests
    COMMAND $<TARGET_FILE:tests>
)
