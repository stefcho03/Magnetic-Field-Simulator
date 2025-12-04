#include <cylindermagnet.h>

CylinderMagnet::CylinderMagnet (float x, float y, float z, uint16_t height, uint16_t radius, float magnetization)
: Magnet (x, y, z, magnetization), m_height (height), m_radius (radius)
{
}