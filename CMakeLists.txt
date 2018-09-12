cmake_minimum_required(VERSION 3.10)
project(traceroute)

set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra -Wpedantic")
message(STATUS "Building with the following extra flags: ${CMAKE_CXX_FLAGS}")

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/include
)

file(GLOB SOURCES "src/*.cpp")

add_library( engine ${SOURCES} )
add_executable(${PROJECT_NAME} src/main.cpp)   
add_dependencies(${PROJECT_NAME} engine)      
target_link_libraries(${PROJECT_NAME} engine)  
