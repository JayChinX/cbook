#!/usr/bin/env bash

# build.sh - convenient build helper for this repository
# Aligns with README.md: run conan install in build/ and then cmake configure+build

set -euo pipefail

ROOT_DIR=$(pwd)
BUILD_DIR="$ROOT_DIR/build"

BUILD_TYPE=Release
JOBS=0
DO_CLEAN=0
DO_INSTALL=0
DO_PACKAGE=0
DO_REINSTALL=0
BUILD_SH_DEBUG=0

# 提示信息函数
usage() {
cat <<'EOF'
Usage: $(basename "$0") [options]

Options:
  -h, --help        Show this help
  -t, --type TYPE   Build type: Debug or Release (default: Release)
  -j, --jobs N      Parallel jobs for build (passed to cmake --build)
  --clean           Remove build/ and output/ then exit
  --install         Run 'cmake --install' after successful build
  --package         Run 'cmake --build --target package' after build

Examples:
  # Default Release build
  ./build.sh

  # Debug build with 4 jobs and install
  ./build.sh -t Debug -j 4 --install

  # Clean build directory
  ./build.sh --clean

EOF
}

# 命令行参数解析
while [[ $# -gt 0 ]]; do
  case "$1" in
    -h|--help) usage; exit 0;;
    -t|--type) BUILD_TYPE="$2"; shift 2;;
    -j|--jobs) JOBS="$2"; shift 2;;
    --clean) DO_CLEAN=1; shift;;
  --install) DO_INSTALL=1; shift;;
  --reinstall) DO_REINSTALL=1; shift;;
  --debug) BUILD_SH_DEBUG=1; shift;;
    --package) DO_PACKAGE=1; shift;;
    --) shift; break;;
    -*) echo "Unknown option: $1"; usage; exit 1;;
    *) break;;
  esac
done

# clean build dir and output if requested, then exit
if [[ $DO_CLEAN -eq 1 ]]; then
  # INSTALL_PREFIX is computed after argument parsing below
  echo "Cleaning ${BUILD_DIR} and output/ ..."
  rm -rf "${BUILD_DIR}" "${ROOT_DIR}/output"
  echo "Clean done."
  exit 0
fi

echo "Build type: ${BUILD_TYPE}"
echo "Build dir: ${BUILD_DIR}"

mkdir -p "${BUILD_DIR}"
pushd "${BUILD_DIR}" >/dev/null

# Install Conan dependencies in build dir (per README)
echo "Running: conan install .. --build=missing -s build_type=${BUILD_TYPE}"
if command -v conan >/dev/null 2>&1; then
  conan install .. --build=missing -s build_type=${BUILD_TYPE}
else
  echo "Warning: conan not found in PATH. Skipping conan install." >&2
fi

# Configure CMake
echo "Configuring CMake (type=${BUILD_TYPE})..."

# Detect Conan-generated toolchain/prefix (prefer config-specific generators e.g. build/Release/generators)
# 判断conan生成的构建目录是否存在，并查找构建文件
BIN_DIR="${BUILD_DIR}/${BUILD_TYPE}"
TOOLCHAIN_FILE=""
PREFIX_DIR=""
if [[ -f "${BIN_DIR}/generators/conan_toolchain.cmake" ]]; then
  TOOLCHAIN_FILE="${BIN_DIR}/generators/conan_toolchain.cmake"
  PREFIX_DIR="${BIN_DIR}/generators"
elif [[ -f "${BUILD_DIR}/generators/conan_toolchain.cmake" ]]; then
  TOOLCHAIN_FILE="${BUILD_DIR}/generators/conan_toolchain.cmake"
  PREFIX_DIR="${BUILD_DIR}/generators"
else
  CT=$(find "${BUILD_DIR}" -type f -name conan_toolchain.cmake -print -quit 2>/dev/null || true)
  if [[ -n "$CT" ]]; then
    TOOLCHAIN_FILE="$CT"
    PREFIX_DIR="$(dirname "$CT")"
  fi
fi
# CMake configure args
CMARGS=( "-DCMAKE_POLICY_DEFAULT_CMP0091=NEW" "-DCMAKE_BUILD_TYPE=${BUILD_TYPE}" )
if [[ -n "$TOOLCHAIN_FILE" ]]; then
  CMARGS+=( "-DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE}" )
