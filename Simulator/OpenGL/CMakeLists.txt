cmake_minimum_required(VERSION 3.20)
project(OpenGLEngine)

include(FetchContent)

# ---- OpenGL ----
find_package(OpenGL REQUIRED)

# ---- GLAD ----
add_library(glad STATIC
    src/glad.c
)
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ---- GLFW ----
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG 3.4
)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

# ---- GLM ----
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm
    GIT_TAG 1.0.2
)

FetchContent_MakeAvailable(glm)

add_library(OpenGLEngine INTERFACE)

target_link_libraries(OpenGLEngine INTERFACE
    glad
    glfw
    glm
    OpenGL::GL
)

target_include_directories(OpenGLEngine INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
