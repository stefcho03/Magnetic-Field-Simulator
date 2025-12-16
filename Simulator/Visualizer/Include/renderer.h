#ifndef VISUALIZER_INCLUDE_RENDERER_
#define VISUALIZER_INCLUDE_RENDERER_

#define GLAD_GL_IMPLEMENTATION
#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>

class Renderer
{
public:
	Renderer ();
	void init ();
	void beginFrame ();
	void drawTriangle ();
	// void draw (const Mesh& mesh, const Shader& shader, const Transform& transform);
	void endFrame (GLFWwindow* window);
	~Renderer ();

private:
	unsigned int VAO = 0;
	unsigned int VBO = 0;
	Shader* triangleShader = nullptr;
};

#endif // VISUALIZER_INCLUDE_RENDERER_