cmake_minimum_required(VERSION 2.8)
project(tasks)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O2")

set(dir ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})

set(SOURCE_FILES
Parser/Parser.cpp Parser/Expression.cpp Parser/Abstraction.cpp
Parser/Application.cpp Parser/Variable.cpp
Normalization/Normalization.cpp
TermParser/Function.cpp TermParser/TermParser.cpp
TermParser/TermVariable.cpp TermParser/Term.cpp
Unification/Unification.cpp Unification/Equation.cpp
Typization/Typization.cpp
)

add_executable(task1 task1.cpp ${SOURCE_FILES})
add_executable(task2 task2.cpp ${SOURCE_FILES})
add_executable(task3 task3.cpp ${SOURCE_FILES})
add_executable(task4 task4.cpp ${SOURCE_FILES})
add_executable(task5 task5.cpp ${SOURCE_FILES})
add_executable(task6 task6.cpp ${SOURCE_FILES})
