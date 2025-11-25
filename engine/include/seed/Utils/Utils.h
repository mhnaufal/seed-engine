#pragma once

#include <Logger.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <SDL3/SDL_error.h>

namespace seed
{
#define LENGTH(x) (sizeof(x) / sizeof((x)[0]))

#define SEED_SDL_CHECK_ERROR(ERROR_MSG, RETURN)                                                                        \
    do                                                                                                                 \
    {                                                                                                                  \
        const char* error = SDL_GetError();                                                                            \
        if (error == nullptr || *error != '\0')                                                                        \
        {                                                                                                              \
            SEED_LOG_ERROR("{}: {}\n", ERROR_MSG, error);                                                              \
            SDL_ClearError();                                                                                          \
            return RETURN;                                                                                             \
        }                                                                                                              \
    }                                                                                                                  \
    while (0);

    inline auto read_shader_file(const std::filesystem::path& path) -> std::vector<Uint8>
    {
        std::ifstream file(path.string().c_str(), std::ios::binary | std::ios::ate);

        const std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<Uint8> code(size);

        file.read(reinterpret_cast<char*>(code.data()), size);
        return code;
    }
} // namespace seed
