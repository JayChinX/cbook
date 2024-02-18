#!/bin/bash
API=21                                                # api
NDK=/Users/qin/Library/Android/sdk/ndk/21.1.6352462   # ndk
TOOLCHAIN=$NDK/toolchains/llvm/prebuilt/darwin-x86_64 # 编译器 clang
OUTPUT=$(pwd)/android                                 # 输出文件夹
ABIS=(armeabi-v7a arm64-v8a x86 x86_64)               # 编译平台 (.. ..) 表示数组

SYSROOT=$TOOLCHAIN/sysroot # 配置编译环境c语言的头文件环境

# 把configure，make写到一个function中（方便编译不同ABI时复用）
# 运行./configure --help查看配置 裁剪
# 换行后不要用空格，可以使用tab

function build {
    echo "Build FFmpeg for $CPU..."
    ./configure \
        --prefix=$PREFIX \
        --enable-small \
        --enable-shared \
        --enable-neon \
        --enable-jni \
        --enable-mediacodec \
        --enable-decoder=h264_mediacodec \
        --enable-hwaccel=h264_mediacodec \
        --enable-cross-compile \
        --disable-static \
        --disable-gpl \
        --disable-postproc \
        --disable-programs \
        --disable-asm \
        --disable-ffmpeg \
        --disable-ffplay \
        --disable-ffprobe \
        --disable-avdevice \
        --disable-iconv \
        --disable-doc \
        --disable-symver \
        --cross-prefix=$CROSS_PREFIX \
        --target-os=android \
        --arch=$ARCH \
        --cpu=$CPU \
        --cc=$CC \
        --cxx=$CXX \
        --sysroot=$SYSROOT \
        --extra-cflags="-Os -fpic $OPTIMIZE_CFLAGS"
    make clean
    make -j 8
    make install
    echo "Buld FFmpeg for $CPU success"
}

# 编译 armeabi_v7a 平台 so
function build_armeabi_v7a {
    ARCH=arm                                                # 平台
    CPU=armv7-a                                             # cpu 架构
    CC=$TOOLCHAIN/bin/armv7a-linux-androideabi$API-clang    # c 编译器
    CXX=$TOOLCHAIN/bin/armv7a-linux-androideabi$API-clang++ # c++ 编译器
    SYSROOT=$TOOLCHAIN/sysroot                              #
    #交叉编译工具目录,对应关系如下(我们这里使用的是armv8a，根据自己的需要进行配置)
    # armv8a -> arm64 -> aarch64-linux-android-
    # armv7a -> arm -> arm-linux-androideabi-
    # x86 -> x86 -> i686-linux-android-
    # x86_64 -> x86_64 -> x86_64-linux-android-
    CROSS_PREFIX=$TOOLCHAIN/bin/arm-linux-androideabi- # abi 前缀
    PREFIX=$OUTPUT/armeabi-v7a                         # 输出文件前缀
    OPTIMIZE_CFLAGS="-mfloat-abi=softfp -mfpu=vfp -marm -march=$CPU "
    build
}

function build_arm64_v8a {
    ARCH=arm64
    CPU=armv8-a
    CC=$TOOLCHAIN/bin/aarch64-linux-android$API-clang
    CXX=$TOOLCHAIN/bin/aarch64-linux-android$API-clang++
    SYSROOT=$TOOLCHAIN/sysroot
    CROSS_PREFIX=$TOOLCHAIN/bin/aarch64-linux-android-
    PREFIX=$OUTPUT/arm64-v8a
    OPTIMIZE_CFLAGS="-march=$CPU"
    build
}

function build_x86 {
    ARCH=x86
    CPU=x86
    CC=$TOOLCHAIN/bin/i686-linux-android$API-clang
    CXX=$TOOLCHAIN/bin/i686-linux-android$API-clang++
    SYSROOT=$TOOLCHAIN/sysroot
    CROSS_PREFIX=$TOOLCHAIN/bin/i686-linux-android-
    PREFIX=$OUTPUT/x86
    OPTIMIZE_CFLAGS="-march=i686 -mtune=intel -mssse3 -mfpmath=sse -m32"
    build
}

function build_x86_64 {
    ARCH=x86_64
    CPU=x86-64
    CC=$TOOLCHAIN/bin/x86_64-linux-android$API-clang
    CXX=$TOOLCHAIN/bin/x86_64-linux-android$API-clang++
    SYSROOT=$TOOLCHAIN/sysroot
    CROSS_PREFIX=$TOOLCHAIN/bin/x86_64-linux-android-
    PREFIX=$OUTPUT/x86_64
    OPTIMIZE_CFLAGS="-march=$CPU -msse4.2 -mpopcnt -m64 -mtune=intel"
    build
}

# 编译好的文件，复制到指定文件夹
function merge_output {
    ABI=${1}
    ABI_OS_DIR=$OUTPUT/jniLibs/$ABI

    rm -rf $ABI_OS_DIR
    mkdir -p $ABI_OS_DIR
    cp -rf $OUTPUT/$ABI/lib/*.so $ABI_OS_DIR/

    rm -rf $OUTPUT/include
    cp -r $OUTPUT/$ABI/include $OUTPUT/include
}

rm -rf $OUTPUT/jniLibs # clear 历史文件
mkdir -p $OUTPUT/jniLibs

for ABI in "${ABIS[@]}"; do # 遍历  读取数组元素 `${数组名[下标]}`   ${array_name[@]} 使用 @ 符号可以获取数组中的所有元素
    if [ $ABI == "armeabi-v7a" ]; then
        build_armeabi_v7a
    elif [ $ABI == "arm64-v8a" ]; then
        build_arm64_v8a
    else
        eval build_$ABI
    fi

    merge_output $ABI
done
