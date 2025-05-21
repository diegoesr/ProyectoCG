#pragma once

#include <glew.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include <glfw3.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);
	int isThirdPerson = 1;  // Modos de vista
	int atraccion = 0;
	float getYaw();
	glm::vec3 getCameraPosition();
	glm::vec3 getCameraDirection();
	glm::mat4 calculateViewMatrix();
	glm::vec3 getCameraFront();
	glm::vec3 getCameraRight();
	glm::vec3 getCameraUp();

	void toggleThirdPerson();
	void setFirstPerson();
	void setThirdPerson();
	void enableThirdPerson(glm::vec3* characterPosition, glm::vec3 offset);
	void disableThirdPerson();

	~Camera();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	glm::vec3* target = nullptr; // Puntero a la posición del personaje
	glm::vec3 thirdPersonOffset = glm::vec3(0.0f, 50.0f, 15.0f); // Altura y distancia

	GLfloat yaw;
	GLfloat pitch;

	GLfloat moveSpeed;
	GLfloat turnSpeed;

	void update();
};

