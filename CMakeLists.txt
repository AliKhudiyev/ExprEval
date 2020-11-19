cmake_minimum_required(VERSION 3.1)

project(ExprEval)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(expreval STATIC 
    expression.cpp 
    tokenizer.cpp 
    operator.cpp 
    node_list.cpp)

add_executable(main expreval.cpp)
target_link_libraries(main expreval)