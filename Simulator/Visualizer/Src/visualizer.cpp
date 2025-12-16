#include <visualizer.h>
#include <stdio.h>

Visualizer::Visualizer (size_t width, size_t height)
{
	if (!glfwInit ())
	{
		fprintf (stderr, "GLFW init failed");
		return;
	}

	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for macOS
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
	m_renderer.init ();
	glClearColor (0.1f, 0.3f, 0.3f, 1.0f);

	while (!glfwWindowShouldClose (m_window))
	{
		processInput (m_window);
		m_renderer.beginFrame ();
		m_renderer.drawTriangle ();
		m_renderer.endFrame (m_window);
		glfwPollEvents ();
	}
}