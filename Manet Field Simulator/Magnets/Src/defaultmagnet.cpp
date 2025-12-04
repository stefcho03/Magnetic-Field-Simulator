#include <defaultmagnet.h>

Magnet::Magnet (float x, float y, float z, float magnetization)
: m_position{ x, y, z }, m_magnetization (magnetization)
{
}

void Magnet::move (float x, float y, float z)
{
    m_position[0] += x;
    m_position[1] += y;
    m_position[2] += z;
}

std::array<float, 3>& Magnet::position ()
{
    return m_position;
}

float Magnet::magnetization ()
{
    return m_magnetization;
}
