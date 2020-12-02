#include <gl_core_4_4.h>
#include "App.h"
#include "Camera.h"
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <cstdio>

using glm::vec3;
using glm::vec4;
using glm::mat4;

App::App()
{
}

App::~App()
{
}

int App::run() 
{
	bool running = true;
	double deltaTime = 0.0f;
	double timeOfPreviousUpdate = 0.0;

	if (!start())
		return -1;

	while (running) {
		//Get the current time
		double timeOfCurrentUpdate = glfwGetTime();
		//Find the change in time
		deltaTime = timeOfCurrentUpdate - timeOfPreviousUpdate;
		//Store the current time for the next loop
		running = update(deltaTime);
		draw();
	}

	if (!end())
		return -2;
	return 0;
}

bool App::start()
{
	//Initialize GLFW
	if (!glfwInit()) {
		return false;
	}

	//Create a window
	m_window = glfwCreateWindow(1280, 720,"Space Graphics",nullptr, nullptr);

	//Ensure window was created
	if (m_window == nullptr) {
		glfwTerminate();
		return false;
	}

	//Focus the window
	glfwMakeContextCurrent(m_window);



	//Load OpenGl Loader functions
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		glfwMakeContextCurrent(m_window);
		glfwTerminate();
		return false;
	}

	//Print the OpenGL version number
	int major = ogl_GetMajorVersion();
	int minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	//Initialize Gizmos
	aie::Gizmos::create(10000, 10000, 10000, 10000);

	//Set the camera
	m_camera = new Camera(this);
	m_camera->setPosition({ 10, 10, 10 });
	m_camera->setYaw(-135.0f);
	m_camera->setPitch(-45.0f);

	

	//Set the color
	glClearColor(0.05f, 0.05f, 0.025f, 1.0f);
	//enables depth
	glEnable(GL_DEPTH_TEST);

	return true;
}

bool App::update(float deltaTime)
{
	glfwPollEvents();


	if (glfwWindowShouldClose(m_window) || glfwGetKey(m_window, GLFW_KEY_ESCAPE))
	{
		return false;
	}
	m_camera->update(deltaTime);

	return true;
}

bool App::draw()
{
	//Clear the window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Clear the Gizmos
	aie::Gizmos::clear();

	aie::Gizmos::addTransform(mat4(1), 4.0f);

	vec4 white(1, 1, 1, 1);
	vec4 black(0.5f, 0.5f, 0.5f, 1);

	for (int i = 0; i < 21; ++i) {
		aie::Gizmos::addLine(
			vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);
		aie::Gizmos::addLine(
			vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);

	}

	aie::Gizmos::draw(m_camera->getProjectionMatrix(2560, 1440)  *  m_camera->getViewMatyrix());
	glfwSwapBuffers(m_window);

	return true;
}

bool App::end()
{
	//Destroy the Gizmos
	aie::Gizmos::destroy();

	//Close the window
	glfwDestroyWindow(m_window);

	//Terminate GLFW
	glfwTerminate();

	return true;
}