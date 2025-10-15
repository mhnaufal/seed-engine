#pragma once

#include <functional>
#include <string>

namespace seed {

enum class EventType : int {
    None = 0,

    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMoved,

    AppTick,
    AppUpdate,
    AppRender,

    KeyPressed,
    KeyReleased,
    KeyTyped,

    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled,
};

enum class EventCategory : int {
    None = 0,
    EventCategoryApplication = 1 << 0,
    EventCategoryInput = 1 << 1,
    EventCategoryKeyboard = 1 << 2,
    EventCategoryMouse = 1 << 3,
    EventCategoryMouseButton = 1 << 4,
};

#define EVENT_CLASS_TYPE(type)                                                                                         \
    static auto GetStaticType() -> EventType /* To get type at runtime */                                              \
    {                                                                                                                  \
        return EventType::##type;                                                                                      \
    }                                                                                                                  \
    virtual auto GetEventType() const -> EventType override                                                            \
    {                                                                                                                  \
        return GetStaticType();                                                                                        \
    }                                                                                                                  \
    virtual auto GetName() const -> const char* override                                                               \
    {                                                                                                                  \
        return #type;                                                                                                  \
    }

#define EVENT_CLASS_CATEGORY(category)                                                                                 \
    auto virtual GetCategoryFlags() const->int override                                                                \
    {                                                                                                                  \
        return static_cast<int>(EventCategory::##category);                                                            \
    };

class Event {
    // NOTE: class EventDispatcher bisa ngakses private & protected nya Event
    friend class EventDispatcher;

public:
    // NOTE: GetEventType() utk "formalitas" polymorph saja.
    // Untuk ngasih tau class Event ada child class XXX.
    virtual auto GetEventType() const -> EventType = 0;
    virtual auto GetCategoryFlags() const -> int = 0;
    virtual auto GetName() const -> const char* = 0;
    virtual auto ToString() const -> std::string { return GetName(); };

    inline auto GetHandled() const -> bool { return m_handled; }

protected:
    bool m_handled = false;
};

class EventDispatcher {
    template<typename T>
    using EventFn = std::function<bool(T&)>;

public:
    EventDispatcher(Event& event)
        : m_event(event)
    {
    }

    // TODO: function apa yg dijalankan di sini(?)
    template<typename T>
    bool Dispatch(EventFn<T> func)
    {
        if (m_event.GetEventType() == T::GetStaticType()) {
            m_event.m_handled = func(*(T*)&m_event);
            return true;
        }
        return false;
    }

private:
    Event& m_event;
};

} // namespace seed