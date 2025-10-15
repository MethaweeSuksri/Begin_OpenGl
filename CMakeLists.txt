cmake_minimum_required(VERSION 3.31)
project(Begin_OpenGl) 

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include GLFW headers
include_directories(${CMAKE_SOURCE_DIR}/GLFW)

# Add executable
add_executable(MyApp main.cpp)

# Link GLFW and OpenGL
target_link_libraries(MyApp
    ${CMAKE_SOURCE_DIR}/libglfw3.a
    GL
    X11
    pthread
    Xrandr
    Xi
    dl
    m
)
