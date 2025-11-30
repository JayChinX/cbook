## Repo snapshot for AI coding agents

This repository is a small C++ project (project name: `books`) that builds with CMake and uses ImGui + GLFW + GLEW for a minimal GUI application. Key locations:

- Top-level build: `CMakeLists.txt` (uses C++17, exports compile_commands.json)
- Main entry: `src/main.cpp` — initializes GLFW/ImGui and calls `app::Render()`
- UI: `src/app.h` — contains `app::Render()` implementation (ImGui code)
- Core logic (CLI-style book manager): `src/books.cpp`, `src/books.h`, `src/book.h`
- Bindings for ImGui backends: `bindings/` (GLFW + OpenGL3 + loader)
- Features and tests: `features/` and `test/` (subdirectories added conditionally)

Quick facts the agent should know

- Build system: uses CMake. Typical local flow:

  - `conan install . --build=missing` (optional, repo references conan in README)
  - `mkdir build && cd build && cmake ..` (CMake config)
  - `cmake --build .` or `make` (build outputs to `build/bin`)
  - Default CMake build type is Debug in `CMakeLists.txt` (overridable)

- Binaries and artifacts:

  - Executable name is `books` (set by project name in `CMakeLists.txt`)
  - `CMakeLists.txt` sets `EXECUTABLE_OUTPUT_PATH` to `${PROJECT_BINARY_DIR}/bin`

- Tests/fuzzers: controlled by CMake options `BUILD_TESTING` and `BUILD_FUZZING`.

Project-specific patterns and conventions

- Single-file UI: `app::Render()` is inline in `src/app.h`. Small UI changes typically happen directly in this header rather than a separate .cpp.
- Mixed UI + CLI code: `src/books.cpp` implements a file-backed, text-file-based book database (reads/writes `text.txt`), not an embedded database. Agents should not assume a DB; existing code uses plain files and malloc/new freely.
- C bindings and ImGui: ImGui backend files live in `bindings/` and are added to the executable via the glob in `CMakeLists.txt`.
- Conditional feature modules: optional features (e.g., `features/mathfunctions`) are enabled via `-DUSE_MYMATH=ON` or by adding subdirectories in CMake.

Where to change behavior safely

- To modify UI: edit `src/app.h` (small, immediate visual effect).
- To change startup/render flow: edit `src/main.cpp` (initialization order, OpenGL version string passed to `ImGui_ImplOpenGL3_Init`).
- To change data handling: edit `src/books.cpp` and `src/book.h`. Note: these functions perform direct file operations on `text.txt` in the working directory.

Common pitfalls and constraints

- Use of C-style memory and file I/O: `books.cpp` mixes malloc/free, new/delete, raw char buffers and std::string. When refactoring, prefer consistent ownership and avoid mismatched free/delete.
- GUI code depends on GLFW, ImGui and GLEW. If building on other platforms, ensure the CMake finds the correct packages (CMake uses find_package for imgui, glfw3, glew).
- Running the GUI requires an X/Window/GL context; CI headless runs will need an offscreen/context wrapper or skip GUI.

Examples (explicit references)

- To change window size: update the size arguments in `glfwCreateWindow(1280, 720, ...)` inside `src/main.cpp`.
- To add a new menu item that triggers an action in `books.cpp`, add the ImGui menu item in `src/app.h` and expose a small API in `books.h` (e.g., `void save_snapshot(const char *path)`), then call it from `app::Render()`.

Developer workflows for local dev

- Quick local build (macOS/zsh):

  mkdir -p build
  cd build
  conan install .. --build=missing # optional if you use conan
  cmake ..
  cmake --build .

- Run the GUI binary from the `build/bin` directory so `text.txt` (working file) is found relative to cwd.

Where to look next (important files)

- `CMakeLists.txt` — build flags, dependencies, outputs
- `conanfile.py` — dependency management (if using conan)
- `src/main.cpp` — startup/shutdown and ImGui/GLFW orchestration
- `src/app.h` — UI entry and immediate place for UI edits
- `src/books.cpp`, `src/books.h`, `src/book.h` — data model and file-backed storage
- `bindings/` — ImGui backend implementation files included in build

If anything above is unclear or you want more examples (tests, refactors, or modernization suggestions—e.g., replace text file with sqlite or fix ownership issues), tell me which area to expand and I will iterate.
