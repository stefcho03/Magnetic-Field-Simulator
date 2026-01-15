#include <helpfunctions.h>

std::array<float, 4> HelpFunctions::quaternion (float degrees, std::array<float, 3> axis)
{
    float radians = degrees / 180;
    std::array<float, 4> quaternion = { sinf (radians / 2) * axis[0],
        sinf (radians / 2) * axis[1], sinf (radians / 2) * axis[2], cosf (radians / 2) };
    return quaternion;
}

std::array<float, 4> HelpFunctions::inverseQuaternion (std::array<float, 4> quaternion)
{
    std::array<float, 4> inverseQuaternion = { quaternion[0], -quaternion[1],
        -quaternion[2], -quaternion[3] };
    return inverseQuaternion;
}

std::array<float, 4>
HelpFunctions::quatMul (std::array<float, 4> q1, std::array<float, 4> q2)
{
    return { q1[0] * q2[0] - q1[1] * q2[1] - q1[2] * q2[2] - q1[3] * q2[3],
        q1[0] * q2[1] + q1[1] * q2[0] - q1[2] * q2[3] + q1[3] * q2[2],
        q1[0] * q2[2] + q1[1] * q2[3] + q1[2] * q2[0] - q1[3] * q2[1],
        q1[0] * q2[3] - q1[1] * q2[2] + q1[2] * q2[1] + q1[3] * q2[0] };
}