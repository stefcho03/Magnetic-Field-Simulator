#include <cmath>
#include <sensor.h>


Sensor::Sensor (float x, float y = 0, float z = 0) : m_position{ x, y, z }
{
}

std::array<float, 3>& Sensor::position ()
{
    return m_position;
}

float Sensor::measureBFromMagnet (MagnetInterface& magnet)
{
    auto distance = calculateDistance (
    std::span<float> (position ()), std::span<float> (magnet.position ()));
    return calculateB (distance, magnet.magnetization ());
}