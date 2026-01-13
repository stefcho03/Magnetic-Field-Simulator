#ifndef VISUAlIZER_INCLUDE_VISUALIZER_
#define VISUAlIZER_INCLUDE_VISUALIZER_
#include <renderer.h>
#include <callbacks.h>
#include <sceneobject.h>
#include <mesh.h>
#include <camera.h>
#include <inputhandler.h>
#include <functional>

#define RESOLUTION 100

class Visualizer
{
public:
	Visualizer (size_t width, size_t height);
	void run ();
	~Visualizer ();

private:
	void addCube (float side, std::array<float, 3>& position);
	void addCylinder (float radius, float height, std::array<float, 3>& position);

	GLFWwindow* m_window;
	InputHandler m_inputHandler;
	Camera m_camera;
	std::vector<SceneObject> m_objects;
	std::unordered_map<InputHandler::Actions, std::function<void ()>> actionMap;
	std::array<float, 3> cubePosition = { 0.0f, 0.0f, 0.0f };
	std::array<float, 3> cylinderPosition = { 0.5f, 0.0f, 0.5f };
	bool m_rotate = false;
	bool m_move = false;
	int m_windowHeight, m_windowWidth;
};

#endif // VISUAlIZER_INCLUDE_VISUALIZER_