fi
if [[ -n "$PREFIX_DIR" ]]; then
  CMARGS+=( "-DCMAKE_PREFIX_PATH=${PREFIX_DIR}" )
fi

# Ensure install prefix is configured at configure-time to avoid passing --prefix to cmake --install
# Recompute INSTALL_PREFIX now that BUILD_TYPE may have been changed by args.
INSTALL_PREFIX="$ROOT_DIR/output/${BUILD_TYPE}"
CMARGS+=( "-DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX}" )

echo "Configuring CMake into: ${BIN_DIR}"
echo "Using toolchain: ${TOOLCHAIN_FILE:-<none>}"
echo "Using prefix path: ${PREFIX_DIR:-<none>}"

echo "Running: cmake -S ${ROOT_DIR} -B ${BIN_DIR} ${CMARGS[*]}"
cmake -S "${ROOT_DIR}" -B "${BIN_DIR}" "${CMARGS[@]}" # -S and -B are CMake 3.13+ only
# cmake -S "${CODE_SOURCE_DIR}" -B "${BUILD_DIR}" "${CMARGS[@]}"

# Build with cmake --build
echo "Building from: ${BIN_DIR}"
if [[ ${JOBS} -gt 0 ]]; then
  echo "Building with ${JOBS} parallel jobs"
  cmake --build "${BIN_DIR}" --parallel ${JOBS}
else
  cmake --build "${BIN_DIR}"
fi

if [[ ${DO_INSTALL} -eq 1 ]]; then
  echo "Installing to ${INSTALL_PREFIX}..."
  # Optionally remove previous install to force a full reinstall
  if [[ ${DO_REINSTALL} -eq 1 ]]; then
    echo "-- Reinstall requested: removing ${INSTALL_PREFIX} before install"
    rm -rf "${INSTALL_PREFIX}"
  fi
  # Use the install target via cmake --build so we can pass VERBOSE=1 reliably to the underlying generator
  if [[ ${BUILD_SH_DEBUG} -ne 0 ]]; then
    set -x
  fi
  cmake --build "${BIN_DIR}" --target install --config "${BUILD_TYPE}" -- VERBOSE=1
fi

if [[ ${DO_PACKAGE} -eq 1 ]]; then
  echo "Packaging..."
  cmake --build "${BIN_DIR}" --target package
  # Collect generated package files (common archive formats) into the output folder
  PKG_OUT_DIR="${INSTALL_PREFIX}/packages"
  mkdir -p "${PKG_OUT_DIR}"
  echo "Moving generated packages to ${PKG_OUT_DIR} ..."
  # find packages in the build dir and move them; be tolerant if none found
  find "${BIN_DIR}" -maxdepth 1 -type f \( -name "*.tar.gz" -o -name "*.tgz" -o -name "*.zip" -o -name "*.dmg" -o -name "*.pkg" \) -print0 |
    xargs -0 -I{} bash -c 'mv "$1" "$2"' -- {} "${PKG_OUT_DIR}" || true
fi

popd >/dev/null

# Summarize results with accurate, config-aware paths
BIN_OUTPUT_DIR="${BIN_DIR}/bin"
PKG_OUT_DIR="${INSTALL_PREFIX}/packages"

echo
echo "========================================"
echo "✅ Build Completed Successfully!"
echo "----------------------------------------"
echo "  🛠️  Build type   : ${BUILD_TYPE}"
echo "  📁 Build tree   : ${BIN_DIR}"
if [[ -d "${BIN_OUTPUT_DIR}" ]]; then
  echo "  🚀 Binaries     : ${BIN_OUTPUT_DIR}"
else
  echo "  🚫 Binaries     : (no binaries found at ${BIN_OUTPUT_DIR})"
fi
if [[ ${DO_INSTALL} -eq 1 ]]; then
  echo "  📦 Installed to : ${INSTALL_PREFIX}"
fi
if [[ ${DO_PACKAGE} -eq 1 ]]; then
  echo "  🎁 Packages dir : ${PKG_OUT_DIR}"
fi
echo "========================================"
echo "🎉 All done. Happy coding!"
echo
