#include "Propellor.h"

#include "vertexArray.h"
#include "shaderProgram.h"
#include "texture.h"

Propellor::Propellor()
{
	model = std::make_shared<vertexArray>("Models/prop/prop.obj");
	modelTexture = std::make_shared<texture>("Models/prop/prop.png");
	program = std::make_shared<shaderProgram>(shaderProgram::SHADERTYPE::SHADER_LIGHT);

	position = glm::vec3(2.6f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	projection = glm::perspective(glm::radians(60.0f), ((1.0f * 1920) / (1.0f * 1080)), 0.1f, 1000.0f);
}
void Propellor::draw(std::shared_ptr<orbitLight> _light)
{
	glUseProgram(program->getId());

	glBindVertexArray(model->getId());

	program->update(projection, viewMatrix, modelMatrix, model, modelTexture->getId());
	//program->update(projection, viewMatrix, modelMatrix, model, modelTexture->getId(), _light);
}

void Propellor::update(glm::vec3 _translation, glm::vec3 _rotation, glm::mat4 _viewMatrix)
{
	modelMatrix = glm::mat4(1.0f);
	position += _translation;
	rotation += _rotation;
	//rotation.y += 10;
	
	

	

	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(0, 1, 0));

	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(1, 0, 0));

	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z + spinFactor), glm::vec3(0, 0, 1));

	
	modelMatrix = glm::translate(modelMatrix, position);

	//modelMatrix = glm::lookAt(position, position + _translation, glm::vec3(0, 1, 0));

	



	viewMatrix = _viewMatrix;
}

void Propellor::setTransform(glm::vec3 _position, glm::vec3 _rotation, glm::mat4 _viewMatrix, float throttle)
{
	modelMatrix = glm::mat4(1.0f);
	spinFactor += 0.25f * throttle;
	

	position = _position;
	rotation = _rotation;

	modelMatrix = glm::translate(modelMatrix, position);

	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(0, 1, 0));

	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(1, 0, 0));

	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));

	modelMatrix = glm::rotate(modelMatrix, spinFactor, glm::vec3(1,0,0));

	
	


	viewMatrix = _viewMatrix;
	//rotation += _ro;
}