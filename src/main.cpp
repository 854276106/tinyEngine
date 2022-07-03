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
float deltaTime = 0.0f;	// 当前帧和最后一帧之间的时间
float lastFrame = 0.0f;  //最后一帧
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
	if (firstMouse)   //鼠标第一次进入
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	float deltaX, deltaY;  //鼠标距上一帧的偏移量
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
//异常回调函数
void error_callback(int error,const char* description)
{
	std::cout << "Error:" << error+description << std::endl;
}
//视口尺寸回调函数  视口和窗口大小保持一致
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void InitRenderData()
{
	ResourceManager::LoadShader("../Resource/Shader/box.vert",
			"../Resource/Shader/box.frag",nullptr,"box");
	ResourceManager::LoadShader("../Resource/Shader/light.vert",
			"../Resource/Shader/light.frag",nullptr,"light");

	ResourceManager::LoadTexture("../Resource/Texture/awesomeface.png",GL_TRUE,"face",0);
	ResourceManager::LoadTexture("../Resource/Texture/container.jpg",GL_FALSE,"container",1);
	ResourceManager::LoadTexture("../Resource/Texture/container2.png",GL_TRUE,"container2",2);
	ResourceManager::LoadTexture("../Resource/Texture/container2_specular.png",GL_TRUE,"container2_specular",3);

	unsigned int VAO;
	glGenVertexArrays(1,&VAO);
	//创建VBO顶点缓冲对象
	unsigned int VBO;
	glGenBuffers(1,&VBO);
	//绑定缓冲类型
	glBindBuffer(GL_ARRAY_BUFFER,VBO);

	glBindVertexArray(VAO);
	//将用户数据复制到当前绑定缓冲(GL_ARRAY_BUFFER)    将数据从CPU复制到GPU
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

	/*设置顶点属性指针 */
	//位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)nullptr);
	glEnableVertexAttribArray(0);
	//法线属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// 纹理属性
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0+ResourceManager::GetTexture("face").Slot);
	ResourceManager::GetTexture("face").Bind();
	glActiveTexture(GL_TEXTURE0+ResourceManager::GetTexture("container").Slot);
	ResourceManager::GetTexture("container").Bind();
	glActiveTexture(GL_TEXTURE0+ResourceManager::GetTexture("container2").Slot);
	ResourceManager::GetTexture("container2").Bind();
	glActiveTexture(GL_TEXTURE0+ResourceManager::GetTexture("container2_specular").Slot);
	ResourceManager::GetTexture("container2_specular").Bind();
}

