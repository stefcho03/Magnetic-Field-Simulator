#ifndef VISUALIZER_INCLUDE_RENDERER_
#define VISUALIZER_INCLUDE_RENDERER_

#define GLAD_GL_IMPLEMENTATION
#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>
#include <mesh.h>

class Renderer
{
public:
	Renderer (Shader* shader);
	void beginFrame ();
	void draw (Mesh& mesh);
	// void draw (const Mesh& mesh, const Shader& shader, const Transform& transform);
	void endFrame (GLFWwindow* window);

private:
	unsigned int m_VAO = 0; // Vertex array object
	unsigned int m_VBO = 0; // Vertex buffer object
	unsigned int m_EBO = 0; // Element buffer object
	Shader* m_shader;
};

#endif // VISUALIZER_INCLUDE_RENDERER_