//
// Created by zzn on 22-5-12.
//

#ifndef DEMO_CAMERA_H
#define DEMO_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// 相机移动的几个可能选项
enum class Camera_Movement{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// 默认相机值
const float YAW = -90.0f;     //偏航角
const float PITCH = 0.0f;     //俯仰角
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;     //灵敏度
const float ZOOM = 45.0f;     //缩放

// 一个抽象的camera类，用于处理输入并计算相应的欧拉角、向量和矩阵
class Camera
{
public:
	// camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// euler Angles
	float Yaw;
	float Pitch;
	// camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	// constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	// returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix() const;

	// 处理从任何类似键盘的输入系统接收的输入。接受摄像机定义枚举形式的输入参数（从窗口系统中提取）
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	// 处理从鼠标输入系统接收的输入。需要x和y方向的偏移值。
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	// 处理从鼠标滚轮事件接收的输入。
	void ProcessMouseScroll(float yoffset);
private:
	// 从摄影机的（更新的）Euler角度计算向量
	void updateCameraVectors();
};


#endif //DEMO_CAMERA_H
