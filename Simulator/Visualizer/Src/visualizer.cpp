#include <callbacks.h>
#include <stdio.h>
#include <visualizer.h>
#include <visualizerinput.h>

Visualizer::Visualizer (size_t width, size_t height)
{
	if (!glfwInit ())
	{
		fprintf (stderr, "GLFW init failed");
		return;
	}

	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow (width, height, "Magnetic Field Simulator", nullptr, nullptr);
	if (!m_window)
	{
		fprintf (stderr, "Window creation failed");
		return;
	}

	glfwMakeContextCurrent (m_window);

	if (!gladLoadGLLoader ((GLADloadproc)glfwGetProcAddress))
	{
		printf ("GLAD init failed");
		return;
	}

	glfwSetFramebufferSizeCallback (m_window, framebuffer_size_callback);
	glViewport (0, 0, width, height);
}

Visualizer::~Visualizer ()
{
	glfwDestroyWindow (m_window);
	glfwTerminate ();
}

void Visualizer::run ()
{
	while (!glfwWindowShouldClose (m_window))
	{
		processInput (m_window);
		glClear (GL_COLOR_BUFFER_BIT);
		glClearColor (0.1f, 0.3f, 0.3f, 1.0f);
		float vertices[] = { -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f };
		unsigned int VBO;
		glGenBuffers (1, &VBO);
		glBindBuffer (GL_ARRAY_BUFFER, VBO);
		glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);
		glfwSwapBuffers (m_window);
		glfwPollEvents ();
	}
}