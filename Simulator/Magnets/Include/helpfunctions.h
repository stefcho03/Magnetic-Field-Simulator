#ifndef MAGNETS_INCLUDE_HELPFUNCTIONS_
#define MAGNETS_INCLUDE_HELPFUNCTIONS_

#include <array>
#include <concepts>

template <typename T>
concept Quaternion = std::same_as<T, std::array<float, 4>>;

template <typename T>
concept Type = std::is_arithmetic_v<T>;

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

    template <Type T, std::size_t L>
    static std::array<T, L> normalize (std::array<T, L> toBeNormalized)
    {
        T sum = 0;
        std::array<T, L> retArr;
        for (size_t i = 0; i < L; i++)
            sum += toBeNormalized[i] * toBeNormalized[i];
        sum = sqrt (sum);
        for (size_t i = 0; i < L; i++)
            retArr[i] = toBeNormalized[i] / sum;
        return retArr;
    }

    // dimension check is done at compile time
    template <Type T, std::size_t L>
    static float calculateDistance (std::array<T, L> first, std::array<T, L> second)
    {
        float distance = 0.0f;
        for (size_t i = 0; i < first.size (); i++) {
            distance += (first[i] - second[i]) * (first[i] - second[i]);
        }
        return sqrt (distance);
    }


private:
    static std::array<float, 4> quatMul (std::array<float, 4> q1, std::array<float, 4> q2);
};

#endif // MAGNETS_INCLUDE_HELPFUNCTIONS_