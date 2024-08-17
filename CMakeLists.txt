cmake_minimum_required(VERSION 3.29)
project(Pong)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories(Pong ${SDL2_INCLUDE_DIRS})
include_directories(Pong ${GLM_INCLUDE_DIRS})

find_package(glm REQUIRED)

add_executable(Pong main.cpp)
target_link_libraries(Pong ${SDL2_LIBRARIES})
target_link_libraries(Pong ${GLM_LIBRARIES})
