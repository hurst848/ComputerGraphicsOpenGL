#include <GL/glew.h>
#include <glm/ext.hpp>
#include <stb_image/stb_image.h>

#include <string>

struct texture
{

public:
	texture();
	texture(glm::ivec2 _size);
	texture(std::string _path);
	glm::ivec2 getSize();
	GLuint getId();
private:
	GLuint id;
	glm::ivec2 textureSize;
};