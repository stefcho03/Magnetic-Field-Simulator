#ifndef MESHES_INCLUDE_MESH_
#define MESHES_INCLUDE_MESH_

#include <vector>
#include <glad/glad.h>

enum class PrimitiveType
{
	Triangles,
	Lines
};

class Mesh
{
public:
	Mesh (const std::vector<float>& vertices, const std::vector<unsigned int>& indices = {}, PrimitiveType type = PrimitiveType::Triangles);
	Mesh (Mesh&& other) noexcept;
	Mesh (const Mesh&) = delete;
	Mesh& operator= (const Mesh&) = delete;
	Mesh& operator= (Mesh&& other) noexcept;

	void draw () const;
	unsigned int getVertexCount () const;
	unsigned int getIndexCount () const;
	bool usesIndices () const;
	~Mesh ();

private:
	void cleanup ();
	unsigned int m_VAO = 0;
	unsigned int m_VBO = 0;
	unsigned int m_EBO = 0;
	unsigned int m_vertexCount = 0;
	unsigned int m_indexCount = 0;
	bool m_hasIndices = false;
	PrimitiveType m_type;
};

#endif // MESHES_INCLUDE_MESH_