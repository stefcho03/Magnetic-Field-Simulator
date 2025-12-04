#ifndef SENSOR_INCLUDE_SENSOR_
#define SENSOR_INCLUDE_SENSOR_

#include <magnetinterface.h>
#include <span>
#include <type_traits>

class Sensor
{
public:
    Sensor (float x, float y, float z);
    float measureBFromMagnet (MagnetInterface& magnet);
    std::array<float, 3>& position ();

private:
    template <typename T>
        requires std::is_arithmetic_v<T>
    T calculateDistance (std::span<T> first, std::span<T> second)
    {
        if (first.size () != second.size ())
            return 0;
        T distance;
        for (size_t i = 0; i < first.size (); i++) {
            distance += (first[i] - second[i]) * (first[i] - second[i]);
        }
        return distance;
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    float calculateB (T distance, float magnetization)
    {
        return magnetization / static_cast<float> (distance);
    }

    std::array<float, 3> m_position;
};

#endif // SENSOR_INCLUDE_SENSOR_