cmake_minimum_required(VERSION 3.9)
project(physics_engine CXX)

set(PROJECT_ROOT ./)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
include(FetchContent)

##############################
# ImGui lib
##############################

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
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
# physics_engine executable
##############################
file(GLOB_RECURSE SRC_FILES "src/*.cpp")

set(RLIMGUI_SRC
    ${PROJECT_ROOT}/Externals/rlImGui/rlImGui.cpp
)

set(IMGUIZMO_SRC
    ${PROJECT_ROOT}/Externals/ImGuizmo/ImGuizmo.cpp
)

add_executable(physics_engine
    ${SRC_FILES}
    ${RLIMGUI_SRC}
    ${IMGUIZMO_SRC}
)

target_include_directories(physics_engine
    PRIVATE
        ${PROJECT_ROOT}/src/
        ${PROJECT_ROOT}/Externals/
        ${PROJECT_ROOT}/Externals/rlImGui
        ${PROJECT_ROOT}/Externals/ImGuizmo
        ${PROJECT_ROOT}/Externals/nlohmann
        ${IMGUI_DIR}
)

target_compile_options(physics_engine PRIVATE 
    -W -Wall -Wextra -Wno-missing-field-initializers
    -march=native
    -O2 -g3)

    
target_link_libraries(physics_engine imgui)
target_link_libraries(physics_engine raylib)
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