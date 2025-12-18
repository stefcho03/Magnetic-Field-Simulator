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

std::array<float, 3> Magnet::field (std::array<float, 3> position)
{
    std::array<float, 3> m = { m_magnetization * m_orientation[0],
        m_magnetization * m_orientation[1], m_magnetization * m_orientation[2] };
    float r = HelpFunctions::calculateDistance (m_position, position);
    float m_x_r = position[0] * m[0] + position[1] * m[1] + position[2] * m[2];
    std::array<float, 3> retArr;
    for (size_t i = 0; i < position.size (); i++)
        retArr[i] = (mu0 / (4 * M_PI)) *
        (3 * m_x_r * position[i] / pow (r, 5) - m[i] / pow (r, 3));
    return retArr;
}

float Magnet::magnetization ()
{
    return m_magnetization;
}
