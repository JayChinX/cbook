cmake_minimum_required(VERSION 3.0.0)
project(mathfunctions VERSION 0.1.0)

# mathfunctions
file(GLOB_RECURSE MATH_SRC mathfunctions.cpp)
add_library(${PROJECT_NAME} SHARED ${MATH_SRC})
# add_library(common_lib STATIC ${COMMON_SRC})
