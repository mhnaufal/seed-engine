import os

from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.files import copy


class SeedEngine(ConanFile):
    name = "seed"
    version = "1.0.0"
    description = "Seed Engine"
    settings = "os", "compiler", "build_type", "arch"
    user = "mhnaufal"
    channel = "stable"

    def requirements(self):
        # self.requires("raylib/5.5")
        self.requires("flecs/4.0.4")
        self.requires("spdlog/1.15.3")
        self.requires("sdl/3.2.20")
        self.requires("fmt/11.2.0")
        self.requires("imgui/1.92.2b-docking")

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

    def package(self):
        cmake = CMake(self)
        cmake.install()

        copy(self, "*.h", os.path.join(self.source_folder, "include"), os.path.join(self.package_folder, "include"))
        copy(self, "*lib", src=self.build_folder, dst=os.path.join(self.package_folder, "lib"), keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["seed"]
        self.cpp_info.libdirs = ["lib"]
        self.cpp_info.includedirs = ["include"]
