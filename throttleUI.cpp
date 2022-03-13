#include "throttleUI.h"

#include"vertexBuffer.h"
#include "vertexArray.h"
#include "texture.h"
#include "shaderProgram.h"

#include <iostream>

throttleUI::throttleUI()
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
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),

		
	};

	bodyVertBuffer = std::make_shared<vertexBuffer>();
	bodyTexBuffer = std::make_shared<vertexBuffer>();
	headVertBuffer = std::make_shared<vertexBuffer>();
	headTexBuffer = std::make_shared<vertexBuffer>();

	for (int i = 0; i < points.size(); i++)
	{
		bodyVertBuffer->addData(points.at(i));
		bodyTexBuffer->addData(texCoords.at(i));

		headVertBuffer->addData(points.at(i));
		headTexBuffer->addData(texCoords.at(i));
	}

	bodyVAO = std::make_shared<vertexArray>();
	bodyVAO->setBuffer(0, bodyVertBuffer);
	bodyVAO->setBuffer(1, bodyTexBuffer);
	bodyVAO->setVertCount(6);

	headVAO = std::make_shared<vertexArray>();
	headVAO->setBuffer(0, headVertBuffer);
	headVAO->setBuffer(1, headTexBuffer);
	headVAO->setVertCount(6);

	program = std::make_shared<shaderProgram>(shaderProgram::SHADER_ORTHO);

	bodyTexture = std::make_shared<texture>("Models/throttle/throttleBase.png");
	headTexture = std::make_shared<texture>("Models/throttle/throttleHead.png");

	bodyModelMatrix = glm::mat4(1.0f);
	bodyModelMatrix = glm::translate(bodyModelMatrix, glm::vec3(0, 0, 0));
	bodyModelMatrix = glm::scale(bodyModelMatrix, glm::vec3(200, 400, 0));
	//bodyModelMatrix = glm::rotate(bodyModelMatrix, glm::radians(180.0f), glm::vec3(0, 0, 1));

	/*headModelMatrix = glm::mat4(1.0f);
	headModelMatrix = glm::translate(headModelMatrix, glm::vec3(25, 0, 0));
	headModelMatrix = glm::scale(headModelMatrix, glm::vec3(100, 50, 0));*/

	projectionMatrix = projectionMatrix = glm::ortho(0.0f, (float)1920, 0.0f, (float)1080, 0.0f, 1.0f);

}

void throttleUI::update(float _throttleValue)
{
	float maxUp = 325;
	float actualThrottleLoc = maxUp * _throttleValue;
	std::cout << actualThrottleLoc << std::endl;
	headModelMatrix = glm::mat4(1.0f);
	headModelMatrix = glm::translate(headModelMatrix, glm::vec3(25, actualThrottleLoc, 0));
	headModelMatrix = glm::scale(headModelMatrix, glm::vec3(100, 50, 0));


	program->update(projectionMatrix, glm::mat4(1.0f), headModelMatrix, headVAO, headTexture->getId());
	program->update(projectionMatrix, glm::mat4(1.0f), bodyModelMatrix, bodyVAO, bodyTexture->getId());
	
}