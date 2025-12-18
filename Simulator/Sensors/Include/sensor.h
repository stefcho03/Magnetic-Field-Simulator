#ifndef SENSOR_INCLUDE_SENSOR_
#define SENSOR_INCLUDE_SENSOR_

#include <magnetinterface.h>
#include <span>
#include <stdio.h>
#include <type_traits>


class Sensor
{
public:
    Sensor (float x, float y, float z);
    std::array<float, 3> measureBFromMagnet (MagnetInterface& magnet);
    std::array<float, 3>& position ();

private:
    std::array<float, 3> calculateBNearField (float distance,
    float magnetization,
    std::array<float, 3> orientation);
    std::array<float, 3> calculateBFarField (float distance,
    float magnetization,
    std::array<float, 3> orientation);
    std::array<float, 3> m_position;
};

#endif // SENSOR_INCLUDE_SENSOR_