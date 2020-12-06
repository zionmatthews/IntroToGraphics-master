#include "Game.h"
#include "Camera.h"
#include <cstdio>

using glm::vec3;
using glm::vec4;
using glm::mat4;

/**
* Everything is placed in here to builed the scene
*/

//Constructer
Game::Game()
{
}

//Constructer
Game::~Game()
{
}

//Start of the loop
int Game::run() 
{
	bool running = true;
	bool drawing = true;

	double deltaTime = 0.0f;
	double timeOfPreviousUpdate = 0.0;

	if (!start())
		return -1;

	while (running && drawing) {
		//Get the current time
		double timeOfCurrentUpdate = glfwGetTime();
		//Find the change in time
		deltaTime = timeOfCurrentUpdate - timeOfPreviousUpdate;
		//Store the current time for the next loop
		timeOfPreviousUpdate = timeOfCurrentUpdate;

		running = update(deltaTime);
		drawing = draw();
	}

	if (!end())
		return -2;
	return 0;
}

//runs the window,shader, and all gizmos
bool Game::start()
{
	//Initialize GLFW
	if (!glfwInit()) {
		return false;
	}

	//Create a window
	m_window = glfwCreateWindow(1280, 720,"Sun Bun",nullptr, nullptr);

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

	//Set the color
		glClearColor(0.05f, 0.05f, 0.025f, 1.0f);
	//enables depth
	glEnable(GL_DEPTH_TEST);

	//Initialize shader
	m_shader.loadShader(aie::eShaderStage::VERTEX, "simple.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "simple.frag");

	if (!m_shader.link())
	{
		printf("Shader Error: %s\n", m_shader.getLastError());

		return false;
	}

	if (!m_objMesh.load("Bunny.obj"))
	{
		printf("Failed to load obj.\n");
		return false;
	}
	
	

	//Initialize Gizmos
	aie::Gizmos::create(10000, 10000, 10000, 10000);

	//Set the camera
	m_camera = new Camera(this);
	m_camera->setPosition({ 10, 10, 10 });
	m_camera->setYaw(-135.0f);
	m_camera->setPitch(-45.0f);

	m_planet = new Planet(
		{ 200.0f, 0.0f, 0.0f },
		glm::vec3(0.0f, 0.0f, 4.7f),
		{ 300.0f, 300.0f, 300.0f }
	);

	
	
	m_planet->start();
	
	//Set up the identity transform
	m_meshTransform = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	m_light.setAmbient({ 1.66f, 0.0f, 0.0f });
	m_light.setDiffuse({ 1.66f, 0.0f, 0.0f });
	m_light.setSpecular({ 1.66f, 0.0f, 0.0f });
				
	return true;
}

//Updates the game loop
bool Game::update(double deltaTime)
{
	glfwPollEvents();

	
	if (glfwWindowShouldClose(m_window) || glfwGetKey(m_window, GLFW_KEY_ESCAPE))
	{
		return false;
	}
	m_camera->update(deltaTime);

	float time = glfwGetTime();

	m_light.setDirection(glm::normalize(glm::vec3(glm::cos(time * 2), -1, glm::sin(time * 2))));

	return true;
}

//Draws everything into the scene
bool Game::draw()
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

	//Get the projection and view matrices
	mat4 projectionMatrix = m_camera->getProjectionMatrix(m_width, m_height);
	mat4 viewMatrix = m_camera->getViewMatrix();

	//Bind shader
	m_shader.bind();

	//Bind camera
	m_shader.bindUniform("CameraPosition", m_camera->getPosition());

	//Bind light
	m_shader.bindUniform("Ga", m_light.getAmbient());
	m_shader.bindUniform("Gd", m_light.getDiffuse());
	m_shader.bindUniform("Gs", m_light.getSpecular());
	m_shader.bindUniform("LightDirection", m_light.getDirection());
	
	//Bind and draw the planet
	mat4 pvm = projectionMatrix * viewMatrix * m_planet->getTransform();
	m_shader.bindUniform("ProjectionViewModel", pvm);

	m_shader.bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_planet->getTransform())));
	m_shader.bindUniform("ModelMatrix", m_planet->getTransform());


	m_shader.bindUniform("diffuseTexture", 0);


	m_planet->draw();
	

	//Draw obj mesh	
	pvm = projectionMatrix * viewMatrix * m_meshTransform;
	m_shader.bindUniform("ProjectionViewModel", pvm);
	m_shader.bindUniform("diffuseTexture", 0);
	m_objMesh.draw();

	aie::Gizmos::draw(projectionMatrix * viewMatrix);

	glfwSwapBuffers(m_window);

	return true;
}

//deletes and end the program
bool Game::end()
{
	//Destroy the Gizmos
	aie::Gizmos::destroy();

	//Close the window
	glfwDestroyWindow(m_window);

	//Terminate GLFW
	glfwTerminate();

	return true;
}