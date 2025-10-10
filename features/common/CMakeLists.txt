cmake_minimum_required(VERSION 3.11.0)
project(common VERSION 0.1.0)

# common
file(GLOB_RECURSE COMMON_SRC md5.cpp)
add_library(${PROJECT_NAME} SHARED ${COMMON_SRC})
# add_library(common_lib STATIC ${COMMON_SRC})

## Only install headers that belong to this `features/common` module.
## Installing the whole ${CMAKE_SOURCE_DIR} caused the install script
## to attempt copying the repository root into the install tree which
## can produce extremely long paths and unexpected recursion.
file(GLOB_RECURSE COMMON_HEADERS
                 CONFIGURE_DEPENDS
                 ${CMAKE_CURRENT_SOURCE_DIR}/*.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
if(COMMON_HEADERS)
        install(FILES ${COMMON_HEADERS} DESTINATION include/common)
endif()
