#include <cubegenerator.h>

CubeGenerator::CubeGenerator (float side, std::array<float, 3> position)
{
	// Define coordinates for 2 squares
	m_vertices = {
		position[0] + side / 2,
		position[1] - side / 2,
		position[2] + side / 2,

		position[0] - side / 2,
		position[1] - side / 2,
		position[2] + side / 2,

		position[0] - side / 2,
		position[1] + side / 2,
		position[2] + side / 2,

		position[0] + side / 2,
		position[1] + side / 2,
		position[2] + side / 2,

		position[0] + side / 2,
		position[1] - side / 2,
		position[2] - side / 2,

		position[0] - side / 2,
		position[1] - side / 2,
		position[2] - side / 2,

		position[0] - side / 2,
		position[1] + side / 2,
		position[2] - side / 2,

		position[0] + side / 2,
		position[1] + side / 2,
		position[2] - side / 2,
	};

	m_indices = { 0,
		1,
		2,
		0,
		2,
		3,

		0,
		3,
		4,
		3,
		4,
		7,

		1,
		2,
		5,
		2,
		5,
		6,

		0,
		1,
		5,
		0,
		4,
		5,

		4,
		5,
		6,
		4,
		6,
		7,

		2,
		3,
		6,
		3,
		6,
		7 };
}

std::vector<unsigned int> CubeGenerator::indices ()
{
	return m_indices;
}

std::vector<float> CubeGenerator::vertices ()
{
	return m_vertices;
}