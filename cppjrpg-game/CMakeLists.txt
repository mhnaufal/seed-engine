cmake_minimum_required(VERSION 3.28)

project(
    cppjrpg
    VERSION 1.0.0
    DESCRIPTION "CppJRPG Engine"
    LANGUAGES C CXX
)

message("C COMPILER ID                  :" ${CMAKE_C_COMPILER_ID})
message("CXX COMPILER ID                :" ${CMAKE_CXX_COMPILER_ID})
message("C COMPILER FRONTEND VARIANT    :" ${CMAKE_C_COMPILER_FRONTEND_VARIANT})
message("CXX COMPILER FRONTEND VARIANT  :" ${CMAKE_CXX_COMPILER_FRONTEND_VARIANT})
message("CMAKE_BUILD_TYPE               :" ${CMAKE_BUILD_TYPE})

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE CACHE BOOL "" FORCE)
set(CMAKE_CXX_STANDARD 17)

# Set a default build type for single-configuration generators
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build" FORCE)
endif()

# Set compiler flags
if (MSVC)
    # General flags for all build types
    string(APPEND CMAKE_CXX_FLAGS " /W4 /permissive-")

    # Flags for Debug build
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /Zi")

    # Flags for Release with Debug Info build
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /O2 /Zi")
else()
    # General flags for all build types (GCC, Clang)
    string(APPEND CMAKE_CXX_FLAGS " -Wextra -Wall -Wpedantic")

    # Flags for Debug build
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

    # Flags for Release with Debug Info build
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O2 -g")
endif ()

set(SOURCE_FILES
    main.cpp
    Sandbox2D.cpp
)

set(HEADER_FILES
    Sandbox2D.h
)

add_executable(
    ${PROJECT_NAME}
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

# target_include_directories(
#     ${PROJECT_NAME} 
#     PUBLIC
#     include/seed
# )

target_compile_options(${PROJECT_NAME} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/EHsc>)

#######################
# Seed Engine
#######################
find_package(seed REQUIRED CONFIG)
target_link_libraries(${PROJECT_NAME} PUBLIC seed::seed)
target_include_directories(${PROJECT_NAME} PUBLIC ${seed_INCLUDE_DIRS})


#######################
# glm
#######################
find_package(glm REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)
target_include_directories(${PROJECT_NAME} PUBLIC ${glm_INCLUDE_DIRS})

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC wsock32 ws2_32)
endif ()
