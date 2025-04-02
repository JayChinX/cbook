# 项目工程

## 目录规划

### include dir

存放头文件

## 构建

```
conan profile detect --force
```

### 安装依赖并配置环境

```sh
$ conan install . --build=missing
```

默认 release 构建

### 配置 Cmake 和构建

```sh
$ cd build
$ cmake ..
```

### debug 构建

```sh
# 安装依赖并配置环境
$ conan install . --build=missing --settings=build_type=Debug
# 配置 Cmake
$ cd build
$ cmake ..
```
