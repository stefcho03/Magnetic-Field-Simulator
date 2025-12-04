#include <cubicmagnet.h>

CubicMagnet::CubicMagnet (float x, float y, float z, uint16_t side, float magnetization)
: Magnet (x, y, z, magnetization), m_side (side)
{
}
