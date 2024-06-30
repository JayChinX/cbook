# 指定目标机的操作系统和处理器架构
# this is required
# 如果是交叉编译给 Android 平台使用的库，直接使用 Android 官方 NDK 中提供的 toolchain 就好。

# 使用 Android toolchain 路径一定要通过 NDK 所在目录指定：`<NDK>/build/cmake/android.toolchain.cmake`，因为它会使用相对路径访问 NDK 内部其他的资源，否则会出错。

cmake_minimum_required(VERSION 3.10)
project(MyAndroidLibrary VERSION 1.0.0 LANGUAGES CXX)

SET(ANDROID_ABI "arm64-v8a")
SET(ANDROID_NATIVE_API_LEVEL 21)
SET(CMAKE_BUILD_TYPE "Release")
# set(CMAKE_TOOLCHAIN_FILE "${ANDROID_NDK_HOME}/build/cmake/android.toolchain.cmake")
set(CMAKE_TOOLCHAIN_FILE "../../../Library/Android/sdk/ndk/25.2.9519653/build/cmake/android.toolchain.cmake")

set(ANDROID_ABI "arm64-v8a")
set(ANDROID_NATIVE_API_LEVEL 21)
set(CMAKE_BUILD_TYPE "Release")
