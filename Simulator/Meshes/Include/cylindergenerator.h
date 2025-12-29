#ifndef MESHES_INCLUDE_CYLINDERGENERATOR_
#define MESHES_INCLUDE_CYLINDERGENERATOR_

#include <vector>
#include <array>

class CylinderGenerator
{
public:
	CylinderGenerator (unsigned int faces, float radius, float height, std::array<float, 3> position);
	std::vector<float> vertices ();
	std::vector<unsigned int> indices ();

private:
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
};

#endif