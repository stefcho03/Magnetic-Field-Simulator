#ifndef MESHES_INCLUDE_MESH_
#define MESHES_INCLUDE_MESH_

#include <vector>
#include <glad/glad.h>

class Mesh
{
public:
	Mesh (const std::vector<float>& vertices, const std::vector<unsigned int>& indices = {});
	void draw () const;
	unsigned int getVertexCount () const;
	unsigned int getIndexCount () const;
	bool usesIndices () const;
	~Mesh ();

private:
	unsigned int m_VAO = 0;
	unsigned int m_VBO = 0;
	unsigned int m_EBO = 0;
	unsigned int m_vertexCount = 0;
	unsigned int m_indexCount = 0;
	bool m_hasIndices = false;
};

#endif // MESHES_INCLUDE_MESH_