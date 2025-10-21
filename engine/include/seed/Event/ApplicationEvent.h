#pragma once

#include "Event.h"

#include <sstream>

namespace seed {
class WindowResizeEvent final : public Event {
public:
    WindowResizeEvent(const unsigned int width, const unsigned int height)
        : m_width(width)
          , m_height(height)
    {
    }

    [[nodiscard]] auto inline GetWidth() const -> unsigned int { return m_width; };
    [[nodiscard]] auto inline GetHeight() const -> unsigned int { return m_height; };

    [[nodiscard]] auto ToString() const -> std::string override
    {
        auto ss = std::stringstream{};
        ss << "<Event> WindowResize: (" << m_width << ", " << m_height << ")";
        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);

private:
    unsigned int m_width{}, m_height{};
};

class WindowCloseEvent final : public Event {
public:
    WindowCloseEvent() = default;

    EVENT_CLASS_TYPE(WindowClose);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);
};

class AppTickEvent : public Event {
public:
    AppTickEvent() = default;

    EVENT_CLASS_TYPE(AppTick);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);
};

class AppUpdateEvent final : public Event {
public:
    AppUpdateEvent() = default;

    EVENT_CLASS_TYPE(AppUpdate);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);
};

class AppRenderEvent final : public Event {
public:
    AppRenderEvent() = default;

    EVENT_CLASS_TYPE(AppRender);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);
};
} // namespace seed