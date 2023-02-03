# 指定目标机的操作系统和处理器架构
# this is required
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_PROCESSOR aarch64)

# 控制程序的编译和链接
# 将变量设置成完整路径或者文件名
# specify the cross compiler
# 编译 C 代码的程序
SET(CMAKE_C_COMPILER /opt/arm/usr/bin/ppc_74xx-gcc)
# 编译 C++ 代码的程序
SET(CMAKE_CXX_COMPILER /opt/arm/usr/bin/ppc_74xx-g++)

# 代表了一系列的相关文件夹路径的根路径的变更，比如你设置了/opt/arm/,
# 所有的Find_xxx.cmake都会优先根据这个路径下的/usr/lib,/lib等进行查找，
# 然后才会去你自己的/usr/lib和/lib进行查找，如果你有一些库是不被包含在/opt/arm里面的，
# 你也可以显示指定多个值给CMAKE_FIND_ROOT_PATH,比如
# where is the target environment
SET(CMAKE_FIND_ROOT_PATH /opt/arm/ppc_74xx /home/rickk/arm_inst)

# 对FIND_PROGRAM()起作用，有三种取值，NEVER,ONLY,BOTH,
# 第一个表示不在你CMAKE_FIND_ROOT_PATH下进行查找，
# 第二个表示只在这个路径下查找，
# 第三个表示先查找这个路径，再查找全局路径，
# 对于这个变量来说，一般都是调用宿主机的程序，所以一般都设置成NEVER
# search for programs in the build host directories (not necessary)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# 对FIND_LIBRARY()起作用，表示在链接的时候的库的相关选项，因此这里需要设置成ONLY来保证我们的库是在交叉环境中找的.
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# 对FIND_PATH()和FIND_FILE()起作用，一般来说也是ONLY,
# 如果你想改变，一般也是在相关的FIND命令中增加option来改变局部设置，
# 有NO_CMAKE_FIND_ROOT_PATH,ONLY_CMAKE_FIND_ROOT_PATH,BOTH_CMAKE_FIND_ROOT_PATH
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# configure Boost and Qt
# 对于Qt用户来说，需要更改相关的qmake命令切换成嵌入式版本，因此这里需要指定成相应的qmake路径（指定到qmake本身）
SET(QT_QMAKE_EXECUTABLE /opt/qt-embedded/qmake)
# 对于需要boost库的用户来说，相关的boost库路径配置也需要设置，因此这里的路径即ARM下的boost路径，里面有include和lib。
SET(BOOST_ROOT /opt/boost_arm)

# 相关toolChain的编写，之后，你可以灵活的选择到底采用宿主机版本还是开发机版本，
# 之间的区别仅仅是一条-DCMAKE_TOOLCHAIN_FILE=./toolChain.cmake，
# 如果你有很多程序需要做转移，但目标平台是同一个，你仅仅需要写一份toolChain放在一个地方，就可以给所有工程使用。