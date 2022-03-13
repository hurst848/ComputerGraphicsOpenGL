#include "glm/ext.hpp"
#include "glm/gtx/quaternion.hpp"
struct input;

struct camera
{
public:
	float cameraSpeed = 0.1f;
	float mouseSensitivity = 0.03f;
	glm::mat4 getMatrix();
	void processInputs(input inp);
	void setTransform(glm::vec3 _position, glm::vec3 _rotation);
	
private:
	glm::vec3 position = glm::vec3(0,0,0);
	glm::vec3 front = glm::vec3(0,0,-1);
	glm::vec3 right = glm::vec3(1,0,0);
	glm::vec3 up = glm::vec3(0, 1, 0);
	float yaw = -90.0f;
	float pitch = 0.0f;
	float roll = 0.0f;

};