#include <cubicmagnet.h>
#include <cylindermagnet.h>
#include <sensor.h>
#include <stdio.h>
#include <visualizer.h>

int main ()
{
	// std::array<float, 3> position{ 0.0f, 0.0f, 0.0f };
	// std::array<float, 3> orientation{ 1.0f, 0.0f, 0.0f };
	// std::array<float, 3> measurementPosition{ 2.0f, 1.0f, 0.0f };
	// CubicMagnet cube (position, orientation, 5.0f, 2000000.0f);
	// cube.move (1.0f, 0.0f, 0.0f);
	// cube.field (measurementPosition);
	Visualizer window (600, 800);
	window.run ();
	return 0;
}