#include "Actor.h"

/**
* The class used to set any mesh objects transform, position, scale etc
*/
Actor::Actor(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
{
	m_position = position;
	m_rotation = rotation;
	m_scale = scale;
}
//grabs the transform
glm::mat4 Actor::getTransform()
{
	if (m_parent)
	{
		return m_parent->getTransform() * glm::translate(m_position) * glm::toMat4(m_rotation) * glm::scale(m_scale);
	}

	return glm::translate(m_position) * glm::toMat4(m_rotation) * glm::scale(m_scale);
}
//grabs the position
glm::vec3 Actor::getParentPosition()
{
	if (m_parent)
	{
		return m_parent->getPosition();
	}

	return glm::vec3(0.0f);
}
//grabs the rotation
glm::quat Actor::getParentRotation()
{
	if (m_parent)
	{
		return m_parent->getRotation();
	}

	return glm::quat(glm::vec3(0.0f));
}
