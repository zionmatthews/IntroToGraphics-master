#pragma once
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera;

class App
{
public:
	App();
	~App();

	int run();
	bool start();
	bool end();
	bool update(float deltaTime);
	bool draw();

	 GLFWwindow* getWindow() { return m_window; }
	 int getWidth() { return m_width; }
	 int getHeight() { return m_height; }
	 const char* getTitle() { return m_title; }

protected:
	 GLFWwindow* m_window;	
	Camera* m_camera;

private:
	int m_width;
	int m_height;
	const char* m_title;
};

