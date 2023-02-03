cmake_minimum_required(VERSION 3.0.0)
project(common VERSION 0.1.0)

# common
file(GLOB_RECURSE COMMON_SRC md5.cpp)
add_library(${PROJECT_NAME} SHARED ${COMMON_SRC})
# add_library(common_lib STATIC ${COMMON_SRC})
