#ifndef VISUALIZER_INCLUDE_CAMERA_
#define VISUALIZER_INCLUDE_CAMERA_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement
{
	FORWARD,  // scroll
	BACKWARD, // scroll
	LEFT,	  // drag
	RIGHT	  // drag
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float PANSENSITIVITY = 0.0015f;
const float ROTATESENSITIVITY = 0.1f;
const float ZOOM = 5.0f;

class Camera
{
public:
	Camera (float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw = YAW, float pitch = PITCH);
	void processMouseMouseInput (bool rotate, bool move, double dx, double dy);
	void processMouseScroll (double offset);
	const glm::vec3 position () const;
	const glm::mat4 view () const;

private:
	void updateCameraVectors ();
	float distance();

	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraTarget;
	glm::vec3 m_cameraDirection;
	glm::vec3 m_up;
	glm::vec3 m_cameraUp;
	glm::vec3 m_cameraRight;
	glm::vec3 m_cameraFront;

	glm::mat4 m_view;
	bool m_rotate = false;
	bool m_move = false;

	float m_yaw, m_pitch, m_panSensitivity, m_rotateSensitivity, m_scrollSensitivity;
	double m_previousPosX, m_previousPosY;
};

#endif // VISUALIZER_INCLUDE_CAMERA_