#ifndef MESHES_INCLUDE_GRIDGENERATOR
#define MESHES_INCLUDE_GRIDGENERATOR

#include <vector>

enum class Plane
{
	xy,
	xz,
	yz
};

class GridGenerator
{
public:
	GridGenerator (int gridHalfSize, float gridSpacing, Plane plane = Plane::xy);
	std::vector<float> vertices ();

private:
	std::vector<float> m_gridVertices;
};
#endif // MESHES_INCLUDE_GRIDGENERATOR