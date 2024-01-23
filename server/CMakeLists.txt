
set(TEST ${CMAKE_PROJECT_NAME}_test)

# common
set(SERVER_TEST server_test)

# 设置使用独立的 asio 还是 Boost.Asio
option(USE_STANDALONE_ASIO "set ON to use standalone Asio instead of Boost.Asio" OFF)

# 是否启用 openssl 证书，就是 https
option(USE_OPENSSL "set OFF to build without OpenSSL" ON)

add_library(${SERVER_TEST} INTERFACE)

# # 包含头文件  SERVER_TEST 的 .h 文件相互可以相互引用
target_include_directories(${SERVER_TEST} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# 查找 Threads
find_package(Threads REQUIRED)

# 链接
target_link_libraries(${SERVER_TEST} INTERFACE Threads::Threads)

if(USE_STANDALONE_ASIO)
    # 查找、链接 独立的 asio
    target_compile_definitions(${SERVER_TEST} INTERFACE ASIO_STANDALONE)

    # There is no canonical way to use Asio from CMake.
    # In particular, Asio does not support CMake natively.
    # However, Conan and Vcpkg do provide CMake support on their own.
    # Prefer the CMake target and fall back to finding asio.hpp.
    if(NOT TARGET asio::asio)
        find_package(asio)
    endif()

    if(TARGET asio::asio)
        target_link_libraries(${SERVER_TEST} INTERFACE asio::asio)
    else()
        find_path(ASIO_PATH asio.hpp)

        if(NOT ASIO_PATH)
            message(FATAL_ERROR "Standalone Asio not found")
        endif()

        target_include_directories(${SERVER_TEST} SYSTEM INTERFACE ${ASIO_PATH})
    endif()
else()
    # 查找、链接 boot.asio
    find_package(Boost 1.53.0 COMPONENTS system REQUIRED)
    target_link_libraries(${SERVER_TEST} INTERFACE Boost::boost Boost::system)

    find_package(Boost 1.53.0 COMPONENTS thread REQUIRED)
    target_link_libraries(${SERVER_TEST} INTERFACE  Boost::thread)

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9)
        # 用于向target添加编译定义 用于 ”输出“宏定义 FUN_DEBUG 到 C 源码中 ，该语句是否执行由 CMakeLists.txt 中的 FUN_TRACE 决定
        target_compile_definitions(${SERVER_TEST} INTERFACE USE_BOOST_REGEX)
        find_package(Boost 1.53.0 COMPONENTS regex REQUIRED)
        target_link_libraries(${SERVER_TEST} INTERFACE Boost::regex)
    endif()
endif()

if(WIN32)
    # windows 链接 ws2_32 wsock32
    target_link_libraries(${SERVER_TEST} INTERFACE ws2_32 wsock32)
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
    target_compile_definitions(${SERVER_TEST} INTERFACE HAVE_OPENSSL)
    target_link_libraries(${SERVER_TEST} INTERFACE OpenSSL::SSL OpenSSL::Crypto)
endif()

if(NOT MSVC)
    add_compile_options(-Wall -Wextra -Wsign-conversion)

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        add_compile_options(-Wthread-safety)
    endif()
else()
    add_compile_options(/W1)
endif()

find_package(Boost 1.53.0 COMPONENTS filesystem)

if(Boost_FOUND)
    file(GLOB_RECURSE WEB_SRC web/*.cpp)
    file(GLOB_RECURSE API_SRC api/*.cpp)

    add_executable(http_examples http_examples.cpp ${API_SRC} ${WEB_SRC})
    target_link_libraries(http_examples ${SERVER_TEST} Boost::boost Boost::filesystem simple-web-server)
    set_target_properties(http_examples PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)

    # sync
    add_executable(asio_client_test asio_client_test.cpp)
    target_link_libraries(asio_client_test ${SERVER_TEST} Boost::boost Boost::filesystem)

    add_executable(asio_server_test asio_server_test.cpp)
    target_link_libraries(asio_server_test ${SERVER_TEST} Boost::boost Boost::filesystem)

    # async
    add_executable(asio_client_async asio_client_async.cpp)
    target_link_libraries(asio_client_async ${SERVER_TEST} Boost::boost Boost::filesystem)

    add_executable(asio_server_async asio_server_async.cpp)
    target_link_libraries(asio_server_async ${SERVER_TEST} Boost::boost Boost::filesystem)

    if(OPENSSL_FOUND)
        add_executable(https_examples https_examples.cpp)
        target_link_libraries(https_examples ${SERVER_TEST} Boost::boost Boost::filesystem)
        set_target_properties(https_examples PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
    endif()
endif()

