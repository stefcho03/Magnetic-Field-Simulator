#include <renderer.h>

Renderer::Renderer ()
{
}

void Renderer::init ()
{
	triangleShader = new Shader ("Visualizer/Shaders/Static/triangle.vert", "Visualizer/Shaders/Static/triangle.frag");
	float vertices[] = { -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f };
	glGenVertexArrays (1, &VAO);
	glGenBuffers (1, &VBO);

	glBindVertexArray (VAO);
	glBindBuffer (GL_ARRAY_BUFFER, VBO);
	glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float), (void*)0);
	glEnableVertexAttribArray (0);

	glBindBuffer (GL_ARRAY_BUFFER, 0);
	glBindVertexArray (0);
}

void Renderer::beginFrame ()
{
	glClear (GL_COLOR_BUFFER_BIT);
	triangleShader->use ();
}

void Renderer::drawTriangle ()
{
	glBindVertexArray (VAO);
	glDrawArrays (GL_TRIANGLES, 0, 3);
	glBindVertexArray (0);
}

void Renderer::endFrame (GLFWwindow* window)
{
	glfwSwapBuffers (window);
}

Renderer::~Renderer ()
{
	glDeleteVertexArrays (1, &VAO);
	glDeleteBuffers (1, &VBO);
	delete triangleShader;
}