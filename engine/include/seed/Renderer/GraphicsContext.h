#pragma once

namespace seed {
class GraphicsContext {
public:
    virtual ~GraphicsContext() = default;

    virtual auto Init() -> void = 0;
    virtual auto SwapBuffers() -> void = 0;
};
}