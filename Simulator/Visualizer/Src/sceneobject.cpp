#include <sceneobject.h>

SceneObject::SceneObject (Mesh&& mesh) : m_mesh (std::move (mesh))
{
}

void SceneObject::setTransform (const glm::mat4& transform)
{
	m_transform = transform;
}

const glm::mat4& SceneObject::transform () const
{
	return m_transform;
}
void SceneObject::draw () const
{
	m_mesh.draw ();
}