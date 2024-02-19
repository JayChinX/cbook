cmake_minimum_required(VERSION 3.11.0)
project(books VERSION 0.1.0)
# 制定C++版本 C++11
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COLOR_MAKEFILE ON)
# 第三方依赖脚本
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

# 自定义参数/编译选项
option(BUILD_TESTING "set ON to build library tests" ON)


include_directories(${PROJECT_SOURCE_DIR}/include)

# 定义变量 SRC = *.cpp + *.cpp
# set(SRC src/main.cpp src/books.cpp)
file(GLOB_RECURSE SRC src/*.cpp)
# 生成可执行文件 + 多文件打包
add_executable(${PROJECT_NAME} ${SRC})

# target_include_directories(${PROJECT_NAME} PUBLIC common)

# 多文件管理
# set(SRC main.cpp bookssm.cpp)
# # 生成库文件 .so 多文件打包
# add_library(book SHARED ${SRC})
# add_library(book SHARED main.cpp bookssm.cpp)

# # 编译参数 debug/release
# set(CMAKE_BUILD_TYPE "Debug")
# # set(CMAKE_BUILD_TYPE Release)

# if (NOT CMAKE_BUILD_TYPE)
#     set(CMAKE_BUILD_TYPE Release)
#     message("Setting default build type to Release")
# endif()


# target_include_directories(${PROJECT_NAME} PUBLIC common)

# target_link_libraries(${PROJECT_NAME} common)


# 将要进行测试的文件编译为静态库
# file(GLOB_RECURSE TEST_SRC src/book.cpp src/books.cpp)
# add_library(book_lib STATIC ${TEST_SRC})


# add_subdirectory(lib/googletest)
# add_subdirectory(jnitest)
add_subdirectory(features/common)
add_subdirectory(libs/server)
add_subdirectory(features/server)

if(BUILD_TESTING)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif(BUILD_TESTING)

# PROJECT_SOURCE_DIR/CMAKE_SOURCE_DIR/_SOURCE_DIR： 为包含PROJECT()命令的最近一个CMakeLists.txt文件所在的文件夹路径。
# 输出可执行文件存放目录 PROJECT_BINARY_DIR 运行cmake命令的目录，即工程编译发生的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
# 输出可动态库文件存放目录
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# 设置是否生成compile_commands.json文件来记录编译过程
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 将b动态库文件链接到可执行文件 a
# target_link_libraries(a b)

# 自定义编译选项
option(USE_MYMATH "Use code provided math implementation" OFF)
# configure_file(Config.h.in Config.h)

if (USE_MYMATH)
    #add_definitions 为源码库编译添加一个
    # cmake .. -DUSE_MYMATH=OFF/0
    # 或者
    # cmake .. -DUSE_MYMATH=ON/1
    message("Use code provided math implementation")
    add_definitions(-DUSE_MYMATH)
    add_subdirectory(features/mathfunctions)
    # 用list命令来在列表中保存需要连接的库和需要导入的头文件。cmake中的list时以;分割的字符串。
    # list(APPEND <list> [<element> ...])
    # APPEND为修改命令，为list中添加元素。
    # <list>为list的变量名，如果当前作用域中不存在这个变量名则作为空, list为其添加
    # [<element> ...]为list添加的元素
    # ps:也可以用set来创建list，例如：set(var a b c d) var的值为a;b;c;d;然后照样可以用list的命令来处理var
    # list(APPEND EXTRA_LIBS features/mathfunctions)
    list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/features/mathfunctions)

    target_link_libraries(${PROJECT_NAME} PUBLIC mathfunctions)

endif()


target_include_directories(${PROJECT_NAME} PUBLIC ${EXTRA_INCLUDES})

# 打包编译产物
install(TARGETS books
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include)

# # mathfunctions 对应头文件
# file(GLOB_RECURSE MATH_LIB_HEADERS features/mathfunctions/*.h)
# install(FILES ${MATH_LIB_HEADERS} DESTINATION include/mathfunctions)

set(CPACK_PROJECT_NAME ${PROJECT_NAME}) # 定义变量 CPACK_PROJECT_NAME = ${PROJECT_NAME}
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION}) # 定义变量 CPACK_PROJECT_VERSION = ${PROJECT_VERSION}
include(CPack)


# include(spdlog)

# target_link_libraries(test_spdlog ${SPDLOG_LIB})
# target_include_directories(test_spdlog PRIVATE ${SPDLOG_INCLUDE_DIR})

# target_link_libraries(test_spdlog PRIVATE spdlog)

# include(gflag-2.2.2)
# target_link_libraries(${PROJECT_NAME} PRIVATE ${GFLAG_LIB_DIR})
# target_include_directories(${PROJECT_NAME} PRIVATE ${GFLAG_INCLUDE_DIR})

# Configure CCache if available
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache) # Less useful to do it for linking, see edit2
endif(CCACHE_FOUND)



