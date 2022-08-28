cmake_minimum_required(VERSION 3.9)
project(Hrothgor_Engine CXX)

set(PROJECT_ROOT ./)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
include(FetchContent)

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

##############################
# ImGui lib
##############################

add_library(imgui STATIC)

target_sources(imgui
    PRIVATE
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui.cpp
)

target_include_directories(imgui PUBLIC ${IMGUI_DIR})

##############################
# source files
##############################

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

set(RLIMGUI_SRC
    ${PROJECT_ROOT}/Externals/rlImGui/rlImGui.cpp
)

set(IMGUIZMO_SRC
    ${PROJECT_ROOT}/Externals/ImGuizmo/ImGuizmo.cpp
)

add_executable(Hrothgor_Engine
    ${SRC_FILES}
    ${RLIMGUI_SRC}
    ${IMGUIZMO_SRC}
)

target_include_directories(Hrothgor_Engine
    PRIVATE
        ${PROJECT_ROOT}
        ${PROJECT_ROOT}/src/
        ${PROJECT_ROOT}/src/Include
        ${IMGUI_DIR}
        )
        
target_compile_options(Hrothgor_Engine PRIVATE
    -W -Wall -Wextra -Wno-missing-field-initializers
    -march=native
    -O3)

target_link_libraries(Hrothgor_Engine imgui)
target_link_libraries(Hrothgor_Engine raylib)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(raylib URL https://github.com/raysan5/raylib/archive/master.tar.gz)
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
        set(raylib_FOUND TRUE)
    endif()
endif()