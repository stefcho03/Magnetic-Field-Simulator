#ifndef VISUAlIZER_INCLUDE_VISUALIZER_
#define VISUAlIZER_INCLUDE_VISUALIZER_

#define GLAD_GL_IMPLEMENTATION
#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Visualizer
{
public:
    Visualizer (size_t width, size_t height);
    void run ();
    ~Visualizer ();

private:
    GLFWwindow* m_window;
};

#endif // VISUAlIZER_INCLUDE_VISUALIZER_