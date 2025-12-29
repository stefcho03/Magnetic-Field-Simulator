#include <visualizer.h>
#include <cubegenerator.h>
#include <stdio.h>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	std::array<float, 3> cubePosition = { 0.0f, 0.0f, 0.0f };
	CubeGenerator cubeGenerator (0.5f, cubePosition);
	Mesh cube (cubeGenerator.vertices (), cubeGenerator.indices ());
	Shader dynamicShader ("Visualizer/Shaders/Dynamic/dynamic.vert", "Visualizer/Shaders/Dynamic/dynamic.frag");
	Renderer dynamicRenderer (&dynamicShader);
	glEnable (GL_DEPTH_TEST);
	while (!glfwWindowShouldClose (m_window))
	{
		float time = glfwGetTime ();
		processInput (m_window);
		dynamicRenderer.beginFrame ();

		glm::mat4 model = glm::mat4 (1.0f);
		model = glm::rotate (model, glm::radians (180.0f) * cos (time), glm::vec3 (sin (time) * 0.5f, 0.0f, 0.5f));

		dynamicShader.use (); // <- MUST be called before setting uniforms
		unsigned int loc = glGetUniformLocation (dynamicShader.ID, "u_Transform");
		glUniformMatrix4fv (loc, 1, GL_FALSE, glm::value_ptr (model));

		cube.draw ();
		dynamicRenderer.endFrame (m_window);
	}
}