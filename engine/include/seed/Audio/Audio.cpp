#include "Audio.h"
#include "Logger.h"

namespace seed {
Audio::Audio(const std::string& path)
{
    SEED_LOG_INFO("Initializing Miniaudio Engine");
    m_audio_path = path;
    m_result = ma_engine_init(nullptr, &m_engine);
    m_result = ma_sound_init_from_file(&m_engine, m_audio_path.c_str(), 0, nullptr, nullptr, &m_sound);
    if (m_result != ma_result::MA_SUCCESS) {
        SEED_LOG_FATAL_ERROR("Failed to initialize Miniaudio Engine: {}", static_cast<int>(m_result));
    }
}

Audio::~Audio()
{
    SEED_LOG_INFO("Destroying Miniaudio Engine");
    ma_sound_uninit(&m_sound);
    ma_engine_uninit(&m_engine);
}

auto Audio::Play() -> void
{
    // ma_engine_play_sound(&m_engine, m_audio_path.c_str(), nullptr);
    ma_sound_start(&m_sound);
}

auto Audio::Pause() -> void
{
    // TODO: fix
    ma_sound_stop(&m_sound);
}

auto Audio::Stop() -> void
{
    ma_sound_stop(&m_sound);
}
}