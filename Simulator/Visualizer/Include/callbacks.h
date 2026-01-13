
#ifndef VISUALIZER_INCLUDE_CALLBACKS_
#define VISUALIZER_INCLUDE_CALLBACKS_
#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback (GLFWwindow* window, int width, int height);
void mouse_callback (GLFWwindow* window, double x, double y);
void scroll_wheel_callback (GLFWwindow* window, double xOffset, double yOffset);
// double scrollWheelXOffset, scrollWheelYOffset;

#endif // VISUALIZER_INCLUDE_CALLBACKS_