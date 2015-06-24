cmake_minimum_required(VERSION 3.1)
project(task3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(dir ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})

set(SOURCE_FILES main.cpp
Parser/Parser.cpp Parser/Expression.cpp Parser/Abstraction.cpp
Parser/Application.cpp Parser/Variable.cpp
)

add_executable(task3 ${SOURCE_FILES})
