#pragma once

#include <cstdint>

constexpr int TARGET_FPS = 60;
constexpr uint64_t TARGET_FRAME_TIME = 1000000 / TARGET_FPS;

#ifndef GL_STATIC_DRAW
#    define GL_STATIC_DRAW 0x88E4
#endif
