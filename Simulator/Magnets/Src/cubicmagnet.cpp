#include <cubicmagnet.h>
#include <stdio.h>

CubicMagnet::CubicMagnet (std::array<float, 3>& position, std::array<float, 3>& orientation, uint16_t side, float magnetization)
: Magnet (position, orientation, magnetization), m_side (side)
{
	m_farFieldThreshold = 3 * side;
	printf (
	"Cube created at: %f, %f, %f with polarization orientation: %f, %f, %f \n", position[0], position[1], position[2], orientation[0], orientation[1], orientation[2]);
}

// std::array<float, 3> CubicMagnet::field (std::array<float, 3>& position)
// {

// }