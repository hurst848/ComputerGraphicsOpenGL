#include "Plane.h"

#include "vertexArray.h"
#include "texture.h"
#include "shaderProgram.h"
#include "Propellor.h"
#include "camera.h"
#include "input.h"
#include "orbitLight.h"

#include "GL/glew.h"
#include "glm/ext.hpp"
#include "SDL2/SDL.h"

#include <iostream>


Plane::Plane()
{
	model = std::make_shared<vertexArray>("Models/plane/plane.obj");
	modelTexture = std::make_shared<texture>("Models/plane/plane.png");
	program = std::make_shared<shaderProgram>(shaderProgram::SHADERTYPE::SHADER_LIGHT);
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	projection = glm::perspective(glm::radians(60.0f), ((1.0f * 1920) / (1.0f * 1080)), 0.1f, 1000.0f);

	propellor = std::make_shared<Propellor>();

	cockpitCamera = std::make_shared<camera>();
	rearCamera = std::make_shared<camera>();
	
	throttle = 0.5f;
	viewMatrix = cockpitCamera->getMatrix();
} 
void Plane::draw(std::shared_ptr<orbitLight> _light, float _deltaTime,int currentCamera)
{
	if (currentCamera == 0)
	{
		program->update(projection, cockpitCamera->getMatrix(), modelMatrix, model, modelTexture->getId());
	}
	else
	{
		program->update(projection, rearCamera->getMatrix(), modelMatrix, model, modelTexture->getId());
	}
	
	//program->update(projection, cockpitCamera->getMatrix(), modelMatrix, model, modelTexture->getId(), _light);
	propellor->draw(_light);
}
void Plane::update(glm::vec3 _translation, glm::vec3 _rotation, glm::mat4 _viewMatrix)
{
	modelMatrix = glm::mat4(1.0f);
	position += _translation;
	rotation += _rotation;

	modelMatrix = glm::translate(modelMatrix, position);

	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(0, 1, 0));

	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(1, 0, 0));

	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	
	front = glm::vec3(modelMatrix * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));
	right = glm::vec3(modelMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	up = glm::vec3(modelMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

	viewMatrix = _viewMatrix;

	glm::vec3 propTransform = front + 2.6f;
	propellor->update(front, _rotation, _viewMatrix);

	
	
}
void Plane::update(input inp, glm::mat4 _viewMatrix, float deltaTime)
{
	

	float mouseSensitivity = 0.6f;
	float xoff = -inp.getMouseDelta().x * mouseSensitivity * deltaTime;
	float yoff = -inp.getMouseDelta().y * mouseSensitivity * deltaTime;
	float zoff = 0.0f;
	if (inp.getKey_e()) { zoff -= 40.0f * mouseSensitivity * deltaTime; }
	if (inp.getKey_q()) { zoff += 40.0f * mouseSensitivity * deltaTime; }

	rotation.x += xoff;// yaw	
	rotation.z += yoff;// pitch
	rotation.y += zoff;// roll

	glm::mat4 Model(1.0f);

	Model = glm::rotate(Model, glm::radians(rotation.x), glm::vec3(0, 1, 0));

	Model = glm::rotate(Model, glm::radians(rotation.y), glm::vec3(1, 0, 0));

	Model = glm::rotate(Model, glm::radians(rotation.z), glm::vec3(0, 0, 1));

	front = glm::vec3(Model * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));
	right = glm::vec3(Model * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	up    = glm::vec3(Model * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

	if (inp.getKey_w() && throttle <= 1.0f)
	{
		throttle += 0.1f * deltaTime;
		//position += -(right * 1.0f) * deltaTime;
	}
	if (inp.getKey_s() && throttle >= 0.0f)
	{
		throttle -= 0.1f * deltaTime;
		//position += right * 1.0f * deltaTime;
	}

	if (throttle < 0.1f)
	{
		position -= (9.8f * up * deltaTime);
	}
	
	
	float currentSpeed = minSpeed + ((throttle / 1.0f) * (maxSpeed - minSpeed));
	position += -(right * currentSpeed) * deltaTime;

	modelMatrix = glm::mat4(1.0f);
	

	modelMatrix = glm::translate(modelMatrix, position);

	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(0, 1, 0));

	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(1, 0, 0));

	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));

	glm::vec3 propTransform = position + (glm::normalize(right) * 2.6f);
	//propellor->update(propTransform, rotation, _viewMatrix);
	propellor->setTransform(propTransform, rotation, _viewMatrix, throttle);
	
	glm::vec3 cockpitCameraPosition = position + (glm::normalize(up) * 2.0f) + (glm::normalize(right) * -2.4f);
	glm::vec3 cockpitRotation = glm::vec3(rotation.x +90, -rotation.z, rotation.y);// +glm::vec3(0, 0, 90);
	cockpitCamera->setTransform(cockpitCameraPosition, cockpitRotation);

	glm::vec3 rearCameraPosition = position + (glm::normalize(up) * 5.0f) + (glm::normalize(right) * 15.0f);
	glm::vec3 rearCameraRotation = glm::vec3(rotation.x + 90, -rotation.z, rotation.y);// rotation.x);
	rearCamera->setTransform(rearCameraPosition, rearCameraRotation);

	viewMatrix = _viewMatrix;
	
}