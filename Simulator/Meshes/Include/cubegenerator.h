#ifndef MESHES_INCLUDE_CUBEGENERATOR_
#define MESHES_INCLUDE_CUBEGENERATOR_

#include <vector>
#include <array>

class CubeGenerator
{
public:
	CubeGenerator (float side, std::array<float, 3> position);
	std::vector<float> vertices ();
	std::vector<unsigned int> indices ();

private:
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
};

#endif // MESHES_INCLUDE_CUBEGENERATOR