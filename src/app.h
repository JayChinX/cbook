#ifndef __APP_H__
#define __APP_H__

#include <imgui.h>

#include <cmath>

namespace app {
// Render 函数：负责绘制 ImGui 界面
inline void Render()
{
    // 开始一个新的 ImGui 窗口
    // ImGui::Begin("Made By Touken", nullptr,
    //              ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar |
    //                  ImGuiWindowFlags_NoMove);
    bool my_tool_active = true;

    // Create a window called "My First Tool", with a menu bar.
    ImGui::Begin("My First Tool", &my_tool_active,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */
            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */
            }
            if (ImGui::MenuItem("Close", "Ctrl+W")) {
                my_tool_active = false;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    // Generate samples and plot them
    float samples[100];
    for (int n = 0; n < 100; n++)
        samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
    ImGui::PlotLines("Samples", samples, 100);
    // 获取当前窗口的大小
    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    // 设置窗口的大小和位置
    ImGui::SetWindowSize(windowSize);
    ImGui::SetWindowPos(ImVec2(0, 0));

    // 显示一段简单的文本
    ImGui::Text("Hello! This is a minimal ImGui application. 你好");

    // 结束当前窗口
    ImGui::End();
}
}  // namespace app

#endif  // __APP_H__