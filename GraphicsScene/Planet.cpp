#include "Planet.h"

Planet::Planet(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
{
	m_position = position;
	m_rotation = rotation;
	m_scale = scale;
}

bool Planet::start()
{
	//Load sun texture
	if (!m_texture.load("Stars.jpg")) {
		printf("Failed to load sun.jpg.\n");
		return false;
	}

	m_mesh.initializeQuad();

	return true;
}

bool Planet::draw()
{
	//Bind texture
	m_texture.bind(0);

	//Draw "sun" mesh
	m_mesh.draw();

	return false;
}
