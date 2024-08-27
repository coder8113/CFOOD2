cmake_minimum_required(VERSION 3.10)

project(CFoodProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories("C:/Program Files (x86)/Microsoft Visual Studio/2022/Community/VC/Auxiliary/VS/UnitTest/include")


add_definitions(-DUNICODE -D_UNICODE)

add_library(HelloCov STATIC
${PROJECT_SOURCE_DIR}/src/CFood.cpp
${PROJECT_SOURCE_DIR}/src/file.cpp
${PROJECT_SOURCE_DIR}/src/Parser.cpp
${PROJECT_SOURCE_DIR}/src/Recipe.cpp
${PROJECT_SOURCE_DIR}/src/EventListener.cpp
)

add_executable(CFoodProject
${PROJECT_SOURCE_DIR}/src/CFood.cpp
${PROJECT_SOURCE_DIR}/src/file.cpp
${PROJECT_SOURCE_DIR}/src/Parser.cpp
${PROJECT_SOURCE_DIR}/src/Recipe.cpp
${PROJECT_SOURCE_DIR}/src/EventListener.cpp
)

add_executable(test_CFoodProject
    ${PROJECT_SOURCE_DIR}/test_CFoodProject/test_CFoodProject.cpp
    # Add other test files if needed
)

target_link_libraries(test_CFoodProject HelloCov)

option(COVERAGE "Enable coverage reporting" ON)
if(COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()

add_custom_target(coverage
    COMMAND ${CMAKE_MAKE_PROGRAM} test_CFoodProject
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMAND lcov --capture --directory . --output-file coverage.info
    COMMAND lcov --remove coverage.info '/usr/*' --output-file coverage.info
    COMMAND lcov --list coverage.info
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running tests and generating coverage report"
)

enable_testing()
add_test(NAME RunUnitTests COMMAND test_CFoodProject)