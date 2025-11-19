cmake_minimum_required(VERSION 3.28)

project(
        seed
        VERSION 1.0.0
        DESCRIPTION "Seed Engine"
        LANGUAGES C CXX
)

message("C COMPILER ID                  :" ${CMAKE_C_COMPILER_ID})
message("CXX COMPILER ID                :" ${CMAKE_CXX_COMPILER_ID})
message("C COMPILER FRONTEND VARIANT    :" ${CMAKE_C_COMPILER_FRONTEND_VARIANT})
message("CXX COMPILER FRONTEND VARIANT  :" ${CMAKE_CXX_COMPILER_FRONTEND_VARIANT})
message("CMAKE_BUILD_TYPE               :" ${CMAKE_BUILD_TYPE})

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE CACHE BOOL "" FORCE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_ERROR_DEPRECATED TRUE)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_BUILD_TYPE Debug)
elseif (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(CMAKE_BUILD_TYPE RelWIthDebInfo)
endif ()


set(SOURCE_FILES
        src/Logger.cpp
        src/Application.cpp
        src/Layer.cpp
        src/LayerStack.cpp

        include/seed/Platform/Windows/WindowsWindow.cpp
        include/seed/Platform/Windows/WindowsInput.cpp

        include/seed/Platform/OpenGL/OpenGLContext.cpp
        include/seed/Platform/OpenGL/OpenGLBuffer.cpp
        include/seed/Platform/OpenGL/OpenGLVertexArray.cpp
        include/seed/Platform/OpenGL/OpenGLRendererAPI.cpp
        include/seed/Platform/OpenGL/OpenGLShader.cpp
        include/seed/Platform/OpenGL/OpenGLTexture.cpp

        include/seed/Platform/SDL_GPU/SDL_GPUContext.cpp
        include/seed/Platform/SDL_GPU/SDL_GPUBuffer.cpp


        include/seed/ImGui/ImGuiLayer.cpp

        include/seed/Renderer/Shader.cpp
        include/seed/Renderer/Renderer.cpp
        include/seed/Renderer/Buffer.cpp
        include/seed/Renderer/VertexArray.cpp
        include/seed/Renderer/RendererAPI.cpp
        include/seed/Renderer/RenderCommand.cpp
        include/seed/Renderer/OrthographicCamera.cpp
        include/seed/Renderer/PerspectiveCamera.cpp
        include/seed/Renderer/Texture.cpp
        include/seed/Renderer/Renderer2D.cpp

        include/seed/Audio/Audio.cpp

        ${CMAKE_SOURCE_DIR}/thirdparty/imgui/backends/imgui_impl_opengl3.cpp
        ${CMAKE_SOURCE_DIR}/thirdparty/imgui/backends/imgui_impl_sdl3.cpp
        ${CMAKE_SOURCE_DIR}/thirdparty/imgui/backends/imgui_impl_sdlgpu3.cpp
        ${CMAKE_SOURCE_DIR}/thirdparty/imgui/backends/imgui_impl_sdlrenderer3.cpp
        ${CMAKE_SOURCE_DIR}/thirdparty/glad/glad.c
)

set(HEADER_FILES
        include/seed/seed.h
        include/seed/Logger.h
        include/seed/Application.h
        include/seed/Window.h
        include/seed/Layer.h
        include/seed/LayerStack.h
        include/seed/Input.h
        include/seed/KeyCodes.h
        include/seed/MouseCodes.h

        include/seed/Core/Definitions.h
        include/seed/Core/Timestep.h

        include/seed/Event/Event.h
        include/seed/Event/ApplicationEvent.h
        include/seed/Event/KeyboardEvent.h
        include/seed/Event/MouseEvent.h

        include/seed/Platform/Windows/WindowsWindow.h
        include/seed/Platform/Windows/WindowsInput.h

        include/seed/Platform/OpenGL/OpenGLContext.h
        include/seed/Platform/OpenGL/OpenGLBuffer.h
        include/seed/Platform/OpenGL/OpenGLVertexArray.h
        include/seed/Platform/OpenGL/OpenGLRendererAPI.h
        include/seed/Platform/OpenGL/OpenGLShader.h
        include/seed/Platform/OpenGL/OpenGLTexture.h

        include/seed/Platform/SDL_GPU/SDL_GPUContext.h
        include/seed/Platform/SDL_GPU/SDL_GPUBuffer.h

        include/seed/ImGui/ImGuiLayer.h

        include/seed/Renderer/GraphicsContext.h
        include/seed/Renderer/Shader.h
        include/seed/Renderer/Renderer.h
        include/seed/Renderer/Buffer.h
        include/seed/Renderer/VertexArray.h
        include/seed/Renderer/RendererAPI.h
        include/seed/Renderer/RenderCommand.h
        include/seed/Renderer/OrthographicCamera.h
        include/seed/Renderer/PerspectiveCamera.h
        include/seed/Renderer/Texture.h
        include/seed/Renderer/Renderer2D.h

        include/seed/Audio/Audio.h

        ${CMAKE_SOURCE_DIR}/thirdparty/imgui/backends/imgui_impl_opengl3.h
        ${CMAKE_SOURCE_DIR}/thirdparty/imgui/backends/imgui_impl_opengl3_loader.h
        ${CMAKE_SOURCE_DIR}/thirdparty/imgui/backends/imgui_impl_sdl3.h
        ${CMAKE_SOURCE_DIR}/thirdparty/imgui/backends/imgui_impl_sdlgpu3.h
        ${CMAKE_SOURCE_DIR}/thirdparty/imgui/backends/imgui_impl_sdlgpu3_shaders.h
        ${CMAKE_SOURCE_DIR}/thirdparty/imgui/backends/imgui_impl_sdlrenderer3.h
        ${CMAKE_SOURCE_DIR}/thirdparty/glad/glad.h
        ${CMAKE_SOURCE_DIR}/thirdparty/glad/khrplatform.h
        ${CMAKE_SOURCE_DIR}/thirdparty/stb/stb_image.h
        ${CMAKE_SOURCE_DIR}/thirdparty/stb/stb_image_write.h
)

add_library(
        ${PROJECT_NAME}
        STATIC
        ${HEADER_FILES}
        ${SOURCE_FILES}
)

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/seed
        ${CMAKE_CURRENT_SOURCE_DIR}/include/seed/Audio
        ${CMAKE_CURRENT_SOURCE_DIR}/include/seed/Core
        ${CMAKE_CURRENT_SOURCE_DIR}/include/seed/Event
        ${CMAKE_CURRENT_SOURCE_DIR}/include/seed/ImGui
        ${CMAKE_CURRENT_SOURCE_DIR}/include/seed/Platform/OpenGL
        ${CMAKE_CURRENT_SOURCE_DIR}/include/seed/Platform/SDL_GPU
        ${CMAKE_CURRENT_SOURCE_DIR}/include/seed/Platform/Windows
        ${CMAKE_CURRENT_SOURCE_DIR}/include/seed/Renderer
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui/backends
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/stb
)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            /W4 /permissive- /std:c++17 /EHsc
            $<$<CONFIG:Debug>:/Od /Zi /RTCs /RTCu /RTC1>
            $<$<CONFIG:RelWithDebInfo>:/O2 /Zi>
            $<$<CONFIG:Release>:/O2>
    )
