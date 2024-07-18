cmake_minimum_required(VERSION 3.10)
project(shades_and_origins_tests)
set(CMAKE_CXX_STANDARD 17)

enable_testing()

find_package(Catch2 REQUIRED)

add_executable(${PROJECT_NAME} test.cpp)
target_link_libraries(${PROJECT_NAME} Catch2::Catch2WithMain)

include(CTest)
include(Catch)

catch_discover_tests(${PROJECT_NAME})