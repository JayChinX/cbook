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
        

    def layout(self):
        cmake_layout(self)
