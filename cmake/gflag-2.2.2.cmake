include(ExternalProject)

set(GFLAG_ROOT          ${CMAKE_BINARY_DIR}/thirdparty/gflag-2.2.2)

# 指定编译好的静态库文件的路径
set(GFLAG_LIB_DIR       ${GFLAG_ROOT}/lib)
# 指定头文件所在的目录
set(GFLAG_INCLUDE_DIR   ${GFLAG_ROOT}/include)

# 指定git仓库地址
set(GFLAG_URL           https://github.com/gflags/gflags/archive/v2.2.2.zip)
# set(SPDLOG_GIT_TAG  v1.4.1)  # 指定版本
# set(SPDLOG_GIT_URL      https://github.com/gabime/spdlog.git)  # 指定git仓库地址
# # 指定配置指令（注意此处修改了安装目录，否则默认情况下回安装到系统目录）
set(GFLAG_CONFIGURE     cd ${GFLAG_ROOT}/src/gflag-2.2.2 && cmake -D CMAKE_INSTALL_PREFIX=${GFLAG_ROOT} .)
# 指定编译指令（需要覆盖默认指令，进入我们指定的SPDLOG_ROOT目录下）
set(GFLAG_MAKE          cd ${GFLAG_ROOT}/src/gflag-2.2.2 && make)
 # 指定安装指令（需要覆盖默认指令，进入我们指定的SPDLOG_ROOT目录下）
set(GFLAG_INSTALL       cd ${GFLAG_ROOT}/src/gflag-2.2.2 && make install)

ExternalProject_Add(gflag-2.2.2
        URL                   ${GFLAG_URL}
        DOWNLOAD_NAME         gflag-2.2.2.zip
        PREFIX                ${GFLAG_ROOT}
        CONFIGURE_COMMAND     ${GFLAG_CONFIGURE}
        BUILD_COMMAND         ${GFLAG_MAKE}
        INSTALL_COMMAND       ${GFLAG_INSTALL}
)
# ExternalProject_Add(SPDLOG
#         PREFIX            ${SPDLOG_ROOT}
#         GIT_REPOSITORY    ${SPDLOG_GIT_URL}
#         GIT_TAG           ${SPDLOG_GIT_TAG}
#         CONFIGURE_COMMAND ${SPDLOG_CONFIGURE}
#         BUILD_COMMAND     ${SPDLOG_MAKE}
#         INSTALL_COMMAND   ${SPDLOG_INSTALL}
# )

# # 指定编译好的静态库文件的路径
# set(SPDLOG_LIB       ${SPDLOG_ROOT}/lib/spdlog/libspdlog.a)
# # 指定头文件所在的目录
# set(SPDLOG_INCLUDE_DIR   ${SPDLOG_ROOT}/include)