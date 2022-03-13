#include "glm/ext.hpp"

struct Transform
{
public:
	Transform()
	{
		position = glm::vec3(0.0f, 0.0f, 0.0f);
		rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		scale = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};