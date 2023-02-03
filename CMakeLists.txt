cmake_minimum_required(VERSION 3.0.0)
project(books VERSION 0.1.0)

include_directories(${PROJECT_SOURCE_DIR}/include)

# add_subdirectory(./src)

# add_subdirectory(./test)

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

set(CPACK_PROJECT_NAME ${PROJECT_NAME}) # 定义变量 CPACK_PROJECT_NAME = ${PROJECT_NAME}
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION}) # 定义变量 CPACK_PROJECT_VERSION = ${PROJECT_VERSION}
include(CPack)

# # 编译参数 debug/release
# set(CMAKE_BUILD_TYPE "Debug")
# # set(CMAKE_BUILD_TYPE Release)

# if (NOT CMAKE_BUILD_TYPE)
#     set(CMAKE_BUILD_TYPE Release)
#     message("Setting default build type to Release")
# endif()


# target_include_directories(${PROJECT_NAME} PUBLIC common)

# target_link_libraries(${PROJECT_NAME} common)

include(CTest)
enable_testing()

# 将要进行测试的文件编译为静态库
file(GLOB_RECURSE TEST_SRC src/book.cpp src/books.cpp)
add_library(book_lib STATIC ${TEST_SRC})

add_subdirectory(test)
add_subdirectory(lib/googletest)
add_subdirectory(jnitest)
add_subdirectory(common)



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
option(USE_MYMATH "Use code provided math implementation" ON)
# configure_file (Config.h.in Config.h)

if (USE_MYMATH)
    #add_definitions 为源码库编译添加一个宏
    # cmake .. -DUSE_MYMATH=OFF/0
    # 或者
    # cmake .. -DUSE_MYMATH=ON/1
    add_definitions(-DUSE_MYMATH)
    add_subdirectory(mathfunctions)
    # 用list命令来在列表中保存需要连接的库和需要导入的头文件。cmake中的list时以;分割的字符串。
    # list(APPEND <list> [<element> ...])
    # APPEND为修改命令，为list中添加元素。
    # <list>为list的变量名，如果当前作用域中不存在这个变量名则作为空, list为其添加
    # [<element> ...]为list添加的元素
    # ps:也可以用set来创建list，例如：set(var a b c d) var的值为a;b;c;d;然后照样可以用list的命令来处理var
    list(APPEND EXTRA_LIBS mathfunctions)
    list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/mathfunctions")
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTRA_LIBS})

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}" ${EXTRA_INCLUDES})

