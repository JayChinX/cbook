cmake_minimum_required(VERSION 3.15.0)

project(imgui_backends VERSION 0.1.0)

file(GLOB_RECURSE IMGUI_BACKENDS_SRC imgui_backends.h imgui_impl_glfw.cpp
                imgui_impl_glfw.h
                imgui_impl_opengl3.cpp
                imgui_impl_opengl3.h
                imgui_impl_opengl3_loader.h)
add_library(imgui_backends STATIC ${IMGUI_BACKENDS_SRC})

# 包含头文件
# PUBLIC 表示不仅当前库需要包含这些头文件，使用该库的目标也需要包含这些头文件
# PRIVATE 表示只有当前库需要包含这些头文件，使用该库的目标不需要包含这些头文件
# INTERFACE 表示只有使用该库的目标需要包含这些
target_include_directories(imgui_backends PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# 定义宏变量
target_compile_definitions(imgui_backends PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLEW)

find_package(imgui REQUIRED CONFIG)
find_package(glfw3 REQUIRED)
find_package(glew REQUIRED)
message(STATUS "IMGUI_SRC_DIR: ${IMGUI_SRC_DIR}")

# 链接库 
# PUBLIC 表示不仅当前库需要链接这些库，使用该库的目标也需要链接这些库
# PRIVATE 表示只有当前库需要链接这些库，使用该库的目标不需要链接这些库
# INTERFACE 表示只有使用该库的目标需要链接这些库，当前库不需要链接这些库
target_link_libraries(imgui_backends PUBLIC imgui::imgui glfw GLEW::GLEW)

file(GLOB_RECURSE IMGUI_BACKENDS_HEADERS
                 CONFIGURE_DEPENDS
                 ${CMAKE_CURRENT_SOURCE_DIR}/*.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
if(IMGUI_BACKENDS_HEADERS)
        install(FILES ${IMGUI_BACKENDS_HEADERS} DESTINATION include/imgui_backends)
endif()