void Render()
{
	Shader lightShader=ResourceManager::GetShader("light");
	Shader boxShader=ResourceManager::GetShader("box");
	Material *boxMaterial=new Material(
			glm::vec3(0.0f, 0.0f, 0.0f),
			ResourceManager::GetTexture("container2").TextureID,
			ResourceManager::GetTexture("container2_specular").TextureID,
			32.0f);

	boxShader.Use();
	boxShader.SetVector3f("viewPos", camera.Position);
	// directional light
	boxShader.SetVector3f("dirLight.direction", lightDirectional.direction);
	boxShader.SetVector3f("dirLight.color", lightDirectional.color);
	boxShader.SetVector3f("dirLight.ambient", lightDirectional.ambient);
	boxShader.SetVector3f("dirLight.diffuse", lightDirectional.diffuse);
	boxShader.SetVector3f("dirLight.specular", lightDirectional.specular);

	// point light
	boxShader.SetVector3f("pointLights[0].position", lightPoint[0].position);
	boxShader.SetVector3f("pointLights[0].color", lightPoint[0].color);
	boxShader.SetVector3f("pointLights[0].ambient", lightPoint[0].ambient);
	boxShader.SetVector3f("pointLights[0].diffuse", lightPoint[0].diffuse);
	boxShader.SetVector3f("pointLights[0].specular", lightPoint[0].specular);
	boxShader.SetFloat("pointLights[0].constant", lightPoint[0].constant);
	boxShader.SetFloat("pointLights[0].linear", lightPoint[0].linear);
	boxShader.SetFloat("pointLights[0].quadratic", lightPoint[0].quadratic);

	boxShader.SetVector3f("pointLights[1].position", lightPoint[1].position);
	boxShader.SetVector3f("pointLights[1].color", lightPoint[1].color);
	boxShader.SetVector3f("pointLights[1].ambient", lightPoint[1].ambient);
	boxShader.SetVector3f("pointLights[1].diffuse", lightPoint[1].diffuse);
	boxShader.SetVector3f("pointLights[1].specular", lightPoint[1].specular);
	boxShader.SetFloat("pointLights[1].constant", lightPoint[1].constant);
	boxShader.SetFloat("pointLights[1].linear", lightPoint[1].linear);
	boxShader.SetFloat("pointLights[1].quadratic", lightPoint[1].quadratic);

	boxShader.SetVector3f("pointLights[2].position", lightPoint[2].position);
	boxShader.SetVector3f("pointLights[2].color", lightPoint[2].color);
	boxShader.SetVector3f("pointLights[2].ambient", lightPoint[2].ambient);
	boxShader.SetVector3f("pointLights[2].diffuse", lightPoint[2].diffuse);
	boxShader.SetVector3f("pointLights[2].specular", lightPoint[2].specular);
	boxShader.SetFloat("pointLights[2].constant", lightPoint[2].constant);
	boxShader.SetFloat("pointLights[2].linear", lightPoint[2].linear);
	boxShader.SetFloat("pointLights[2].quadratic", lightPoint[2].quadratic);

	boxShader.SetVector3f("pointLights[3].position", lightPoint[3].position);
	boxShader.SetVector3f("pointLights[3].color", lightPoint[3].color);
	boxShader.SetVector3f("pointLights[3].ambient", lightPoint[3].ambient);
	boxShader.SetVector3f("pointLights[3].diffuse", lightPoint[3].diffuse);
	boxShader.SetVector3f("pointLights[3].specular", lightPoint[3].specular);
	boxShader.SetFloat("pointLights[3].constant", lightPoint[3].constant);
	boxShader.SetFloat("pointLights[3].linear", lightPoint[3].linear);
	boxShader.SetFloat("pointLights[3].quadratic", lightPoint[3].quadratic);

	// spotLight
	boxShader.SetVector3f("spotLight.position", camera.Position);
	boxShader.SetVector3f("spotLight.direction", camera.Front);
	boxShader.SetVector3f("spotLight.color", lightSpot.color);
	boxShader.SetVector3f("spotLight.ambient", lightSpot.ambient);
	boxShader.SetVector3f("spotLight.diffuse", lightSpot.diffuse);
	boxShader.SetVector3f("spotLight.specular", lightSpot.specular);
	boxShader.SetFloat("spotLight.constant", lightSpot.constant);
	boxShader.SetFloat("spotLight.linear", lightSpot.linear);
	boxShader.SetFloat("spotLight.quadratic", lightSpot.quadratic);
	boxShader.SetFloat("spotLight.cutOff", lightSpot.cutOff);
	boxShader.SetFloat("spotLight.outerCutOff", lightSpot.outerCutOff);

	// create transformations
	glm::mat4 view          = glm::mat4(1.0f);
	glm::mat4 projection    = glm::mat4(1.0f);
	view = camera.GetViewMatrix();
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	boxShader.SetMatrix4("view",view);
	boxShader.SetMatrix4("projection",projection);

	boxShader.Use();
	for (auto & cubePosition : cubePositions)
	{
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePosition);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-45.0f), glm::vec3(1.0f, 0.3f, 0.5f));
		boxShader.SetMatrix4("model",model);

		//set Material -> Uniforms
		boxShader.SetVector3f("material.ambient", boxMaterial->ambient);
		boxShader.SetInteger("material.diffuse", ResourceManager::GetTexture("container2").Slot);
		boxShader.SetInteger("material.specular", ResourceManager::GetTexture("container2_specular").Slot);
		boxShader.SetFloat("material.shininess", boxMaterial->shiness);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	lightShader.Use();
	lightShader.SetMatrix4("view",view);
	lightShader.SetMatrix4("projection",projection);

	for (auto & pointLightPosition : pointLightPositions)
	{
	// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, pointLightPosition);
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		lightShader.SetMatrix4("model",model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

int main()
{
	//初始化glfw库
	if (glfwInit()==-1)
	{
		return -1;
	}
	
	//设置opengl版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建窗口
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"Demo", nullptr, nullptr);
	if (window==nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
        //结束，释放分配的内存
		glfwTerminate();
		return -1;
	}

	//设置当前窗口，绑定上下文
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
	glfwSetErrorCallback(error_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //隐藏鼠标光标
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
	//创建视口
	glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);

	//开启深度测试
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	InitRenderData();

	while(!glfwWindowShouldClose(window))
	{
		//计算每帧时间
		auto currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		//设置屏幕颜色。 当调用glClear函数，清除颜色缓冲之后，整个颜色缓冲都会被填充为glClearColor里所设置的颜色。
		glClearColor(0.2f,0.3f,0.3f,1.0f);
		// 清除缓冲区
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//当前可写的颜色缓冲

		Render();

		//Swap front and back buffers (交换颜色缓冲)
		glfwSwapBuffers(window);

 		//Poll for and process events (检测是否有事件出发（鼠标、键盘）)
		glfwPollEvents();
	}

}
