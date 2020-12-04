#pragma once
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <Gizmos.h>
#include <Texture.h>
#include "OBJMesh.h"
#include "Shader.h"
#include "Mesh.h"
#include "Light.h"
#include "Planet.h"
class Camera;

class Game
{
	

public:
	Game();
	~Game();

	int run();

	bool start();
	bool end();
	bool update(double deltaTime);
	bool draw();


	 GLFWwindow* getWindow() { return m_window; }
	 int getWidth() { return m_width; }
	 int getHeight() { return m_height; }
	 const char* getTitle() { return m_title; }

protected:
	 GLFWwindow* m_window;	
	Camera* m_camera;

	Planet* m_planet;
	Planet* m_planet2;

	Mesh m_mesh;
	glm::mat4 m_meshTransform;
	aie::ShaderProgram m_shader;
	aie::Texture m_texture;
	aie::OBJMesh m_objMesh;
	Light m_light;

private:
	int m_width;
	int m_height;
	const char* m_title;
};

