import sys
import os
import argparse
import subprocess


def main() -> bool:
    parser = argparse.ArgumentParser(description="Build C++ JRPG Game")
    parser.add_argument("--build-type", choices=["Debug", "Release"],
                        default="Debug", required=False, help="Build type (default: Debug, RelWithDebInfo)")
    parser.add_argument("--run", action="store_true",
                        required=False, help="Run the game after building")
    args = parser.parse_args()

    command_install = [
        "conan",
        "install",
        "--profile",
        "../tools/conanprofiles/win_msvc_194",
        "--build=missing",
        "-s",
        f"build_type={args.build_type}",
        "."
    ]

    print(f"Executing: {' '.join(command_install)}")
    is_success = subprocess.run(command_install, check=True).returncode == 0
    if not is_success:
        print("Conan install failed.")
        return False

    command_build = [
        "conan",
        "build",
        "--profile",
        "../tools/conanprofiles/win_msvc_194",
        "-s",
        f"build_type={args.build_type}",
        "."
    ]

    print(f"Executing: {' '.join(command_build)}")
    is_success = subprocess.run(command_build, check=True).returncode == 0
    if not is_success:
        print("Conan build failed.")
        return False

    if args.run:
        command_run = [
            "build\Debug\cppjrpg.exe",
        ]
        print(f"Executing: {' '.join(command_run)}")
        is_success = subprocess.run(command_run, check=True).returncode == 0
        if not is_success:
            print("Failed to run the game.")
            return False

    return True


if __name__ == "__main__":
    result = main()
    sys.exit(result)
