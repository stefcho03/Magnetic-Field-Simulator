#ifndef VISUAlIZER_INCLUDE_VISUALIZER_
#define VISUAlIZER_INCLUDE_VISUALIZER_

#include <visualizerinput.h>
#include <renderer.h>
#include <callbacks.h>
#include <mesh.h>

class Visualizer
{
public:
	Visualizer (size_t width, size_t height);
	void run ();
	~Visualizer ();

private:
	GLFWwindow* m_window;
};

#endif // VISUAlIZER_INCLUDE_VISUALIZER_