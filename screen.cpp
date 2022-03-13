#include "screen.h"

#include "vertexBuffer.h"
#include "vertexArray.h"
#include "shaderProgram.h"
#include "texture.h"

#include <vector>

screen::screen()
{
	std::vector<glm::vec3> points =
	{
		glm::vec3(1.0f,1.0f,0.0f),
		glm::vec3(0.0f,1.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,1.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,0.0f,0.0f)		
	};
	std::vector<glm::vec2> texCoords =
	{
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),

	};

	vertBuffer = std::make_shared<vertexBuffer>();
	texCoord = std::make_shared<vertexBuffer>();
	for (int i = 0; i < points.size(); i++)
	{
		texCoord->addData(texCoords.at(i));
		vertBuffer->addData(points.at(i));
	}

	
	

	vao = std::make_shared<vertexArray>();
	vao->setBuffer(0, vertBuffer);
	vao->setBuffer(1, texCoord);
	vao->setVertCount(6);

	program = std::make_shared<shaderProgram>(shaderProgram::SHADERTYPE::SHADER_ORTHO);

	/*projectionMatrix = glm::ortho(0.0f, (float)1920, 0.0f, (float)1080, 0.0f, 1.0f);

	modelMatrix = glm::mat4(1.0);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(1920 / 2, 1080 / 2, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(100, 100, 0));*/

	
	//currentTexture = 0;
}

screen::screen(glm::ivec2 _size)
{
	
}

void screen::update(GLuint _tex)
{
	currentTexture = _tex;
}

void screen::draw(glm::mat4 _view)
{
	//projectionMatrix = glm::perspective(glm::radians(60.0f), ((1.0f * 1920) / (1.0f * 1080)), 0.1f, 1000.0f);
	projectionMatrix = glm::ortho(0.0f, (float)1920, 0.0f, (float)1080, 0.0f, 1.0f);
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(100, 100, 0));
	
	program->update(projectionMatrix, glm::mat4(1.0f), modelMatrix, *vao, currentTexture);
}