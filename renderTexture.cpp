#include "renderTexture.h"
#include "shaderProgram.h"
#include "Scene.h"
#include "texture.h"
#include <iostream>

renderTexture::renderTexture()
{
	glGenFramebuffers(1, &frameBufferId);
	if (!frameBufferId) { throw std::exception(); }
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);

	tex = std::make_shared<texture>(glm::ivec2(512,512));
	renderTextureId = tex->getId();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTextureId, 0);

	glGenRenderbuffers(1, &renderBufferId);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 512,512);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
		GL_RENDERBUFFER, renderBufferId);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	textureSize = glm::ivec2(256,256);
}

renderTexture::renderTexture(glm::ivec2  _size)
{
	glGenFramebuffers(1, &frameBufferId);
	if (!frameBufferId) { throw std::exception(); }
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);

	tex = std::make_shared<texture>(glm::ivec2(_size.x, _size.y));
	renderTextureId = tex->getId();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTextureId, 0);
	
	glGenRenderbuffers(1, &renderBufferId);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _size.x,
		_size.y);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
		GL_RENDERBUFFER, renderBufferId);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	textureSize = _size;
}


void renderTexture::drawToTexture(shaderProgram shader)
{
	//glUseProgram()
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void renderTexture::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
}

void renderTexture::unBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint renderTexture::getTexture()
{
	return renderTextureId;
}