#!/bin/bash

# 安全的shell脚本，建议在脚本开头添加以下设置
#  -e参数 在执行到某个命令返回非0时立即结束脚本。
#  -u参数 将未设置的参数或者变量视为错误并退出脚本。
#  -f参数 禁用文件名通配符。
#  -o pipefail选项 在管道中某个命令出错时立即报错返回
set -euf -o pipefail

BUILD_DIR="build"
INSTALL_DIR=$(pwd)/output
rm -rf "${BUILD_DIR}"

# Configure 编译命令，与 vs 中 task配置类似
# BUILD_TYPE=Debug
# cmake -B "${BUILD_DIR}" \
#     -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR}" \
#     -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
#     -DCPACK_OUTPUT_FILE_PREFIX="${INSTALL_DIR}"

# 配合 cmakepresets.json
# cmake -B "${BUILD_DIR}" 生成 makefile 文件等信息到 BUILD_DIR 文件夹，如 build 文件夹
cmake -B "${BUILD_DIR}"

# Build 开始编译命令
# cmake --build "${BUILD_DIR}"

# 配合 cmakepresets.json
cmake --build --preset=default

cd "${BUILD_DIR}"

# Test 执行单元测试
# make test CTEST_OUTPUT_ON_FAILURE=TRUE GTEST_COLOR=TRUE
# GTEST_COLOR=TRUE ctest --output-on-failure

# Install 打包命令 安装到本地
# cmake --build . --target install
# cmake --install . --prefix "../output" # After cmake 3.15
# make install

# Package 开始打包
# cmake --build . --target package
make package

cd -
