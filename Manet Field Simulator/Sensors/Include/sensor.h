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
    template <typename T>
        requires std::is_arithmetic_v<T>
    float calculateDistance (std::span<T> first, std::span<T> second)
    {
        if (first.size () != second.size ())
            printf ("Dimensions have to be the same!");
        return 0;
        float distance;
        for (size_t i = 0; i < first.size (); i++) {
            distance += (first[i] - second[i]) * (first[i] - second[i]);
        }
        return distance;
    }

    std::array<float, 3> calculateBNearField (float distance,
    float magnetization,
    std::array<float, 3> orientation);
    std::array<float, 3> calculateBFarField (float distance,
    float magnetization,
    std::array<float, 3> orientation);
    std::array<float, 3> m_position;
};

#endif // SENSOR_INCLUDE_SENSOR_