elseif (CMAKE_GNU_COMPILER_ID)
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Wextra -Wall -Wpedantic
            $<$<CONFIG:Debug>:-g>
            $<$<CONFIG:RelWithDebInfo>:-O2 -g>
            $<$<CONFIG:Release>:-O2>
    )
endif ()

# #######################
# # Flecs
# #######################
# find_package(flecs REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE flecs::flecs_static)
# target_include_directories(${PROJECT_NAME} PRIVATE ${flecs_INCLUDE_DIRS})

#######################
# spdlog
#######################
find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
target_include_directories(${PROJECT_NAME} PRIVATE ${spdlog_INCLUDE_DIRS})

#######################
# SDL3
#######################
find_package(SDL3 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL3_INCLUDE_DIRS})

#######################
# Dear ImGui
#######################
find_package(imgui REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
target_include_directories(${PROJECT_NAME} PRIVATE ${imgui_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/thirdparty/imgui/backends)

# #######################
# # eigen
# #######################
# find_package(Eigen3 REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE Eigen3::Eigen)
# target_include_directories(${PROJECT_NAME} PRIVATE ${Eigen3_INCLUDE_DIRS})

#######################
# glm
#######################
find_package(glm REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)
target_include_directories(${PROJECT_NAME} PUBLIC ${glm_INCLUDE_DIRS})

#######################
# miniaudio
#######################
find_package(miniaudio REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC miniaudio)
target_include_directories(${PROJECT_NAME} PUBLIC ${miniaudio_INCLUDE_DIRS})

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC wsock32 ws2_32)
endif ()
