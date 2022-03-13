#include "orbitLight.h"

orbitLight::orbitLight()
{
	orbitLocation = glm::vec3(0, 0, 0);
	axis = glm::vec3(0, 1, 0);
	orbitSpeed = 0.5f;
	orbitDistance = 1000.0f;
	currentRotation = 0.0f;
}

orbitLight::orbitLight(glm::vec3 _origin, glm::vec3 _axis, float _speed, float _radius)
{
	orbitLocation = _origin;
	axis = _axis;
	orbitSpeed = _speed;
	orbitDistance = _radius;
	currentRotation = 0.0f;
}


void orbitLight::update(float _deltaTime)
{
	currentRotation += orbitSpeed * _deltaTime;

	glm::mat4 tmpMatrix = glm::mat4(1.0f);
	tmpMatrix = glm::rotate(tmpMatrix, glm::radians(currentRotation), axis);
	tmpMatrix = glm::translate(tmpMatrix, glm::vec3(orbitDistance, 0.0f, 0.0f));
	
	position =  glm::vec4(position,  1.0f) * tmpMatrix;
}

glm::vec3 orbitLight::getPos()
{
	return position;
}