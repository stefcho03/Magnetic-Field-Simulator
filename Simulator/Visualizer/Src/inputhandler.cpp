#include <inputhandler.h>
#include <stdio.h>

InputHandler::InputHandler ()
{
}

void InputHandler::update (GLFWwindow* window)
{
	glfwGetCursorPos (window, &m_cursorPosition[0], &m_cursorPosition[1]);
	for (unsigned int i = 0; i < m_cursorPosition.size (); i++)
	{
		m_cursorDelta[i] = m_cursorPosition[i] - m_lastCursorPosition[i];
		m_lastCursorPosition[i] = m_cursorPosition[i];
	}
	m_previous = m_current;
	// m_isPressedThisFrame = m_previous == false && m_current == true;
	m_current[(size_t)Actions::CloseWindow] = glfwGetKey (window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
	m_current[(size_t)Actions::SpawnCube] = glfwGetKey (window, GLFW_KEY_A) == GLFW_PRESS;
	m_current[(size_t)Actions::SpawnCylinder] = glfwGetKey (window, GLFW_KEY_S) == GLFW_PRESS;
}

bool InputHandler::actionPressed (Actions action)
{
	size_t i = (size_t)action;
	return m_current[i] && !m_previous[i];
}

bool InputHandler::actionPressedOnce (Actions action)
{
	return m_current.at ((size_t)action) && !m_previous.at ((size_t)action);
}

bool InputHandler::isMouseButtonDown (GLFWwindow* window, int button)
{
	if (glfwGetMouseButton (window, button) == GLFW_PRESS)
		printf ("Mouse check");
	return glfwGetMouseButton (window, button) == GLFW_PRESS;
}

bool InputHandler::isKeyboardButtonDown (GLFWwindow* window, int button)
{
	if (glfwGetKey (window, button) == GLFW_PRESS)
		printf ("Button check");
	return glfwGetKey (window, button) == GLFW_PRESS;
}

std::array<double, 2>& InputHandler::consumeScroll ()
{
	m_consumed = { m_scrollOffset[0], m_scrollOffset[1] };
	m_scrollOffset[0] = 0.0;
	m_scrollOffset[1] = 0.0;
	return m_consumed;
}

void InputHandler::onScroll (double xOffset, double yOffset)
{
	m_scrollOffset[0] += xOffset;
	m_scrollOffset[1] += yOffset;
}

std::array<double, 2>& InputHandler::cursorPosition ()
{
	return m_cursorPosition;
}

std::array<double, 2>& InputHandler::cursorDelta ()
{
	return m_cursorDelta;
}

std::array<double, 2>& InputHandler::scrollOffset ()
{
	return m_scrollOffset;
}