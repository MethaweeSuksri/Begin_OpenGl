cmake_minimum_required(VERSION 3.31)
project(Begin_OpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    src/main.cpp
    src/glad.c
)

# Executable
add_executable(Begin_OpenGL ${SOURCES})

# Include directories
target_include_directories(Begin_OpenGL PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

# Link libraries
target_link_libraries(Begin_OpenGL PRIVATE
    ${PROJECT_SOURCE_DIR}/lib/libglfw.so
    GL

    X11
    pthread
    Xrandr
    Xi
    dl
    m
)

# Optional: Set output directory for executable
set_target_properties(Begin_OpenGL PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build
)
