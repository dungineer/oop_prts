cmake_minimum_required(VERSION 3.19)
project(TraxParser)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} main.cpp parser/parser.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC parser)
