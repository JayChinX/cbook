# 项目工程

## 目录规划

### include dir

```sh
src/                # 源代码目录
├── main.cpp        # 程序入口，初始化 GLFW/ImGui 并调用 app::Render()
├── app.h           # 包含 app::Render() 的实现（UI 代码）
├── books.cpp       # 文件支持的书籍管理核心逻辑
├── books.h         # books.cpp 的头文件
├── book.h          # 定义单本书的结构和相关操作
bindings/           # ImGui 后端绑定（GLFW + OpenGL3 + loader）
features/           # 可选功能模块（例如 mathfunctions）
test/               # 测试代码目录
CMakeLists.txt      # 顶层 CMake 构建文件
```

## 依赖和环境

```sh
$ conan profile detect --force
```

自动检测当前系统的配置并生成一个 Conan 配置文件（profile）

> 运行 conan profile detect --force 后，Conan 会：
> 检测当前系统的编译器（例如 GCC、Clang 或 MSVC）。
> 检测编译器版本、操作系统类型、CPU 架构等。
> 生成一个新的配置文件，通常命名为 default，并存储在 ~/.conan/profiles/ 目录下

```sh
$ conan install .. --build=missing
```

生成并安装依赖到当前 build 目录（Release 为默认）：
这会生成 conan_toolchain.cmake（如果仓库使用 conan 的 CMake 集成）

如果需要 Debug 构建，请显式指定：

```sh
$ conan install .. --build=missing -s build_type=Debug
```

默认 release 构建

## 命令构建

```sh
$ cd build
$ cmake ..
```

指定构建类型（Debug/Release）更明确且可重现：

```sh
$ cmake .. -DCMAKE_BUILD_TYPE=Release
$ cmake .. -DCMAKE_BUILD_TYPE=Debug
```

```sh
$ cmake --build . # 在运行它之前，应该已运行过 cmake ..（或等效命令）来配置构建目录并选择生成器/目标文件
```

## Cmake Tools 插件构建

使用 VSCode 的 CMake Tools 插件，可以在 VSCode GUI 内选择构建类型（Debug/Release）并运行构建命令。
