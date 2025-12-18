#include <renderer.h>
#include <mesh.h>

Renderer::Renderer (Shader* shader) : m_shader (shader)
{
}

void Renderer::beginFrame ()
{
	glClearColor (0.5f, 0.3f, 0.4f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT);
	m_shader->use ();
}

void Renderer::draw (Mesh& mesh)
{
	mesh.draw ();
}

void Renderer::endFrame (GLFWwindow* window)
{
	glfwSwapBuffers (window);
	glfwPollEvents ();
}
