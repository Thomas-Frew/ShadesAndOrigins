cmake_minimum_required(VERSION 3.10)
project(shades_and_origins_src)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_SOURCE_DIR}/build/src/${PROJECT_NAME}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Running Shades and Origins Source"
)

# Run tests
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build/tests
)

add_dependencies(${PROJECT_NAME} run_tests)