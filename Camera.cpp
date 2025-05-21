#include "Camera.h"

Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	// Solo actualizamos yaw para rotar el personaje horizontalmente
	yaw += xChange;
	pitch += yChange;

	// Limitar pitch para no volcar la cámara
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	update();
}

float Camera::getYaw()
{
	return yaw;
}

glm::mat4 Camera::calculateViewMatrix()
{
	if (isThirdPerson == 1)
	{
		position = *target - (front * thirdPersonOffset.z) + glm::vec3(0.0f, thirdPersonOffset.y, 0.0f);
		return glm::lookAt(position, *target, glm::vec3(0.0f, 1.0f, 0.0f));
	}
	else if (isThirdPerson == 2)
	{	
			position = *target + glm::vec3(0.0f, 20.0f, 0.0f);
			return glm::lookAt(position, position + front, up);
	}
	else
	{
		glm::vec3 worldCenter = glm::vec3(0.0f, 0.0f, 0.0f);
		position = glm::vec3(0.0f, 900.0f, 0.01f);
		glm::vec3 lookingAt = worldCenter;
		glm::vec3 upVector = glm::vec3(0.0f, 0.0f, -1.0f);

		return glm::lookAt(position, lookingAt, upVector);
	}
}


glm::vec3 Camera::getCameraPosition()
{
	return position;
}

glm::vec3 Camera::getCameraFront()
{
	return front;
}

glm::vec3 Camera::getCameraRight()
{
	return right;
}

glm::vec3 Camera::getCameraUp()
{
	return up;
}


glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

void Camera::enableThirdPerson(glm::vec3* characterPosition, glm::vec3 offset)
{
	isThirdPerson = true;
	target = characterPosition;
	thirdPersonOffset = offset;
}

void Camera::disableThirdPerson()
{
	isThirdPerson = false;
	target = nullptr;
}

void Camera::toggleThirdPerson()
{
	isThirdPerson = (isThirdPerson % 3) + 1;
}

void Camera::setFirstPerson() {
	isThirdPerson = 2;
}

void Camera::setThirdPerson() {
	isThirdPerson = 1;

}
Camera::~Camera()
{
}

