#pragma once

#include "Event/ApplicationEvent.h"
#include "Event/Event.h"

#include <memory>

namespace seed {

class Logger;
class Window;

class Application {
public:
    Application();

    ~Application();

    auto run() const -> void;

    auto OnEvent(seed::Event& e) -> void;

private:
    auto OnWindowClose(WindowCloseEvent& e) -> bool;

    bool m_is_app_running = false;
    std::unique_ptr<seed::Window> m_window = nullptr;
};
} // namespace seed
