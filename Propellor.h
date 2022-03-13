#include "glm/ext.hpp"

#include <memory>

struct vertexArray;
struct texture;
struct shaderProgram;
struct orbitLight;

struct  Propellor
{
public:
	Propellor();
	void draw(std::shared_ptr<orbitLight> _light);
	void update(glm::vec3 _translation, glm::vec3 _rotation, glm::mat4 _viewMatrix);
	void setTransform(glm::vec3 _position, glm::vec3 _rotation, glm::mat4 _viewMatrix, float throttle);
private:
	float spinFactor = 0.0f;
	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;

	glm::mat4 projection;
	glm::mat4 view;

	glm::vec3 position;
	glm::vec3 rotation;

	std::shared_ptr<vertexArray> model;
	std::shared_ptr<texture> modelTexture;
	std::shared_ptr<shaderProgram> program;
};
