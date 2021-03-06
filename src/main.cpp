#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ResourceManager.h"
#include "Camera.h"
#include "LightSource.h"
#include "Material.h"
#include "RenderData.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const unsigned int SCR_WIDTH=800;
const unsigned int SCR_HEIGHT=600;

bool isFullScreen = false;
void FullScreen(GLFWwindow* window)
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	if (!isFullScreen)
	{
		glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
		isFullScreen = true;
	}
	else if (isFullScreen)
	{
		glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, SCR_WIDTH, SCR_HEIGHT, mode->refreshRate);

		isFullScreen = false;
	}
}

bool isMax = false;
void MaxScreen(GLFWwindow* window)
{

	if (!isMax)
	{
		glfwMaximizeWindow(window);
		isMax = true;
	}
	else if (isMax)
	{
		glfwRestoreWindow(window);
		isMax = false;
	}
}

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));


#pragma region Light Declare

LightDirectional lightDirectional(glm::vec3(0.05f, 0.05f, 0.05f),glm::vec3(0.4f, 0.4f, 0.4f),
		glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.2f, -1.0f, -0.3f));

std::vector <LightPoint> lightPoint = {
		LightPoint(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f),
				pointLightPositions[0], 1.0f, 0.09f, 0.032f, glm::vec3(0.0f,0.9f,0.8f)),

		LightPoint(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f),
				pointLightPositions[1], 1.0f, 0.09f, 0.032f, glm::vec3(1.0f,0.9f,0.8f)),

		LightPoint(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f),
				pointLightPositions[2], 1.0f, 0.09f, 0.032f, glm::vec3(1.0f,0.9f,0.8f)),

		LightPoint(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f),
				pointLightPositions[3], 1.0f, 0.09f, 0.032f, glm::vec3(1.0f,0.9f,0.8f))
};

LightSpot lightSpot(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
		1.0f, 0.09f, 0.032f, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)));

#pragma endregion

// timing
float deltaTime = 0.0f;	// ???????????????????????????????????????
float lastFrame = 0.0f;  //????????????
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::DOWN, deltaTime);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_PRESS)
		return;
	switch (key)
	{
	case GLFW_KEY_F10:
		MaxScreen(window);
		break;
	case GLFW_KEY_F11:
		FullScreen(window);
		break;
	default:
		break;
	}
}

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
void mouse_callback(GLFWwindow*window,double _xPos,double _yPos)
{
	auto xPos=static_cast<float>(_xPos);
	auto yPos=static_cast<float>(_yPos);
	if (firstMouse)   //?????????????????????
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	float deltaX, deltaY;  //??????????????????????????????
	deltaX = xPos - lastX;
	deltaY = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(deltaX, deltaY);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
//??????????????????
void error_callback(int error,const char* description)
{
	std::cout << "Error:" << error+description << std::endl;
}
//????????????????????????  ?????????????????????????????????
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void InitRenderData()
{
	ResourceManager::LoadShader("../Resource/Shader/nanosuit.vert",
			"../Resource/Shader/nanosuit.frag",nullptr,"nanosuit");

	ResourceManager::LoadModel("../Resource/Model/nanosuit/nanosuit.obj","nanosuit");
}

void Render()
{
	Shader nanosuitShader=ResourceManager::GetShader("nanosuit");
	nanosuitShader.Use();

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	nanosuitShader.SetMatrix4("projection", projection);
	nanosuitShader.SetMatrix4("view", view);

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
	nanosuitShader.SetMatrix4("model", model);

	Model nanosuit=ResourceManager::GetModel("nanosuit");
	nanosuit.Draw(nanosuitShader);
}

int main()
{
	//?????????glfw???
	if (glfwInit()==-1)
	{
		return -1;
	}
	
	//??????opengl??????
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//????????????
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"Demo", nullptr, nullptr);
	if (window==nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
        //??????????????????????????????
		glfwTerminate();
		return -1;
	}

	//????????????????????????????????????
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
	glfwSetErrorCallback(error_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //??????????????????
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	//Init GLEW

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//????????????
	glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);

	//??????????????????
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	InitRenderData();

	while(!glfwWindowShouldClose(window))
	{
		//??????????????????
		auto currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		//????????????????????? ?????????glClear????????????????????????????????????????????????????????????????????????glClearColor????????????????????????
		glClearColor(0.2f,0.3f,0.3f,1.0f);
		// ???????????????
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//???????????????????????????

		Render();

		//Swap front and back buffers (??????????????????)
		glfwSwapBuffers(window);

 		//Poll for and process events (????????????????????????????????????????????????)
		glfwPollEvents();
	}

}
