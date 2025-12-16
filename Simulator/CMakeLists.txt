cmake_minimum_required(VERSION 3.20)
project(magnetSimulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Add engine ----
add_subdirectory(OpenGL)

# ---- Libraries ----

# ---- Magnets ----

add_library(Magnets
    Magnets/Src/defaultmagnet.cpp
    Magnets/Src/cubicmagnet.cpp
    Magnets/Src/cylindermagnet.cpp
    Magnets/Src/helpfunctions.cpp
)

target_include_directories(Magnets PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Magnets/Include
)

# ---- Sensors ----

add_library(Sensors
    Sensors/Src/sensor.cpp
)

target_link_libraries(Sensors PUBLIC Magnets)

target_include_directories(Sensors PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Sensors/Include
)

# ---- Visualizer ----

add_library(Visualizer
    Visualizer/Src/visualizer.cpp
    Visualizer/Src/callbacks.cpp
    Visualizer/Src/visualizerinput.cpp
    Visualizer/Src/renderer.cpp
    Visualizer/Shaders/Src/shader.cpp
)

# ---- Shaders ----
file(GLOB_RECURSE SHADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/Visualizer/Shaders/**/*.vert"
    "${CMAKE_CURRENT_SOURCE_DIR}/Visualizer/Shaders/**/*.frag")

# I am losing my mind
message(STATUS "Shader files:")
foreach(S ${SHADERS})
    message(STATUS "  ${S}")
endforeach()

foreach(SHADER ${SHADERS})
    file(RELATIVE_PATH REL_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/Visualizer/Shaders
        ${SHADER})

    configure_file(
        ${SHADER} 
        ${CMAKE_CURRENT_BINARY_DIR}/Visualizer/Shaders/${REL_PATH} COPYONLY)
endforeach()



target_link_libraries(Visualizer PUBLIC OpenGLEngine)

target_include_directories(Visualizer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Visualizer/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Visualizer/Shaders/Include
)

# ---- Executable ----

add_executable(Simulator main.cpp)

target_link_libraries(Simulator
    PRIVATE
        Visualizer
        Sensors
)
