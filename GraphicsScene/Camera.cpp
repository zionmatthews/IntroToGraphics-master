#include "Camera.h"
/**
*  Creates the camera and camera controls 
*/

glm::mat4 Camera::getViewMatrix()
{
	//Convert degrees to radians
	float yawR = glm::radians(m_yaw);
	float pitchR = glm::radians(m_pitch);

	//Forward vector
	glm::vec3 forward(
		cos(pitchR) * cos(yawR), sin(pitchR),
		cos(pitchR) * sin(yawR));

	//Return view matrix
	return glm::lookAt(m_position, m_position + forward, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::getProjectionMatrix(float width, float height)
{
	return glm::perspective(glm::pi<float>() * 0.25f,
		width / height,
		0.1f, 1000.0f);
}

/**
* Gets the yaw
*/
float Camera::getYaw()
{
	return m_yaw;
}

/**
* sets the yaw
*/
void Camera::setYaw(float degrees)
{
	m_yaw = degrees;
}

/**
* gets the pitch
*/
float Camera::getPitch()
{
	return m_pitch;
}

/**
* sets the pitch
*/
void Camera::setPitch(float degrees)
{
	m_pitch = degrees;
}

/**
* updates the camera with user input
*/
bool Camera::update(double deltaTime) 
{
	int keyForward = GLFW_KEY_W;
	int keyBack = GLFW_KEY_S;
	int keyLeft = GLFW_KEY_A;
	int keyRight = GLFW_KEY_D;
	int keyUp = GLFW_KEY_SPACE;
	int keyDown = GLFW_KEY_Q;

	//Convert degrees to radians
	float yawR = glm::radians(m_yaw);
	float pitchR = glm::radians(m_pitch);
	
	// Calculate the Forward vector
	glm::vec3 forward(
		cos(pitchR) * cos(yawR), sin(pitchR),
		cos(pitchR) * sin(yawR));

	//Calculate the right vector
	glm::vec3 right(-sin(yawR), 0.0f, cos(yawR));

	//Caculate the up vector
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	//Check input
	if (glfwGetKey(m_instance->getWindow(), keyForward)) {
		//Move forward
		m_position += forward * m_moveSpeed * (float)deltaTime;
	}
	if (glfwGetKey(m_instance->getWindow(), keyBack)) {
		//Move backward
		m_position -= forward * m_moveSpeed * (float)deltaTime;
	}
	if (glfwGetKey(m_instance->getWindow(), keyLeft)) {
		//Move left
		m_position -= right * m_moveSpeed * (float)deltaTime;
	}
	if (glfwGetKey(m_instance->getWindow(), keyRight)) {
		//Move right
		m_position += right * m_moveSpeed * (float)deltaTime;
	}
	if (glfwGetKey(m_instance->getWindow(), keyUp)) {
		//Move up
		m_position += up * m_moveSpeed * (float)deltaTime;
	}
	if (glfwGetKey(m_instance->getWindow(), keyDown)) {
		//Move down
		m_position -= up * m_moveSpeed * (float)deltaTime;
	}

	//Get current mouse position
	glfwGetCursorPos(m_instance->getWindow(), &m_currentMouseX, &m_currentMouseY);
	m_currentMouseX -= m_instance->getWidth() / 2;
	m_currentMouseY -= m_instance->getHeight() / 2;

	//Turn the camera based on the change in mouse position (delta mouse)
	if (glfwGetMouseButton(m_instance->getWindow(), GLFW_MOUSE_BUTTON_1)) {
		setYaw(getYaw() + m_turnSpeed * (m_currentMouseX - m_previousMouseX));
		setPitch(getPitch() - m_turnSpeed * (m_currentMouseY - m_previousMouseY));
	}
	//Store previous mouse coordinates
	m_previousMouseX = m_currentMouseX;
	m_previousMouseY = m_currentMouseY;

	return true;
}
