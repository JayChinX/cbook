cmake_minimum_required(VERSION 3.7)

project(Simple-Web-Server)

# 设置使用独立的 asio 还是 Boost.Asio
option(USE_STANDALONE_ASIO "set ON to use standalone Asio instead of Boost.Asio" OFF)

# 当前目录是否是 cmake的所在目录，打开测试
if(CMAKE_SOURCE_DIR STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    option(BUILD_TESTING "set ON to build library tests" ON)
else()
    option(BUILD_TESTING "set ON to build library tests" OFF)
endif()

# Fuzz测试
option(BUILD_FUZZING "set ON to build library fuzzers" OFF)

# 是否启用 openssl 证书，就是 https
option(USE_OPENSSL "set OFF to build without OpenSSL" ON)

# lib
add_library(simple-web-server INTERFACE)

# 包含头文件
if(CMAKE_SOURCE_DIR STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    target_include_directories(simple-web-server INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
else()
    target_include_directories(simple-web-server SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
endif()

# 查找 Threads
find_package(Threads REQUIRED)
# 链接
target_link_libraries(simple-web-server INTERFACE Threads::Threads)

if(USE_STANDALONE_ASIO)
# 查找、链接 独立的 asio
    target_compile_definitions(simple-web-server INTERFACE ASIO_STANDALONE)
    # There is no canonical way to use Asio from CMake.
    # In particular, Asio does not support CMake natively.
    # However, Conan and Vcpkg do provide CMake support on their own.
    # Prefer the CMake target and fall back to finding asio.hpp.
    if(NOT TARGET asio::asio)
        find_package(asio)
    endif()
    if(TARGET asio::asio)
        target_link_libraries(simple-web-server INTERFACE asio::asio)
    else()
        find_path(ASIO_PATH asio.hpp)
        if(NOT ASIO_PATH)
            message(FATAL_ERROR "Standalone Asio not found")
        endif()
        target_include_directories(simple-web-server SYSTEM INTERFACE ${ASIO_PATH})
    endif()
else()
# 查找、链接 boot.asio
    find_package(Boost 1.53.0 COMPONENTS system REQUIRED)
    target_link_libraries(simple-web-server INTERFACE Boost::boost Boost::system)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9)
        # 注入宏变量
        target_compile_definitions(simple-web-server INTERFACE USE_BOOST_REGEX)
        find_package(Boost 1.53.0 COMPONENTS regex REQUIRED)
        target_link_libraries(simple-web-server INTERFACE Boost::regex)
    endif()
endif()

if(WIN32)
# windows 链接 ws2_32 wsock32
    target_link_libraries(simple-web-server INTERFACE ws2_32 wsock32)
endif()

if(APPLE)
# apple 设置 openssl 的位置
    if(EXISTS /usr/local/opt/openssl)
        set(OPENSSL_ROOT_DIR /usr/local/opt/openssl)
    elseif(EXISTS /opt/homebrew/opt/openssl)
        set(OPENSSL_ROOT_DIR /opt/homebrew/opt/openssl)
    endif()
endif()

# 查找 OpenSSL
if(USE_OPENSSL)
    find_package(OpenSSL)
endif()

# 找到 OpenSSL  链接
if(OPENSSL_FOUND)
    target_compile_definitions(simple-web-server INTERFACE HAVE_OPENSSL)
    target_link_libraries(simple-web-server INTERFACE OpenSSL::SSL OpenSSL::Crypto)
endif()

# If Simple-Web-Server is not a sub-project: 不是库形式，编译为 可执行文件
if(CMAKE_SOURCE_DIR STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    if(NOT MSVC)
        add_compile_options(-Wall -Wextra -Wsign-conversion)
        if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
            add_compile_options(-Wthread-safety)
        endif()
    else()
        add_compile_options(/W1)
    endif()

    find_package(Boost 1.53.0 COMPONENTS filesystem)
    if(Boost_FOUND)
        add_executable(http_examples http_examples.cpp)
        target_link_libraries(http_examples simple-web-server Boost::boost Boost::filesystem)
        set_target_properties(http_examples PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
        if(OPENSSL_FOUND)
            add_executable(https_examples https_examples.cpp)
            target_link_libraries(https_examples simple-web-server Boost::boost Boost::filesystem)
            set_target_properties(https_examples PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
        endif()
     endif()

    install(FILES asio_compatibility.hpp server_http.hpp client_http.hpp server_https.hpp client_https.hpp crypto.hpp utility.hpp status_code.hpp mutex.hpp DESTINATION include/simple-web-server)
endif()

# 编译测试子目录
if(BUILD_TESTING OR BUILD_FUZZING)
    if(BUILD_TESTING)
        enable_testing()
    endif()
    add_subdirectory(tests)
endif()
