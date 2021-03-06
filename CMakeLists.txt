cmake_minimum_required(VERSION 3.9)
project(physics_engine CXX)

set(PROJECT_ROOT ./)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT COMPILING_COMPONENTS)
    set(COMPILING_COMPONENTS OFF)
endif()

include(GNUInstallDirs)
include(FetchContent)

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

if (NOT COMPILING_COMPONENTS)

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
    list(FILTER SRC_FILES EXCLUDE REGEX ".*main\\.cpp$")
    
    set(RLIMGUI_SRC
        ${PROJECT_ROOT}/Externals/rlImGui/rlImGui.cpp
    )

    set(IMGUIZMO_SRC
        ${PROJECT_ROOT}/Externals/ImGuizmo/ImGuizmo.cpp
    )

    ##############################
    # physics_engine .so for runtime compilation
    ##############################

    add_library(physics_engine_lib SHARED
        ${SRC_FILES}
        ${RLIMGUI_SRC}
        ${IMGUIZMO_SRC}
    )

    target_include_directories(physics_engine_lib
        PRIVATE
            ${PROJECT_ROOT}
            ${PROJECT_ROOT}/src/
            ${PROJECT_ROOT}/src/Include
            ${IMGUI_DIR}
            )
            
    target_compile_options(physics_engine_lib PRIVATE
        -W -Wall -Wextra -Wno-missing-field-initializers
        -march=native
        -O3)

    target_link_libraries(physics_engine_lib imgui)
    target_link_libraries(physics_engine_lib raylib)
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

    install(TARGETS physics_engine_lib DESTINATION ${PROJECT_ROOT})

    ##############################
    # physics_engine executable
    ##############################

    add_executable(physics_engine
        ${PROJECT_ROOT}/src/main.cpp
    )

    target_include_directories(physics_engine
        PRIVATE
            ${PROJECT_ROOT}
            ${PROJECT_ROOT}/src/
            ${PROJECT_ROOT}/src/Include
            ${IMGUI_DIR}
            )
    
    target_link_directories(physics_engine 
        PRIVATE
            ${PROJECT_ROOT})
    target_link_libraries(physics_engine physics_engine_lib)

endif()

if (COMPILING_COMPONENTS)

    ##############################
    # physics_engine componennts libraries .so
    ##############################

    file(GLOB_RECURSE SRC_FILES_COMPONENTS "Engine/Components/*.cpp")

    add_library(components SHARED
        ${SRC_FILES_COMPONENTS}
        )

    target_include_directories(components
        PRIVATE
            ${PROJECT_ROOT}
            ${PROJECT_ROOT}/src/
            ${PROJECT_ROOT}/src/Include
            ${IMGUI_DIR}
            )

    target_compile_options(components PRIVATE
        -W -Wall -Wextra -Wno-missing-field-initializers
        -march=native
        -O3)
    
    target_link_directories(components 
        PRIVATE
            ${PROJECT_ROOT})
    target_link_libraries(components physics_engine_lib)

    install(TARGETS components DESTINATION ${PROJECT_ROOT})

endif()