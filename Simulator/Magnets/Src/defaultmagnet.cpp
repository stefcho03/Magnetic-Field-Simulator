#include <cmath>
#include <defaultmagnet.h>
#include <helpfunctions.h>
#include <stdio.h>

Magnet::Magnet (std::array<float, 3> position, std::array<float, 3> orientation, float magnetization)
: m_position{ position[0], position[1], position[2] }, m_orientation{ orientation[0], orientation[1], orientation[2] }, m_magnetization (magnetization)
{
}

void Magnet::move (float x, float y, float z)
{
	m_position[0] += x;
	m_position[1] += y;
	m_position[2] += z;
	printf ("Magnet moved to: %f, %f, %f \n", m_position[0], m_position[1], m_position[2]);
}

void Magnet::rotate (float degrees, std::array<float, 3>& axis)
{
	std::array<float, 4> pointQuaternion{ 0, m_position[0], m_position[1], m_position[2] };
	std::array<float, 4> rotationQuaternion = HelpFunctions::quaternion (degrees, axis);
	std::array<float, 4> inverse = HelpFunctions::inverseQuaternion (rotationQuaternion);
	std::array<float, 4> newPositionQuaternion = HelpFunctions::quaternionMultiplication (inverse, pointQuaternion, rotationQuaternion);

	std::copy (newPositionQuaternion.begin (), newPositionQuaternion.end (), m_position.data ());
}
void Magnet::rotate (float degrees, std::array<float, 3>& axis, std::array<float, 3>& anchor)
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

std::array<float, 3> Magnet::field (const std::array<float, 3>& position)
{
	// Magnetic field strength axial components
	std::array<float, 3> magnetic_axial_components = { m_magnetization * m_orientation[0], m_magnetization * m_orientation[1], m_magnetization * m_orientation[2] };
	float r = HelpFunctions::calculateDistance (m_position, position);
	if (r == 0)
	{
		printf ("Measurement position the same as magnet origin. Not allowed!");
		return { 0.0f, 0.0f, 0.0f };
	}

	float r2 = r * r;
	float r3 = r2 * r;
	float r5 = r3 * r2;
	std::array<float, 3> retArr;
	std::array<float, 3> r_vec = { position[0] - m_position[0], position[1] - m_position[1], position[2] - m_position[2] };

	printf ("Distance: %f, Magnetization: %f\n", r, m_magnetization);
	float m_x_r = r_vec[0] * magnetic_axial_components[0] + r_vec[1] * magnetic_axial_components[1] + r_vec[2] * magnetic_axial_components[2];
	for (size_t i = 0; i < position.size (); i++)
		retArr[i] = (mu0 / (4 * M_PI)) * (3 * m_x_r * r_vec[i] / r5 - magnetic_axial_components[i] / r3);

	printf ("Field parameters at %f, %f, %f: %f, %f, %f \n", position[0], position[1], position[2], retArr[0], retArr[1], retArr[2]);
	return retArr;
}

float Magnet::magnetization ()
{
	return m_magnetization;
}
