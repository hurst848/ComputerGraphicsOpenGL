#include <memory>

#include "glm/ext.hpp"

struct vertexBuffer;
struct vertexArray;
struct texture;
struct shaderProgram;

struct throttleUI
{
public:
	throttleUI();
	~throttleUI() {};

	void update(float _throttleValue);

private:
	float currentThrottle = 0.0f;

	// body of throttle
	std::shared_ptr<vertexBuffer> bodyVertBuffer;
	std::shared_ptr<vertexBuffer> bodyTexBuffer;
	std::shared_ptr<vertexArray> bodyVAO;
	std::shared_ptr<texture> bodyTexture;
	glm::mat4 bodyModelMatrix;

	// head of throttle
	std::shared_ptr<vertexBuffer> headVertBuffer;
	std::shared_ptr<vertexBuffer> headTexBuffer;
	std::shared_ptr<vertexArray> headVAO;
	std::shared_ptr<texture> headTexture;
	glm::mat4 headModelMatrix;

	// shared attributes
	std::shared_ptr<shaderProgram> program;
	glm::mat4 projectionMatrix;
};
