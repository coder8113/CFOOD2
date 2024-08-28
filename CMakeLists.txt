cmake_minimum_required(VERSION 3.10)

project(CFoodProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/lib/test_library
)


add_definitions(-DUNICODE -D_UNICODE)
add_library(test_library ${PROJECT_SOURCE_DIR}/test_library/test_library.cpp)

add_executable(CFoodProject
${PROJECT_SOURCE_DIR}/src/CFood.cpp
${PROJECT_SOURCE_DIR}/src/file.cpp
${PROJECT_SOURCE_DIR}/src/Parser.cpp
${PROJECT_SOURCE_DIR}/src/Recipe.cpp
${PROJECT_SOURCE_DIR}/src/EventListener.cpp
${PROJECT_SOURCE_DIR}/src/Menu.cpp
)

add_executable(tests ${PROJECT_SOURCE_DIR}/tests/tests.cpp)
target_link_libraries(tests PRIVATE test_library)
enable_testing()

add_test(
	NAME tests
	COMMAND $<TARGET_FILE:tests>
)
