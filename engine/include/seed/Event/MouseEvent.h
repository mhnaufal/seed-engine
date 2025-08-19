#pragma once

#include "Event.h"

#include <sstream>

namespace seed {
class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(float x, float y)
        : m_mouse_x(x)
        , m_mouse_y(y)
    {
    }
    auto inline GetX() const -> float { return m_mouse_x; }
    auto inline GetY() const -> float { return m_mouse_y; }

    auto ToString() const -> std::string override
    {
        auto ss = std::stringstream{};
        ss << "MouseMovedEvent: " << "(" << m_mouse_x << ", " << m_mouse_y << ")";
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMoved);
    EVENT_CLASS_CATEGORY(EventCategoryMouse);

private:
    float m_mouse_x{}, m_mouse_y{};
};

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(float x_offset, float y_offset)
        : m_offset_x(x_offset)
        , m_offset_y(y_offset)
    {
    }

    auto inline GetXOfsset() const -> float { return m_offset_x; }
    auto inline GetYOfsset() const -> float { return m_offset_y; }

    auto ToString() const -> std::string override
    {
        auto ss = std::stringstream{};
        ss << "MouseScrolledEvent: " << "(" << m_offset_x << ", " << m_offset_y << ")";
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled);
    EVENT_CLASS_CATEGORY(EventCategoryMouse);

private:
    float m_offset_x{}, m_offset_y{};
};

class MouseButtonEvent : public Event {
public:
    auto inline GetMouseButton() const -> int { return m_button; }
    EVENT_CLASS_CATEGORY(EventCategoryMouse);

protected:
    MouseButtonEvent(int button)
        : m_button(button)
    {
    }

    int m_button{};
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    MouseButtonPressedEvent(int button)
        : MouseButtonEvent(button)
    {
    }

    auto ToString() const -> std::string override
    {
        auto ss = std::stringstream{};
        ss << "MouseButtonPressed: " << m_button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed);
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    MouseButtonReleasedEvent(int button)
        : MouseButtonEvent(button)
    {
    }

    auto ToString() const -> std::string override
    {
        auto ss = std::stringstream{};
        ss << "MouseButtonReleased: " << m_button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonReleased);
};

} // namespace seed