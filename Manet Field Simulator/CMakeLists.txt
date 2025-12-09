cmake_minimum_required(VERSION 3.20)
project(magnetSimulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Add engine ----
add_subdirectory(OpenGL)

# ---- Libraries ----

add_library(Magnets
    Magnets/Src/defaultmagnet.cpp
    Magnets/Src/cubicmagnet.cpp
    Magnets/Src/cylindermagnet.cpp
    Magnets/Src/helpfunctions.cpp
)

target_include_directories(Magnets PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Magnets/Include
)

add_library(Sensors
    Sensors/Src/sensor.cpp
)

target_link_libraries(Sensors PUBLIC Magnets)

target_include_directories(Sensors PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Sensors/Include
)

# ---- Executable ----

add_executable(Simulator main.cpp)

target_link_libraries(Simulator
    PRIVATE
        OpenGLEngine
        Sensors
)
