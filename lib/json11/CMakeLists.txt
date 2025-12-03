cmake_minimum_required(VERSION 3.11.0)
project(json11 VERSION 0.1.0)

# common
file(GLOB_RECURSE SRC json11.cpp)
add_library(${PROJECT_NAME} STATIC ${SRC})
# add_library(common_lib STATIC ${COMMON_SRC})

# 关键：暴露头文件路径（PUBLIC 表示其他依赖此库的目标可访问该路径）
# 这里用 CMAKE_CURRENT_SOURCE_DIR 表示 common 目录的绝对路径
target_include_directories(json11 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

## Only install headers that belong to this `features/common` module.
## Installing the whole ${CMAKE_SOURCE_DIR} caused the install script
## to attempt copying the repository root into the install tree which
## can produce extremely long paths and unexpected recursion.
# file(GLOB_RECURSE HEADERS
#                  CONFIGURE_DEPENDS
#                  ${CMAKE_CURRENT_SOURCE_DIR}/*.h
#                  ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
# if(HEADERS)
#         install(FILES ${HEADERS} DESTINATION include/common)
# endif()
