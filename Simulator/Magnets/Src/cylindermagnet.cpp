#include <cylindermagnet.h>

CylinderMagnet::CylinderMagnet (std::array<float, 3>& position,
std::array<float, 3>& orientation,
uint16_t height,
uint16_t radius,
float magnetization)

: Magnet (position, orientation, magnetization), m_height (height), m_radius (radius)
{
    m_farFieldThreshold = 3 * std::max (m_height, m_radius);
}