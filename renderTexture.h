#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "glm/ext.hpp"

#include <memory>
struct shaderProgram;
struct Scene;
struct texture;

struct renderTexture
{
public:
	renderTexture();
	renderTexture(glm::ivec2 _size);

	void bind();
	void unBind();

	GLuint getTexture();

	void drawToTexture(shaderProgram object);
	glm::ivec2 textureSize;
private:
	std::shared_ptr<texture> tex;
	GLuint renderTextureId;
	GLuint frameBufferId;
	GLuint renderBufferId;
	SDL_Window *window;
	
	
};