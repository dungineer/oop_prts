cmake_minimum_required(VERSION 3.18)
project(Missions)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} main.cpp mission.cpp planner.cpp)