#include <cylindermagnet.h>
#include <stdio.h>

CylinderMagnet::CylinderMagnet (std::array<float, 3>& position, std::array<float, 3>& orientation, uint16_t height, uint16_t radius, float magnetization)

: Magnet (position, orientation, magnetization), m_height (height), m_radius (radius)
{
	m_farFieldThreshold = 3 * std::max (m_height, m_radius);
	printf (
	"Cylinder created at: %f, %f, %f with polarization orientation: %f, %f, %f \n", position[0], position[1], position[2], orientation[0], orientation[1], orientation[2]);
}