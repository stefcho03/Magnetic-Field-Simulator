#include <gridgenerator.h>

GridGenerator::GridGenerator (int gridHalfSize, float gridSpacing, Plane plane)
{
	if (plane == Plane::xy)
	{
		for (int i = -gridHalfSize; i <= gridHalfSize; ++i)
		{
			float p = (float)i * gridSpacing;

			// vertical lines (parallel to Y)
			m_gridVertices.push_back (p);								   // x
			m_gridVertices.push_back ((float)-gridHalfSize * gridSpacing); // y
			m_gridVertices.push_back (0.0f);							   // z

			m_gridVertices.push_back (p);
			m_gridVertices.push_back ((float)gridHalfSize * gridSpacing);
			m_gridVertices.push_back (0.0f);

			// horizontal lines (parallel to X)
			m_gridVertices.push_back ((float)-gridHalfSize * gridSpacing);
			m_gridVertices.push_back (p);
			m_gridVertices.push_back (0.0f);

			m_gridVertices.push_back ((float)gridHalfSize * gridSpacing);
			m_gridVertices.push_back (p);
			m_gridVertices.push_back (0.0f);
		}
	}
	if (plane == Plane::xz)
	{
		for (int i = -gridHalfSize; i <= gridHalfSize; ++i)
		{
			float p = (float)i * gridSpacing;

			// vertical lines (parallel to Y)
			m_gridVertices.push_back (p);								   // x
			m_gridVertices.push_back (0.0f);							   // z
			m_gridVertices.push_back ((float)-gridHalfSize * gridSpacing); // y

			m_gridVertices.push_back (p);
			m_gridVertices.push_back (0.0f);
			m_gridVertices.push_back ((float)gridHalfSize * gridSpacing);

			// horizontal lines (parallel to X)
			m_gridVertices.push_back ((float)-gridHalfSize * gridSpacing);
			m_gridVertices.push_back (0.0f);
			m_gridVertices.push_back (p);

			m_gridVertices.push_back ((float)gridHalfSize * gridSpacing);
			m_gridVertices.push_back (0.0f);
			m_gridVertices.push_back (p);
		}
	}
	if (plane == Plane::yz)
	{
		for (int i = -gridHalfSize; i <= gridHalfSize; ++i)
		{
			float p = (float)i * gridSpacing;

			// vertical lines (parallel to Y)
			m_gridVertices.push_back (0.0f);							   // z
			m_gridVertices.push_back (p);								   // x
			m_gridVertices.push_back ((float)-gridHalfSize * gridSpacing); // y

			m_gridVertices.push_back (0.0f);
			m_gridVertices.push_back (p);
			m_gridVertices.push_back ((float)gridHalfSize * gridSpacing);

			// horizontal lines (parallel to X)
			m_gridVertices.push_back (0.0f);
			m_gridVertices.push_back ((float)-gridHalfSize * gridSpacing);
			m_gridVertices.push_back (p);

			m_gridVertices.push_back (0.0f);
			m_gridVertices.push_back ((float)gridHalfSize * gridSpacing);
			m_gridVertices.push_back (p);
		}
	}
}

std::vector<float> GridGenerator::vertices ()
{
	return m_gridVertices;
}