#include "Audio.h"
#include "Logger.h"

namespace seed {
Audio::Audio(const std::string& path)
{
    SEED_LOG_INFO("Initializing Miniaudio Engine");
    m_audio_path = path;
    m_result = ma_engine_init(nullptr, &m_engine);
    if (m_result != ma_result::MA_SUCCESS) {
        SEED_LOG_ERROR("Failed to initialize Miniaudio Engine");
    }
}

Audio::~Audio()
{
    SEED_LOG_INFO("Destroying Miniaudio Engine");
    ma_engine_uninit(&m_engine);
}

auto Audio::Play() -> void
{
    ma_engine_play_sound(&m_engine, m_audio_path.c_str(), nullptr);
}

auto Audio::Pause() -> void
{
}

auto Audio::Stop() -> void
{
}
}