//
// Created by zzn on 22-5-12.
//

#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch )
			: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED),
			MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
		: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY),Zoom(ZOOM)
{
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	switch (direction)
	{
	case Camera_Movement::FORWARD:
		Position += Front * velocity;
		break;
	case Camera_Movement::BACKWARD:
		Position -= Front * velocity;
		break;
	case Camera_Movement::LEFT:
		Position -= Right * velocity;
		break;
	case Camera_Movement::RIGHT:
		Position += Right * velocity;
		break;
	case Camera_Movement::UP:
		Position += WorldUp * velocity;
		break;
	case Camera_Movement::DOWN:
		Position -= WorldUp * velocity;
		break;
	default:
		break;
	}
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	// 确保当俯仰超出边界时，屏幕不会翻转
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	Zoom -= (float)yoffset;  //竖直滚动大小
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
	// calculate the new Front vector
	glm::vec3 front;
	front.x = static_cast<float>(cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)));
	front.y = static_cast<float>(sin(glm::radians(Pitch)));
	front.z = static_cast<float>(sin(glm::radians(Yaw)) * cos(glm::radians(Pitch)));
	Front = glm::normalize(front);
	// also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize(glm::cross(Right, Front));
}


