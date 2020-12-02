#pragma once
#include "App.h"
#include "Actor.h"
#include <glm/glm.hpp>

class Camera : public Actor
{
public:
	Camera(App* instance) { m_instance = instance; }
	~Camera() {};

	glm::mat4 getViewMatyrix();
	glm::mat4 getProjectionMatrix(float width, float height);

	float getyaw() { return m_yaw; }
	void setYaw(float degrees) { m_yaw = degrees; }

	float getpitch() { return m_pitch; }
	void setPitch(float degrees) { m_pitch = degrees; }
	glm::vec3 sgetPosition() { return m_position; }
	void setPosition(glm::vec3 position) { m_position = position; }

	bool update(double deltaTime) override;

private:
	App* m_instance;

	float m_yaw;
	float m_pitch;

	glm::vec3 m_position{ 0.0f, 0.0f, 0.0f };

	float m_turnSpeed = 0.1f;
	float m_moveSpeed = 0.3f;

	double m_currentMouseX = 0.0f;
	double m_currentMouseY = 0.0f;
	double m_previousMouseX = 0.0f;
	double m_previousMouseY = 0.0f;
};

