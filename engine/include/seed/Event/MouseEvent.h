#pragma once

#include <Event.h>
#include <MouseCodes.h>

#include <sstream>

namespace seed {
class MouseMovedEvent final : public Event {
public:
    MouseMovedEvent(const float x, const float y)
        : m_mouse_x(x)
          , m_mouse_y(y)
    {
    }

    [[nodiscard]] auto inline GetX() const -> float { return m_mouse_x; }
    [[nodiscard]] auto inline GetY() const -> float { return m_mouse_y; }

    [[nodiscard]] auto ToString() const -> std::string override
    {
        auto ss = std::stringstream{};
        ss << "<Event> MouseMoved: " << "(" << m_mouse_x << ", " << m_mouse_y << ")";
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMoved);
    EVENT_CLASS_CATEGORY(EventCategoryMouse);

private:
    float m_mouse_x{}, m_mouse_y{};
};

class MouseScrolledEvent final : public Event {
public:
    MouseScrolledEvent(const float x_offset, const float y_offset)
        : m_offset_x(x_offset)
          , m_offset_y(y_offset)
    {
    }

    [[nodiscard]] auto inline GetXOffset() const -> float { return m_offset_x; }
    [[nodiscard]] auto inline GetYOffset() const -> float { return m_offset_y; }

    [[nodiscard]] auto ToString() const -> std::string override
    {
        auto ss = std::stringstream{};
        ss << "<Event> MouseScrolled: " << "(" << m_offset_x << ", " << m_offset_y << ")";
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled);
    EVENT_CLASS_CATEGORY(EventCategoryMouse);

private:
    float m_offset_x{}, m_offset_y{};
};

class MouseButtonEvent : public Event {
public:
    [[nodiscard]] auto inline GetMouseButton() const -> MouseCode { return m_button; }
    EVENT_CLASS_CATEGORY(EventCategoryMouse);

protected:
    explicit MouseButtonEvent(MouseCode button)
        : m_button(button)
    {
    }

    MouseCode m_button{};
};

class MouseButtonPressedEvent final : public MouseButtonEvent {
public:
    explicit MouseButtonPressedEvent(int button)
        : MouseButtonEvent(button)
    {
    }

    [[nodiscard]] auto ToString() const -> std::string override
    {
        auto ss = std::stringstream{};
        ss << "<Event> MouseButtonPressed: " << m_button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed);
};

class MouseButtonReleasedEvent final : public MouseButtonEvent {
public:
    explicit MouseButtonReleasedEvent(MouseCode button)
        : MouseButtonEvent(button)
    {
    }

    [[nodiscard]] auto ToString() const -> std::string override
    {
        auto ss = std::stringstream{};
        ss << "<Event> MouseButtonReleased: " << m_button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonReleased);
};
} // namespace seed