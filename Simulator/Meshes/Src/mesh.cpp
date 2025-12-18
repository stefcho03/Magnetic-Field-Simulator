#include <mesh.h>

Mesh::Mesh (const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
: m_vertexCount (vertices.size () / 3), m_indexCount (indices.size ()), m_hasIndices (!indices.empty ())
{
	glGenVertexArrays (1, &m_VAO);
	glGenBuffers (1, &m_VBO);

	glBindVertexArray (m_VAO);
	// Any buffer calls will be used to configure the bound buffer (VBO)
	glBindBuffer (GL_ARRAY_BUFFER, m_VBO);
	// Copy vertex data into buffer's memory
	glBufferData (GL_ARRAY_BUFFER, vertices.size () * sizeof (float), vertices.data (), GL_STATIC_DRAW);

	/* 	1. Vertex attribute to configure. Tells where in the array to look (Our vertex shader - position has location 0)
		2. Size of attribute - 3 (3D)
		3. Data type
		4. Normalize data (yes, no)
		5. How big is the array (Where to look next)
		6. Offset - Where the data begins
	*/
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float), (void*)0);
	glEnableVertexAttribArray (0); // Enable the vertex attribute
	if (m_hasIndices)
	{
		glGenBuffers (1, &m_EBO);
		glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData (GL_ELEMENT_ARRAY_BUFFER, indices.size () * sizeof (unsigned int), indices.data (), GL_STATIC_DRAW);
	}

	glBindVertexArray (0);
}

void Mesh::draw () const
{
	glBindVertexArray (m_VAO);
	if (m_hasIndices)
		glDrawElements (GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays (GL_TRIANGLES, 0, m_vertexCount);
	glBindVertexArray (0);
}

unsigned int Mesh::getVertexCount () const
{
	return m_vertexCount;
}
unsigned int Mesh::getIndexCount () const
{
	return m_indexCount;
}
bool Mesh::usesIndices () const
{
	return m_hasIndices;
}

Mesh::~Mesh ()
{
	glDeleteVertexArrays (1, &m_VAO);
	glDeleteBuffers (1, &m_VBO);
	if (m_hasIndices)
		glDeleteBuffers (1, &m_EBO);
}