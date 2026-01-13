#ifndef VISUALIZER_INCLUDE_INPUT_
#define VISUALIZER_INCLUDE_INPUT_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <array>

class InputHandler
{
public:
	enum class Actions
	{
		CloseWindow,
		SpawnCube,
		SpawnCylinder,
		COUNT
	};

	struct InputState
	{
		bool pressed = false;
		bool pressedLast = false;
	};

	InputHandler ();
	void update (GLFWwindow* window);
	bool actionPressed (Actions action);
	bool actionPressedOnce (Actions action);
	bool isMouseButtonDown (GLFWwindow* window, int button);
	bool isKeyboardButtonDown (GLFWwindow* window, int button);
	std::array<double, 2>& consumeScroll ();
	void onScroll (double xOffset, double yOffset);
	std::array<double, 2>& cursorPosition ();
	std::array<double, 2>& cursorDelta ();
	std::array<double, 2>& scrollOffset ();

private:
	static constexpr size_t ActionCount = static_cast<size_t> (Actions::COUNT);
	std::array<bool, ActionCount> m_current{};
	std::array<bool, ActionCount> m_previous{};
	std::array<InputState, ActionCount> m_inputState{};

	Actions m_last_action;
	std::array<double, 2> m_cursorPosition;
	std::array<double, 2> m_lastCursorPosition;
	std::array<double, 2> m_cursorDelta;
	std::array<double, 2> m_scrollOffset;
	std::array<double, 2> m_consumed;
};

#endif // VISUALIZER_INCLUDE_INPUT_
