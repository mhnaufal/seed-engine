cmake_minimum_required(VERSION 3.28)

project(
    cppjrpg
    VERSION 1.0.1
    DESCRIPTION "Card Battler made using Seed Engine"
    LANGUAGES C CXX
)

message("C COMPILER ID                  :" ${CMAKE_C_COMPILER_ID})
message("CXX COMPILER ID                :" ${CMAKE_CXX_COMPILER_ID})
message("C COMPILER FRONTEND VARIANT    :" ${CMAKE_C_COMPILER_FRONTEND_VARIANT})
message("CXX COMPILER FRONTEND VARIANT  :" ${CMAKE_CXX_COMPILER_FRONTEND_VARIANT})
message("CMAKE_BUILD_TYPE               :" ${CMAKE_BUILD_TYPE})

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE CACHE BOOL "" FORCE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_ERROR_DEPRECATED TRUE)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_BUILD_TYPE Debug)
elseif (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(CMAKE_BUILD_TYPE RelWIthDebInfo)
endif ()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build" FORCE)
endif()

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

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            /W4 /permissive- /std:c++20 /EHsc
            $<$<CONFIG:Debug>:/Od /Zi /RTCs /RTCu /RTC1 /Z7>
            $<$<CONFIG:RelWithDebInfo>:/O2 /Zi /Gy /Gw /OPT:REF /OPT:ICF>
            $<$<CONFIG:Release>:/O2 /Gy /Gw /OPT:REF /OPT:ICF>
    )
    target_link_options(${PROJECT_NAME} PRIVATE /GL /LTCG)
elseif (CMAKE_GNU_COMPILER_ID)
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Wextra -Wall -Wpedantic
            $<$<CONFIG:Debug>:-g>
            $<$<CONFIG:RelWithDebInfo>:-O2 -g>
            $<$<CONFIG:Release>:-O2>
    )
endif ()

#######################
# Seed Engine
#######################
find_package(seed REQUIRED CONFIG)
target_link_libraries(${PROJECT_NAME} PUBLIC seed::seed)
target_include_directories(${PROJECT_NAME} PUBLIC ${seed_INCLUDE_DIRS})

# #######################
# # glm
# #######################
# find_package(glm REQUIRED)
# target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)
# target_include_directories(${PROJECT_NAME} PUBLIC ${glm_INCLUDE_DIRS})

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC wsock32 ws2_32)
endif ()
