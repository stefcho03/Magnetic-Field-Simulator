#include <cmath>
#include <defaultmagnet.h>
#include <helpfunctions.h>

Magnet::Magnet (std::array<float, 3> position, std::array<float, 3> orientation, float magnetization)
: m_position{ position[0], position[1], position[2] },
  m_orientation{ orientation[0], orientation[1], orientation[2] },
  m_magnetization (magnetization)
{
}

void Magnet::move (float x, float y, float z)
{
    m_position[0] += x;
    m_position[1] += y;
    m_position[2] += z;
}

void Magnet::rotate (float degrees, std::array<float, 3> axis)
{
    std::array<float, 4> pointQuaternion{ 0, m_position[0], m_position[1], m_position[2] };
    std::array<float, 4> rotationQuaternion = HelpFunctions::quaternion (degrees, axis);
    std::array<float, 4> inverse = HelpFunctions::inverseQuaternion (rotationQuaternion);
    std::array<float, 4> newPositionQuaternion =
    HelpFunctions::quaternionMultiplication (inverse, pointQuaternion, rotationQuaternion);

    std::copy (newPositionQuaternion.begin (), newPositionQuaternion.end (),
    m_position.data ());
}
void Magnet::rotate (float degrees, std::array<float, 3> axis, std::array<float, 3> anchor)
{
}

std::array<float, 3>& Magnet::orientation ()
{
    return m_orientation;
}

std::array<float, 3>& Magnet::position ()
{
    return m_position;
}

float Magnet::farFieldThreshold ()
{
    return m_farFieldThreshold;
}

float Magnet::magnetization ()
{
    return m_magnetization;
}
