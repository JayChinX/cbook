# 项目工程

## 目录规划

### include dir

存放头文件

## 构建

### 安装依赖并配置环境

```sh
$ conan install . --output-folder=build --build=missing
```

默认 release 构建

### 配置 Cmake 和构建

```sh
$ cd build
$ cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
```

### debug 构建

```sh
# 安装依赖并配置环境
$ conan install . --output-folder=build --build=missing --settings=build_type=Debug
# 配置 Cmake
$ cd build
$ cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug
```
