include(FetchContent)
FetchContent_Declare(
  googletest
# URL https://github.com/google/googletest/archive/c875c4e2249ec124c24f72141b3780c22256fd44.zip
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.0
# URL_HASH  SHA256=${FILE_HASH}
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest) 是将Google Test框架作为外部项目导入到CMake的当前项目中。这个命令会下载、构建并将Google Test的源代码和构建结果添加到当前项目中，使得可以在项目中直接使用Google Test的功能。
FetchContent_MakeAvailable(googletest)

