#pragma once

#include <Event.h>
#include <Input.h>

#include <sstream>

namespace seed {
class KeyboardEvent : public Event {
public:
    [[nodiscard]] auto inline GetKeyCode() const -> KeyCode { return m_key_code; };
    EVENT_CLASS_CATEGORY(EventCategoryKeyboard);

protected:
    explicit KeyboardEvent(const KeyCode key_code)
        : m_key_code(key_code)
    {
    }

private:
    KeyCode m_key_code{};
};

class KeyboardPressedEvent final : public KeyboardEvent {
public:
    KeyboardPressedEvent(const KeyCode key_code, const int repeat_count)
        : KeyboardEvent(key_code)
          , m_repeat_count(repeat_count)
    {
    }

    [[nodiscard]] auto inline GetRepeatCount() const -> int { return m_repeat_count; };

    [[nodiscard]] auto ToString() const -> std::string override
    {
        auto ss = std::stringstream{};
        ss << "KeyboardPressedEvent: " << GetKeyCode() << "(" << m_repeat_count << ")";
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed);

private:
    int m_repeat_count{};
};

class KeyboardReleaseEvent final : public KeyboardEvent {
public:
    explicit KeyboardReleaseEvent(const KeyCode key_code)
        : KeyboardEvent(key_code)
    {
    }

    [[nodiscard]] auto ToString() const -> std::string override
    {
        auto ss = std::stringstream{};
        ss << "KeyboardReleased: " << GetKeyCode();
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased);
};
} // namespace seed