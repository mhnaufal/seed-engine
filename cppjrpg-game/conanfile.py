import os

from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.files import copy


class CppJRPG(ConanFile):
    name = "cpp-jrpg"
    version = "1.0.0"
    settings = "os", "compiler", "build_type", "arch"
    description = "C++ JRPG Style Game"
    user = "mhnaufal"
    channel = "stable"

    def requirements(self):
        self.requires("seed/1.0.0@mhnaufal/stable")

    def layout(self):
        self.folders.build = "build"
        self.folders.generators = "generators"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

        copy(self,
             "*.h",
             src=os.path.join(
                 self.dependencies["seed"].package_folder, "include", "seed"),
             dst=os.path.join(self.build_folder, "include", "seed")
             )

    def package(self):
        cmake = CMake(self)
        cmake.install()
