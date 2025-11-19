#pragma once

#include "../Core/Definitions.h"

#include <string>

namespace seed {
class Texture {
public:
    virtual ~Texture() = default;
    virtual auto GetWidth() -> uint32_t const = 0;
    virtual auto GetHeight() -> uint32_t const = 0;

    virtual auto Bind(uint32_t slot) -> void = 0;
    virtual auto Unbind(uint32_t slot) -> void = 0;

    virtual auto SetData(void* data, uint32_t size) -> void = 0;
};

class Texture2D : public Texture {
public:
    static auto Create(const std::string& path) -> Ref<Texture2D>;
    static auto Create(uint32_t width, uint32_t height) -> Ref<Texture2D>;
};
}