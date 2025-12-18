#include <cmath>
#include <sensor.h>


Sensor::Sensor (float x, float y = 0, float z = 0) : m_position{ x, y, z }
{
}

std::array<float, 3>& Sensor::position ()
{
    return m_position;
}

std::array<float, 3> Sensor::measureBFromMagnet (MagnetInterface& magnet)
{
    return magnet.field (m_position);
}

std::array<float, 3> Sensor::calculateBNearField (float distance,
float magnetization,
std::array<float, 3> orientation)
{
    return { 0, 0, 0 }; // TODO PLACEHOLDER
}

std::array<float, 3> Sensor::calculateBFarField (float distance,
float magnetization,
std::array<float, 3> orientation)
{
    return { 0, 0, 0 }; // TODO PLACEHOLDER
}