#include "glm/ext.hpp"



struct orbitLight
{
public:
	orbitLight();
	orbitLight(glm::vec3 _origin, glm::vec3 _axis, float _speed, float _radius);
	~orbitLight(){}

	void update(float _deltaTime);
	glm::vec3 getPos();
	
private:
	glm::vec3 orbitLocation;
	glm::vec3 axis;
	glm::vec3 position;
	float orbitSpeed;
	float orbitDistance;
	float currentRotation;
};
