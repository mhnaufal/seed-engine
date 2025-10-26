# Seed

A Little Tiny Miny Game Engine with TOON POWER 🛠️

## Dependency

1. [Conan](https://docs.conan.io/2.0/reference/commands/install.html)
2. [CMake](https://cmake.org/)
3. [Flecs](https://www.flecs.dev/)
4. [spdlog](https://github.com/gabime/spdlog)
5. [SDL3](https://wiki.libsdl.org/SDL3/CategoryAPI)
6. [Eigen3](https://eigen.tuxfamily.org/index.php?title=Main_Page#Documentation)

## Installation Seed Engine

1. Clone

    ```shell
    git clone https://github.com/mhnaufal/seed-engine.git
    ```

2. `cd engine`

3. Install

    ```shell
    conan install --profile ..\tools\conanprofiles\win_msvc_194 --build=missing -s build_type=Debug .
    ```

4. Build

    ```shell
    conan build --profile ..\tools\conanprofiles\win_msvc_194 --build=missing -s build_type=Debug .
    ```

5. Export the lib

    ```shell
    conan export-pkg --profile ..\tools\conanprofiles\win_msvc_194 -s build_type=Debug .
    ```

6. Now you can use the header files and lib for developing your game! You just need to include it as conan depedencies or grab those files manually

7. To delete the exported packaged

    ```shell
    conan remove seed/1.0.0@mhnaufal/stable
    ```

### Simpler Commands

```shell
python build.py --export --build-type Debug
```

```shell
python build.py --run --build-type Debug
```

---

## Previews

![Checkpoint 1](./engine/assets/checkpoint1.png)

![Checkpoint 2](./engine/assets/checkpoint2.png)

## TODO

1. Make the engine as Shared Library
2. ✅ Differentiate build type
3. Make each folder wrapped in namespace

## References

1. [The Cherno Game Engine Series](https://www.youtube.com/@TheCherno)
