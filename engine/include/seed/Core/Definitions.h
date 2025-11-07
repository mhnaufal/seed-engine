#pragma once

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM

#include <cstdint>
#include <memory>

constexpr int TARGET_FPS = 60;
constexpr uint64_t TARGET_FRAME_TIME = 10000 / TARGET_FPS;

namespace seed {
template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T>
using Ref = std::shared_ptr<T>;
}