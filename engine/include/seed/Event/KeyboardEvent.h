#pragma once

#include "Event.h"

#include <sstream>

namespace seed {

class KeyboardEvent : public Event {
public:
    auto inline GetKeyCode() const -> int { return m_key_code; };
    EVENT_CLASS_CATEGORY(EventCategoryKeyboard);

protected:
    KeyboardEvent(int key_code)
        : m_key_code(key_code)
    {
    }

private:
    int m_key_code{};
};

class KeyboardPressedEvent : public KeyboardEvent {
public:
    KeyboardPressedEvent(int key_code, int repeat_count)
        : KeyboardEvent(key_code)
        , m_repeat_count(repeat_count)
    {
    }
    auto inline GetRepeatCount() const -> int { return m_repeat_count; };
    auto ToString() const -> std::string override
    {
        auto ss = std::stringstream{};
        ss << "KeyboardPressedEvent: " << GetKeyCode() << "(" << m_repeat_count << ")";
        return ss.str();
    }
    EVENT_CLASS_TYPE(KeyPressed);

private:
    int m_repeat_count{};
};

class KeyboardReleaseEvent : public KeyboardEvent {
public:
    KeyboardReleaseEvent(int key_code)
        : KeyboardEvent(key_code)
    {
    }
    auto ToString() const -> std::string override
    {
        auto ss = std::stringstream{};
        ss << "KeyboardReleased: " << GetKeyCode();
        return ss.str();
    }
    EVENT_CLASS_TYPE(KeyReleased);
};

} // namespace seed