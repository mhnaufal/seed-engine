#pragma once

#include <miniaudio.h>
#include <string>

namespace seed {
class Audio {
public:
    Audio() = delete;
    explicit Audio(const std::string& path);
    ~Audio();

    auto Play() -> void;
    auto Pause() -> void;
    auto Stop() -> void;

private:
    ma_result m_result{};
    ma_engine m_engine{};
    ma_sound m_sound{};
    std::string m_audio_path{};
};
}