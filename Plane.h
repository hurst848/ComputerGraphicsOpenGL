#include "glm/ext.hpp"
#include <memory>

struct Propellor;
struct texture;
struct shaderProgram;
struct vertexArray;
struct camera;
struct input;
struct orbitLight;

struct Plane
{
public:
	Plane();
	void draw(std::shared_ptr<orbitLight> _light, float _deltaTime,int currentCamera);
	void update(glm::vec3 _translation, glm::vec3 _rotation, glm::mat4 _viewMatrix);
	void update(input inp, glm::mat4 _viewMatrix, float deltaTime);
	
	std::shared_ptr<camera> cockpitCamera;
	std::shared_ptr<camera> rearCamera;

	glm::vec3 front;
	glm::vec3 right; 
	glm::vec3 up;

	float throttle = 0.0f;

private:
	float maxSpeed = 250.0f;
	float minSpeed = 0.0f;


	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;

	glm::mat4 projection;
	glm::mat4 view;

	glm::vec3 position;
	glm::vec3 rotation;

	std::shared_ptr<vertexArray> model;
	std::shared_ptr<texture> modelTexture;
	std::shared_ptr<shaderProgram> program;

	std::shared_ptr<Propellor> propellor;
};
