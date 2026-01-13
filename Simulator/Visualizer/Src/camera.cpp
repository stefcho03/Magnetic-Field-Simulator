#include <camera.h>

Camera::Camera (float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
: m_cameraFront (glm::vec3 (0.0f, 0.0f, -1.0f)), m_panSensitivity (PANSENSITIVITY), m_rotateSensitivity (ROTATESENSITIVITY), m_scrollSensitivity (ZOOM)
{
	m_cameraPos = glm::vec3 (posX, posY, posZ);
	m_up = glm::vec3 (upX, upY, upZ);
	m_yaw = yaw;
	m_pitch = pitch;
	updateCameraVectors ();
}

void Camera::processMouseMouseInput (bool rotate, bool move, double dx, double dy)
{
	if (rotate)
	{
		double rdx = dx * m_rotateSensitivity;
		double rdy = dy * m_rotateSensitivity;

		m_yaw -= rdx;
		m_pitch += rdy;
		m_pitch = glm::clamp (m_pitch, -89.0f, 89.0f);
	}

	if (move)
	{
		double pdx = dx * m_panSensitivity;
		double pdy = dy * m_panSensitivity;

		m_cameraPos -= m_cameraRight * (float)pdx;
		m_cameraPos += m_cameraUp * (float)pdy;
	}

	updateCameraVectors ();
}

void Camera::processMouseScroll (double offset)
{
	m_cameraPos += m_cameraFront * (float)offset * m_scrollSensitivity;
}

const glm::vec3 Camera::position () const
{
	return m_cameraPos;
}

const glm::mat4 Camera::view () const
{
	return glm::lookAt (m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}

void Camera::updateCameraVectors ()
{
	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos (glm::radians (m_yaw)) * cos (glm::radians (m_pitch));
	front.y = sin (glm::radians (m_pitch));
	front.z = sin (glm::radians (m_yaw)) * cos (glm::radians (m_pitch));
	m_cameraFront = glm::normalize (front);
	// also re-calculate the Right and Up vector
	// normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_cameraRight = glm::normalize (glm::cross (m_cameraFront, m_up));
	m_cameraUp = glm::normalize (glm::cross (m_cameraRight, m_cameraFront));
}