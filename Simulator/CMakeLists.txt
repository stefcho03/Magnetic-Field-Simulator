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
)

target_link_libraries(Visualizer PUBLIC OpenGLEngine)

target_include_directories(Visualizer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Visualizer/Include
)

# ---- Executable ----

add_executable(Simulator main.cpp)

target_link_libraries(Simulator
    PRIVATE
        Visualizer
        Sensors
)
