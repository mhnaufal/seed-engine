#include "RendererAPI.h"

namespace seed
{
    /// NOTEX: Place where we switch RendererAPI
    // RendererAPI::API RendererAPI::m_api = API::OPENGL;
    RendererAPI::API RendererAPI::m_api = API::SDL_GPU;
}
