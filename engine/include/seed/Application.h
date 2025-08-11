#pragma once

namespace seed {

class Logger;
class Window;

class Application {
public:
    Application();

    ~Application();

    auto run() const -> void;

private:
    bool m_is_app_running = false;
    seed::Window* m_window = nullptr;
};
} // namespace seed
