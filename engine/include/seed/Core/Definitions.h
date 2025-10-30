#pragma once

#include <cstdint>

constexpr int TARGET_FPS = 60;
constexpr uint64_t TARGET_FRAME_TIME = 1000000 / TARGET_FPS;

#define GL_BOOL 0x8B56
#define GL_FLOAT_MAT2 0x8B5A
#define GL_FLOAT_MAT3 0x8B5B
#define GL_FLOAT_MAT4 0x8B5C
#define GL_INT 0x1404
#define GL_ZERO 0

#define GL_STATIC_DRAW 0x88E4

#define GL_DEPTH_BUFFER_BIT 0x00000100
