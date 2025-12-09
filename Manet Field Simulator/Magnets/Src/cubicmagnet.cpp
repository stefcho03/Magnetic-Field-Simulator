#include <cubicmagnet.h>

CubicMagnet::CubicMagnet (std::array<float, 3>& position,
std::array<float, 3>& orientation,
uint16_t side,
float magnetization)
: Magnet (position, orientation, magnetization), m_side (side)
{
    m_farFieldThreshold = 3 * side;
}
