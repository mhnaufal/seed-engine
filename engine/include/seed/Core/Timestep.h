#pragma once

namespace seed {
class Timestep {
public:
    explicit Timestep(const float time = 0.0f)
        : m_time(time)
    {
    }

    operator float() const { return m_time; }

    Timestep& operator=(const Timestep& other)
    {
        m_time = other.m_time;
        return *this;
    }

    float& operator=(const float& other)
    {
        m_time = other;
        return m_time;
    }

    auto GetSeconds() const -> float { return m_time; }
    auto GetMilliSeconds() const -> float { return m_time * 1000.0f; }
    auto GetNanoSeconds() const -> float { return m_time * 1000.0f * 1000.0f; }

private:
    float m_time{};
};
} // namespace seed