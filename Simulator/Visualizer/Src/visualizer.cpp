#include <visualizer.h>
#include <stdio.h>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

Visualizer::Visualizer (size_t width, size_t height)
{

	// Create window
	if (!glfwInit ())
	{
		fprintf (stderr, "GLFW init failed");
		return;
	}
	// Version control
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

	// Callback for resizing
	glfwSetFramebufferSizeCallback (m_window, framebuffer_size_callback);
	// Start and end coordinates for drawing
	glViewport (0, 0, width, height);
}

Visualizer::~Visualizer ()
{
	glfwDestroyWindow (m_window);
	glfwTerminate ();
}

void Visualizer::run ()
{
	if (!m_window)
		return;
	Mesh triangleMesh ({ 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, -0.5f, 0.5f, 0.0f });
	std::vector<float> circleVertices = { 0.0f, 0.0f, 0.0f }; // center
	std::vector<unsigned int> circleIndices;
	size_t faces = 100;
	float step = 2 * M_PI / faces;
	float radius = 0.5f;
	for (size_t i; i <= faces; i++)
	{
		circleVertices.push_back (radius * sin (i * step));
		circleVertices.push_back (radius * cos (i * step));
		circleVertices.push_back (0.0f);
	}
	for (size_t i = 1; i <= faces; i++)
	{
		circleIndices.push_back (0);
		circleIndices.push_back (i);
		circleIndices.push_back (i + 1);
	}

	circleIndices.push_back (0);
	circleIndices.push_back (faces);
	circleIndices.push_back (1);
	Mesh circleMesh (circleVertices, circleIndices);

	Shader shader ("Visualizer/Shaders/Static/triangle.vert", "Visualizer/Shaders/Static/triangle.frag");
	Renderer renderer (&shader);
	while (!glfwWindowShouldClose (m_window))
	{
		processInput (m_window);
		renderer.beginFrame ();
		renderer.draw (circleMesh);
		renderer.endFrame (m_window);
	}
}