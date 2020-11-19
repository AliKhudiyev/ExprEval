cmake_minimum_required(VERSION 3.1)

project(ExprEval)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(expreval STATIC 
    src/expression.cpp 
    src/tokenizer.cpp 
    src/operator.cpp 
    src/node_list.cpp)

add_executable(main expreval.cpp)
target_link_libraries(main expreval)