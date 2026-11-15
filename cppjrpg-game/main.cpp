#include "Sandbox2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
// #include <seed/Platform/OpenGL/OpenGLShader.h>
#include <seed/seed.h>

class GameApplication : public seed::Application {
public:
    GameApplication()
    {
        // m_game_layer = new GameLayer();
        // PushLayer(m_game_layer);

        m_game_layer = new Sandbox2D{};
        PushLayer(m_game_layer);
    }

    ~GameApplication()
    {
        PopLayer(m_game_layer);
        delete m_game_layer;
    }

private:
    seed::Layer* m_game_layer{};
};

seed::Application* CreateApplication()
{
    return new GameApplication();
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** __argv)
{
    SEED_PROFILE_BEGIN_SESSION("Startup", "SeedProfile-Startup.json");
    auto game = CreateApplication();
    SEED_PROFILE_END_SESSION();

    SEED_PROFILE_BEGIN_SESSION("Runtime", "SeedProfile-Runtime.json");
    game->run();
    SEED_PROFILE_END_SESSION();

    SEED_PROFILE_BEGIN_SESSION("Shutdown", "SeedProfile-Shutdown.json");
    delete game;
    SEED_PROFILE_END_SESSION();

    return 0;
}
