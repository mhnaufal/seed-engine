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

if (MSVC)
    set(CMAKE_CXX_FLAGS "/W4 /permissive-")
elseif (CMAKE_GNU_COMPILER_ID)
    set(CMAKE_CXX_FLAGS "-Wextra -Wall -Wpedantic")
endif ()

set(SOURCE_FILES
        src/Logger.cpp
        src/Application.cpp
        src/Window.cpp
)

set(HEADER_FILES
        include/seed/seed.h
        include/seed/Logger.h
        include/seed/Application.h
        include/seed/Window.h
        include/seed/Event/Event.h
        include/seed/Event/ApplicationEvent.h
        include/seed/Event/KeyboardEvent.h
        include/seed/Event/MouseEvent.h
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
        include/seed
        include/seed/Event
)

target_compile_options(${PROJECT_NAME} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/EHsc>)

# #######################
# # Raylib
# #######################
# find_package(raylib REQUIRED)
# target_link_libraries(${PROJECT_NAME} PUBLIC raylib)
# target_include_directories(${PROJECT_NAME} PUBLIC ${raylib_INCLUDE_DIRS})

#######################
# Flecs
#######################
find_package(flecs REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE flecs::flecs_static)
target_include_directories(${PROJECT_NAME} PRIVATE ${flecs_INCLUDE_DIRS})

#######################
# spdlog
#######################
find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
target_include_directories(${PROJECT_NAME} PRIVATE ${spdlog_INCLUDE_DIRS})

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC wsock32 ws2_32)
endif ()
