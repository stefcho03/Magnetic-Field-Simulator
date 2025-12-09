#ifndef MAGNETS_INCLUDE_HELPFUNCTIONS_
#define MAGNETS_INCLUDE_HELPFUNCTIONS_
#define _USE_MATH_DEFINES

#include <array>
#include <concepts>
#include <math.h>

template <typename T>
concept Quaternion = std::same_as<T, std::array<float, 4>>;

static constexpr float mu0 = 4.0f * M_PI * 1e-7f;

class HelpFunctions
{
public:
    static std::array<float, 4> quaternion (float degrees, std::array<float, 3> axis);
    static std::array<float, 4> inverseQuaternion (std::array<float, 4> quaternion);

    template <Quaternion... Q>
    static std::array<float, 4> quaternionMultiplication (Q&... q)
    {
        std::array<float, 4> result{ 1, 0, 0, 0 };
        ((result = quatMul (result, q)), ...);
        return result;
    }

private:
    static std::array<float, 4> quatMul (std::array<float, 4> q1, std::array<float, 4> q2);
};

#endif // MAGNETS_INCLUDE_HELPFUNCTIONS_