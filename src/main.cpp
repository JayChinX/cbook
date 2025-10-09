#include <cassert>
#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "books.h"

#include <imgui.h>

#include "../bindings/imgui_impl_glfw.h"
#include "../bindings/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include "Application.hpp"

#ifdef USE_MYMATH
#include <mathfunctions.h>
#else
#include <cmath>
#endif

int main(int, char **)
{
    //     double inputValue = 5.0;
    // #ifdef USE_MYMATH
    //     double outputValue = mySquare(inputValue);
    //     std::cout << "mySquare func called!" << std::endl;
    // #else
    //     double outputValue = pow(inputValue, 2);

    //     std::cout << "pow func called!" << std::endl;
    // #endif
    //     std::cout << "result: " << outputValue << std::endl;
    //     std::cout << "result: " << __cplusplus << std::endl;
    //     start();
    //     printf("This code running.\n");
    // 初始化 GLFW 库
    if (!glfwInit()) {
        return -1;  // 初始化失败则退出
    }

    // 创建一个 1280x720 的窗口
    GLFWwindow *window = glfwCreateWindow(1280, 720, "ImGui GLFW OpenGL3 Example", nullptr, nullptr);
    if (!window) {
        glfwTerminate();  // 创建失败则清理并退出
        return -1;
    }

    // 将当前窗口的 OpenGL 上下文设置为活动状态
    glfwMakeContextCurrent(window);

    // 初始化 ImGui
    IMGUI_CHECKVERSION();    // 检查 ImGui 版本
    ImGui::CreateContext();  // 创建 ImGui 上下文
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    // io.Fonts->AddFont(const ImFontConfig *font_cfg);  // 获取 IO 对象
    ImGui::StyleColorsDark();                         // 设置暗色主题
    ImGui_ImplGlfw_InitForOpenGL(window, true);       // 初始化 GLFW 后端
    ImGui_ImplOpenGL3_Init("#version 120");           // 初始化 OpenGL3 后端

    // 主循环，直到窗口关闭
    while (!glfwWindowShouldClose(window)) {
        // 处理 GLFW 事件（如键盘、鼠标输入）
        glfwPollEvents();

        // 开始新的一帧
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 调用封装的 Render 函数绘制界面
        app::Render();

        // 渲染 ImGui 内容
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);  // 获取窗口大小
        glViewport(0, 0, display_w, display_h);                  // 设置 OpenGL 视口
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);                // 设置背景颜色
        glClear(GL_COLOR_BUFFER_BIT);                            // 清除颜色缓冲区
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());  // 渲染 ImGui 数据

        // 交换前后缓冲区，显示渲染结果
        glfwSwapBuffers(window);
    }

    // 清理资源
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
