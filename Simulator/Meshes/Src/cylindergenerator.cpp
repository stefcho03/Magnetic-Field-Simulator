#include <cylindergenerator.h>
#define _USE_MATH_DEFINES
#include <math.h>

CylinderGenerator::CylinderGenerator (unsigned int faces, float radius, float height, std::array<float, 3> position)
{
	// Center of upper circle
	m_vertices.push_back (position[0]);
	m_vertices.push_back (position[1] + height / 2);
	m_vertices.push_back (position[2]);

	// Center of lower circle
	m_vertices.push_back (position[0]);
	m_vertices.push_back (position[1] - height / 2);
	m_vertices.push_back (position[2]);

	// Create upper circle
	for (unsigned int i = 1; i < faces + 1; i++)
	{
		m_vertices.push_back (position[0] + radius * cos (2.0f * M_PI * i / faces));
		m_vertices.push_back (position[1] + height / 2);
		m_vertices.push_back (position[2] + radius * sin (2.0f * M_PI * i / faces));

		m_indices.push_back (0);
		m_indices.push_back (i + 1);
		m_indices.push_back (i + 2);
	}

	m_indices.push_back (0);
	m_indices.push_back (2);
	m_indices.push_back (faces + 1);

	// Create lower circle
	for (unsigned int i = 0; i < faces + 1; i++)
	{
		m_vertices.push_back (position[0] + radius * cos (2.0f * M_PI * i / faces));
		m_vertices.push_back (position[1] - height / 2);
		m_vertices.push_back (position[2] + radius * sin (2.0f * M_PI * i / faces));

		m_indices.push_back (1);
		m_indices.push_back (i + faces + 1);
		m_indices.push_back (i + faces + 2);
	}

	m_indices.push_back (1);
	m_indices.push_back (faces + 1);
	m_indices.push_back (2 * faces + 1);

	// Side
	for (unsigned int i = 0; i < faces + 1; i++)
	{
		m_indices.push_back (i + 1);
		m_indices.push_back (i + 2);
		m_indices.push_back (i + faces + 1);

		m_indices.push_back (i + 2);
		m_indices.push_back (i + faces + 1);
		m_indices.push_back (i + faces + 2);
	}
}

std::vector<float> CylinderGenerator::vertices ()
{
	return m_vertices;
}

std::vector<unsigned int> CylinderGenerator::indices ()
{
	return m_indices;
}
