#ifndef VISUALIZER_INCLUDE_SCENEOBJECT_
#define VISUALIZER_INCLUDE_SCENEOBJECT_

#include <mesh.h>
#include <glm/glm.hpp>

class SceneObject
{
public:
	SceneObject (Mesh&& mesh);
	SceneObject (SceneObject&& other) noexcept = default;
	SceneObject& operator= (SceneObject&& other) noexcept = default;
	SceneObject (const SceneObject&) = delete;
	SceneObject& operator= (const SceneObject&) = delete;

	void setTransform (const glm::mat4& transform);
	const glm::mat4& transform () const;
	void draw () const;

private:
	Mesh m_mesh;
	glm::mat4 m_transform;
};

#endif // VISUALIZER_INCLUDE_SCENEOBJECT_
