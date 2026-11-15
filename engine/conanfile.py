import os

from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.files import copy


class SeedEngine(ConanFile):
    name = "seed"
    version = "1.0.1"
    description = "Seed Engine"
    settings = "os", "compiler", "build_type", "arch"
    user = "mhnaufal"
    # channel = "stable"
    channel = "sdlgpu"
    # package_type = "library"
    # options = {"shared": [True, False]}
    # default_options = {"shared": False} # TODO: change to dynamic lib

    def requirements(self):
        # self.requires("flecs/4.1.6")
        self.requires("spdlog/1.17.0")
        self.requires("sdl/3.4.16")
        # self.requires("fmt/12.1.0")
        self.requires("imgui/1.92.9b-docking")
        # self.requires("eigen/5.0.1")
        # self.requires("ozz-animation/0.14.1")
        self.requires("miniaudio/0.11.25")
        self.requires("glm/1.0.3")
        self.requires("assimp/6.0.5")
        self.requires("stb/cci.20230920")
        self.requires("glad/2.0.8")

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

        copy(self, "*.h", os.path.join(self.source_folder, "include"),
             os.path.join(self.package_folder, "include"))
        copy(self, "*lib", src=self.build_folder,
             dst=os.path.join(self.package_folder, "lib"), keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["seed"]
        self.cpp_info.libdirs = ["lib"]
        self.cpp_info.includedirs = ["include"]
