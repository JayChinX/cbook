# 指定目标机的操作系统和处理器架构
# this is required
# 如果是交叉编译给 Android 平台使用的库，直接使用 Android 官方 NDK 中提供的 toolchain 就好。

# 使用 Android toolchain 路径一定要通过 NDK 所在目录指定：`<NDK>/build/cmake/android.toolchain.cmake`，因为它会使用相对路径访问 NDK 内部其他的资源，否则会出错。