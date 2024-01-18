# book

set(TEST ${CMAKE_PROJECT_NAME}_test)

file(GLOB_RECURSE TEST_SRC book/unittest.cpp)

add_executable(${TEST} ${TEST_SRC})
add_test(NAME ${TEST} COMMAND ${TEST})

# book
target_link_libraries(${TEST} PUBLIC book_lib gtest gtest_main)

# common
set(COMMON_TEST common_test)

file(GLOB_RECURSE COMMON_TEST_SRC common/*.cpp)

add_executable(${COMMON_TEST} ${COMMON_TEST_SRC})
add_test(NAME ${COMMON_TEST} COMMAND ${COMMON_TEST})


add_subdirectory(server)

target_include_directories(${COMMON_TEST} PUBLIC ${PROJECT_SOURCE_DIR}/common)

target_link_libraries(${COMMON_TEST} PUBLIC common gtest gtest_main)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# 一个单元测试来说，添加的步骤为：
# 1. 使用add_executable添加测试目标
# 2. 使用target_link_libraries为测试目标添加依赖gtest和gtest_main
# 3. 使用add_test添加到项目，以便可以使用ctest命令执行测试

# 1. build/test 执行 执行 ctest -V -C Debug 可以输出详细信息
# 2. build/test 执行 make test 只能输出测试结果
# 3. build/test 执行 xxx