#include "glm/ext.hpp"
#include "GL/glew.h"

#include <memory>

struct vertexBuffer;
struct vertexArray;
struct texture;
struct shaderProgram;

struct screen
{
public:
	screen();
	
	screen(glm::ivec2 _size);

	void update(GLuint _tex);
	void draw(glm::mat4 _view);

private:
	GLuint currentTexture;
	
	std::shared_ptr<vertexBuffer> vertBuffer;
	std::shared_ptr<vertexBuffer> texCoord;
	std::shared_ptr<vertexArray> vao;
	std::shared_ptr<shaderProgram> program;

	glm::ivec2 screenSize;

	glm::mat4 projectionMatrix;
	glm::mat4 modelMatrix;
};
