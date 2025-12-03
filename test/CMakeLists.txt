# book
find_package(GTest REQUIRED)
# GTest 头文件路径（部分系统需显式指定，如 Ubuntu）
# include_directories(${GTEST_INCLUDE_DIRS})
message(STATUS "GTest_INCLUDE_DIR: ${GTest_INCLUDE_DIR}")

# ctest 测试无细节输出，需要加 -V 参数查看详细输出

## book unittest
set(TEST ${CMAKE_PROJECT_NAME}_test)
file(GLOB_RECURSE TEST_SRC book/unittest.cpp)
add_executable(${TEST} ${TEST_SRC})
add_test(NAME ${TEST} COMMAND ${TEST})
target_include_directories(${TEST} PUBLIC ${GTest_INCLUDE_DIR})
target_link_libraries(${TEST} PUBLIC gtest::gtest)

## common unittest
set(COMMON_TEST common_test)
file(GLOB_RECURSE COMMON_TEST_SRC common/*.cpp)
add_executable(${COMMON_TEST} ${COMMON_TEST_SRC})
add_test(NAME ${COMMON_TEST} COMMAND ${COMMON_TEST}) # NAME = common_test

# 设置包含目录，指向 common 特性代码的位置
# target_include_directories(${COMMON_TEST} PUBLIC ${PROJECT_SOURCE_DIR}/features/common)
target_include_directories(${COMMON_TEST} PUBLIC ${GTest_INCLUDE_DIR})
target_link_libraries(${COMMON_TEST} PUBLIC 
    common  # 跨子目录链接核心库（直接用子目录定义的目标名）
    gtest::gtest
)

## json11 unittest
set(JSON11_TEST json11_test)
file(GLOB_RECURSE JSON11_TEST_SRC json11/*.cpp)
add_executable(${JSON11_TEST} ${JSON11_TEST_SRC})
add_test(NAME ${JSON11_TEST} COMMAND ${JSON11_TEST}) # NAME = json11_test
target_include_directories(${JSON11_TEST} PUBLIC ${GTest_INCLUDE_DIR})
target_link_libraries(${JSON11_TEST} PUBLIC 
    json11  # 跨子目录链接核心库（直接用子目录定义的目标名）
    gtest::gtest
)

# 这行代码用于包含Google Test框架的CMake模块。通过包含GoogleTest模块，可以使用Google Test提供的一些CMake函数和宏，用于配置和管理测试相关的任务。
# include(GoogleTest)
# find_package(GTest CONFIG REQUIRED)
# 设置包含目录，通常这不是必需的，因为 FetchContent_MakeAvailable 已经处理了  
# 但如果您遇到问题，可以手动添加
# target_include_directories(${COMMON_TEST} PUBLIC ${gtest_SOURCE_DIR}/include)

# add_subdirectory(jnitest)

# fuzz
# add_executable(request_message_parse fuzzers/request_message_parse.cpp)
# target_compile_options(request_message_parse PRIVATE -fsanitize=address,fuzzer)
# target_link_libraries(request_message_parse simple-web-server -fsanitize=address,fuzzer)
# set_target_properties(request_message_parse PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# 一个单元测试来说，添加的步骤为：
# 1. 使用add_executable添加测试目标
# 2. 使用target_link_libraries为测试目标添加依赖gtest和gtest_main
# 3. 使用add_test添加到项目，以便可以使用ctest命令执行测试

# 1. build/test 执行 执行 ctest -V -C Debug 可以输出详细信息
# 2. build/test 执行 make test 只能输出测试结果
# 3. build/test 执行 xxx