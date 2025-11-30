import os

from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.files import copy


class CompressorRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("zlib/1.3.1")
        self.requires("gtest/1.16.0")
        self.requires("rapidjson/1.1.0")
        self.requires("imgui/1.92.2b")
        self.requires("glfw/3.4")
        self.requires("glew/2.2.0")

    def generate(self):
        copy(self, "*glfw*", os.path.join(self.dependencies["imgui"].package_folder,
             "res", "bindings"), os.path.join(self.source_folder, "lib/imgui_backends"))
        copy(self, "*opengl3*", os.path.join(self.dependencies["imgui"].package_folder,
             "res", "bindings"), os.path.join(self.source_folder, "lib/imgui_backends"))

    def layout(self):
        cmake_layout(self)
