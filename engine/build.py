import sys
import os
import argparse
import subprocess


def main() -> bool:
    parser = argparse.ArgumentParser(description="Build Seed Engine")
    parser.add_argument("--build-type", choices=["Debug", "Release"],
                        default="Debug", required=False, help="Build type (default: Debug)")
    parser.add_argument("--export", action="store_true",
                        required=False, help="Epxort the package after building")
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

    if args.export:
        command_export = [
            "conan",
            "export-pkg",
            "--profile",
            "../tools/conanprofiles/win_msvc_194",
            "-s",
            f"build_type={args.build_type}",
            "."
        ]

        print(f"Executing: {' '.join(command_export)}")
        is_success = subprocess.run(command_export, check=True).returncode == 0
        if not is_success:
            print("Conan export failed.")
            return False

    return True


if __name__ == "__main__":
    result = main()
    sys.exit(result)
