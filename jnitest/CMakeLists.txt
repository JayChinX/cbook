cmake_minimum_required(VERSION 3.0.0)
project(jni_learn VERSION 0.1.0)

# jni
file(GLOB_RECURSE JNI_SRC corendk.cpp)
add_library(${PROJECT_NAME} SHARED ${JNI_SRC})

# 导入头文件，让头文件可以通过 <xx.h> 形式导入
target_include_directories(${PROJECT_NAME} PUBLIC .)

target_include_directories(${PROJECT_NAME} PUBLIC ../lib/jni)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

