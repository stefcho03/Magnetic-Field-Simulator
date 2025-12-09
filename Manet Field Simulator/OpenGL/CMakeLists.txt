cmake_minimum_required(VERSION 3.20)
project(OpenGLEngine)

# ---- GLAD ----
add_library(glad STATIC
    src/glad.c
)
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ---- GLFW ----
# you should set your glfw folder here. In this project it's built and installed separately
# so the config and target files are already generated. This wouldnt be the case if using choco 
set(GLFW3_DIR "D:/Users/HP/GLFW3/glfw-install-mingw/lib/cmake/glfw3")
find_package(GLFW3 REQUIRED) 

# ---- Engine ----
add_library(OpenGLEngine INTERFACE)
target_include_directories(OpenGLEngine INTERFACE 
    include/glad
    ${GLFW3_INCLUDE_DIR})
target_link_libraries(OpenGLEngine INTERFACE 
    glad 
    glfw)
