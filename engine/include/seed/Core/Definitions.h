#pragma once

#include <cstdint>

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include "glad.h"

constexpr int TARGET_FPS = 60;
constexpr uint64_t TARGET_FRAME_TIME = 10000 / TARGET_FPS;

