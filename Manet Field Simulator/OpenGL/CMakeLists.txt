cmake_minimum_required(VERSION 3.20)
project(OpenGLEngine)

# # ---- Temporary -----
# set(GLFW3_INCLUDE_DIR "C:/ProgramData/chocolatey/lib/glfw3/include")
# set(GLFW3_LIBRARY "C:/ProgramData/chocolatey/lib/glfw3/lib/glfw3.lib")
# set(GLFW3_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/GLFW)
# set(GLFW_STATIC_LIBRARIES "C:/ProgramData/chocolatey/lib/glfw3/lib/glfw3.lib")


# ---- GLAD ----
add_library(glad STATIC
    src/glad.c
)
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ---- GLFW ----
set(GLFW3_DIR "D:/Users/HP/GLFW3/glfw-install-mingw/lib/cmake/glfw3")
find_package(GLFW3 REQUIRED) 
# include_directories(${GLFW_INCLUDE_DIR})
# target_link_libraries(simple ${GLFW_STATIC_LIBRARIES})

# ---- Engine ----
add_library(OpenGLEngine INTERFACE)
target_include_directories(OpenGLEngine INTERFACE 
    include/glad
    ${GLFW3_INCLUDE_DIR})
target_link_libraries(OpenGLEngine INTERFACE 
    glad 
    glfw)
