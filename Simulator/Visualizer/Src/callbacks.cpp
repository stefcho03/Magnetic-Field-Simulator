#include <callbacks.h>
#include <stdio.h>
#include <inputhandler.h>

void framebuffer_size_callback (GLFWwindow* window, int width, int height)
{
	glViewport (0, 0, width, height);
}

void mouse_callback (GLFWwindow* window, double x, double y)
{
	printf ("Cursor x: %f y: %f \n", x, y);
}

void scroll_wheel_callback (GLFWwindow* window, double xOffset, double yOffset)
{
	InputHandler* inputHandler = static_cast<InputHandler*> (glfwGetWindowUserPointer (window));
	if (inputHandler)
		inputHandler->onScroll (xOffset, yOffset); // Forward scroll to InputHandler
	printf ("Scroll x: %f y: %f \n", xOffset, yOffset);
}
