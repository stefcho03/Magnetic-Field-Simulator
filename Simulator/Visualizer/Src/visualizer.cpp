#include <visualizer.h>
#include <cubegenerator.h>
#include <cylindergenerator.h>
#include <gridgenerator.h>
#include <stdio.h>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Visualizer::Visualizer (size_t width, size_t height) : m_camera (0.0f, 0.0f, 3.0f, 0.0f, 1.0f, 0.0f)
{
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

	// Create window
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
	// Callback for mouse position
	glfwSetWindowUserPointer (m_window, &m_inputHandler);
	glfwSetCursorPosCallback (m_window, mouse_callback);
	// Callback for scroll wheel
	glfwSetScrollCallback (m_window, scroll_wheel_callback);

	// Start and end coordinates for drawing
	glViewport (0, 0, width, height);

	// Input handling
	std::array<float, 3> objectPosition = { static_cast<float> (m_inputHandler.cursorPosition ()[0]), static_cast<float> (m_inputHandler.cursorPosition ()[1]), 0.5f };
	actionMap[InputHandler::Actions::CloseWindow] = [&] () { glfwSetWindowShouldClose (m_window, true); };
	actionMap[InputHandler::Actions::SpawnCube] = [&] ()
	{
		glfwGetWindowSize (m_window, &m_windowWidth, &m_windowHeight);
		double mouseX = m_inputHandler.cursorPosition ()[0];
		double mouseY = m_inputHandler.cursorPosition ()[1];

		float x = 2.0f * mouseX / m_windowWidth - 1.0f;
		float y = -2.0f * mouseY / m_windowHeight + 1.0f;

		glm::mat4 projection = glm::perspective (glm::radians (60.0f), // FOV
		(float)m_windowWidth / m_windowHeight,						   // Aspect ratio
		0.1f,														   // Near clipping plane
		100.0f);													   // Far clipping plane

		glm::vec4 rayClip (x, y, -1.0f, 1.0f);
		glm::vec4 rayView = glm::inverse (projection) * rayClip;
		rayView.z = -1.0f;
		rayView.w = 0.0f;
		glm::vec3 rayWorld = glm::normalize (glm::vec3 (glm::inverse (m_camera.view ()) * rayView));
		float t = -m_camera.position ().z / rayWorld.z;
		glm::vec3 hitPoint = m_camera.position () + t * rayWorld;
		std::array<float, 3> objectPosition = { hitPoint.x, hitPoint.y, hitPoint.z };

		addCube (0.3f, objectPosition);
	};
	actionMap[InputHandler::Actions::SpawnCylinder] = [&] ()
	{
		glfwGetWindowSize (m_window, &m_windowWidth, &m_windowHeight);
		double mouseX = m_inputHandler.cursorPosition ()[0];
		double mouseY = m_inputHandler.cursorPosition ()[1];

		float x = 2.0f * mouseX / m_windowWidth - 1.0f;
		float y = -2.0f * mouseY / m_windowHeight + 1.0f;

		glm::mat4 projection = glm::perspective (glm::radians (60.0f), // FOV
		(float)m_windowWidth / m_windowHeight,						   // Aspect ratio
		0.1f,														   // Near clipping plane
		100.0f);													   // Far clipping plane

		glm::vec4 rayClip (x, y, -1.0f, 1.0f);
		glm::vec4 rayView = glm::inverse (projection) * rayClip;
		rayView.z = -1.0f;
		rayView.w = 0.0f;
		glm::vec3 rayWorld = glm::normalize (glm::vec3 (glm::inverse (m_camera.view ()) * rayView));
		float t = -m_camera.position ().z / rayWorld.z;
		glm::vec3 hitPoint = m_camera.position () + t * rayWorld;
		std::array<float, 3> objectPosition = { hitPoint.x, hitPoint.y, hitPoint.z };

		addCylinder (0.5f, 0.5f, objectPosition);
	};
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
	Shader dynamicShader ("Visualizer/Shaders/Dynamic/dynamic.vert", "Visualizer/Shaders/Dynamic/dynamic.frag");
	Shader gridShader ("Visualizer/Shaders/Static/grid.vert", "Visualizer/Shaders/Static/grid.frag");
	Renderer dynamicRenderer (&dynamicShader);
	Renderer gridRenderer (&gridShader);
	GridGenerator verticalGridGenerator (10, 1.0f, Plane::xy);
	GridGenerator horizontalGridGenerator (10, 1.0f, Plane::xz);
	Mesh verticalGridMesh (verticalGridGenerator.vertices (), {}, PrimitiveType::Lines);
	Mesh horizontalGridMesh (horizontalGridGenerator.vertices (), {}, PrimitiveType::Lines);
	GLuint u_ViewLoc = glGetUniformLocation (gridShader.ID, "u_View");
	GLuint u_ProjLoc = glGetUniformLocation (gridShader.ID, "u_Projection");

	glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
	glEnable (GL_DEPTH_TEST);
	glDisable (GL_CULL_FACE);

	while (!glfwWindowShouldClose (m_window))
	{
		glfwPollEvents ();
		glfwGetWindowSize (m_window, &m_windowWidth, &m_windowHeight);
		if (glfwGetMouseButton (m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			printf ("GLFW: LMB DOWN\n");
		}
		float time = glfwGetTime ();
		m_inputHandler.update (m_window);
		for (auto& [action, command] : actionMap)
		{
			if (m_inputHandler.actionPressedOnce (action))
				command ();
		}
		dynamicRenderer.beginFrame ();
		gridShader.use ();
		glm::mat4 projection = glm::perspective (glm::radians (60.0f), // FOV
		(float)m_windowWidth / m_windowHeight,						   // Aspect ratio
		0.1f,														   // Near clipping plane
		100.0f);													   // Far clipping plane
		glUniformMatrix4fv (u_ViewLoc, 1, GL_FALSE, glm::value_ptr (m_camera.view ()));
		glUniformMatrix4fv (u_ProjLoc, 1, GL_FALSE, glm::value_ptr (projection));
		glDisable (GL_DEPTH_TEST); // optional, grid behind everything
		horizontalGridMesh.draw ();
		verticalGridMesh.draw ();
		glEnable (GL_DEPTH_TEST);

		glm::mat4 model = glm::mat4 (1.0f);
		// model = glm::rotate (model, glm::radians (20.0f) * cos (time), glm::vec3 (1.0f, 0.0f, 1.0f));

		m_move = m_inputHandler.isMouseButtonDown (m_window, GLFW_MOUSE_BUTTON_1) &&
		!(m_inputHandler.isKeyboardButtonDown (m_window, GLFW_KEY_LEFT_CONTROL) || m_inputHandler.isKeyboardButtonDown (m_window, GLFW_KEY_RIGHT_CONTROL));

		m_rotate = m_inputHandler.isMouseButtonDown (m_window, GLFW_MOUSE_BUTTON_1) &&
		(m_inputHandler.isKeyboardButtonDown (m_window, GLFW_KEY_LEFT_CONTROL) || m_inputHandler.isKeyboardButtonDown (m_window, GLFW_KEY_RIGHT_CONTROL));
		m_camera.processMouseMouseInput (m_rotate, m_move, m_inputHandler.cursorDelta ()[0], m_inputHandler.cursorDelta ()[1]);

		std::array<double, 2> scroll = m_inputHandler.consumeScroll ();
		m_camera.processMouseScroll (scroll[1]); // yOffset
		dynamicShader.use ();					 // <- MUST be called before setting uniforms

		glUniformMatrix4fv (glGetUniformLocation (dynamicShader.ID, "u_View"), // Location
		1,																	   // # of matrices
		GL_FALSE,															   // Transpose
		glm::value_ptr (m_camera.view ()));									   // ptr to matrix

		glUniformMatrix4fv (glGetUniformLocation (dynamicShader.ID, "u_Projection"), 1, GL_FALSE, glm::value_ptr (projection));

		for (auto& obj : m_objects)
		{
			unsigned int loc = glGetUniformLocation (dynamicShader.ID, "u_Transform");
			// glUniformMatrix4fv (loc, 1, GL_FALSE, glm::value_ptr (obj.transform ()));
			glUniformMatrix4fv (loc, 1, GL_FALSE, glm::value_ptr (model));
			obj.draw ();
		}
		dynamicRenderer.endFrame (m_window);
	}
}

void Visualizer::addCube (float side, std::array<float, 3>& position)
{
	CubeGenerator cubeGenerator (side, position);
	Mesh cube (cubeGenerator.vertices (), cubeGenerator.indices ());
	SceneObject cubeObject (std::move (cube));
	m_objects.emplace_back (std::move (cubeObject));
}

void Visualizer::addCylinder (float radius, float height, std::array<float, 3>& position)
{
	CylinderGenerator cylinderGenerator (RESOLUTION, radius, height, position);
	Mesh cylinder (cylinderGenerator.vertices (), cylinderGenerator.indices ());
	SceneObject cylinderObject (std::move (cylinder));
	m_objects.emplace_back (std::move (cylinderObject));
}