cmake_minimum_required(VERSION 3.10)

project(CFoodProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_definitions(-DUNICODE -D_UNICODE)

add_executable(CFoodProject
${PROJECT_SOURCE_DIR}/src/CFood.cpp
${PROJECT_SOURCE_DIR}/src/file.cpp
${PROJECT_SOURCE_DIR}/src/Parser.cpp
${PROJECT_SOURCE_DIR}/src/Recipe.cpp
)
