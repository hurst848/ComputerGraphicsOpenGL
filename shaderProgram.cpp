#include "shaderProgram.h"
#include "GL/glew.h"
#include "vertexArray.h"
#include "camera.h"
#include "orbitLight.h"
#include <fstream>
#include <iostream>
#include <vector>

shaderProgram::shaderProgram(std::string _vertexPath, std::string _fragementPath)
{
	const GLchar* vertCode = readShader(_vertexPath);
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertCode, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success) { throw std::exception(); }
	std::cout << "compiled vertex shader" << std::endl;
	
	const GLchar* fragCode = readShader(_fragementPath);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragCode, NULL);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success) { throw std::exception(); }
	std::cout << "compiled fragment shader" << std::endl;
	
	id = glCreateProgram();
	glAttachShader(id, vertexShaderId);
	glAttachShader(id, fragmentShaderId);
	glBindAttribLocation(id, 0, "in_Position");
	glBindAttribLocation(id, 1, "a_texCoords");
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) { throw std::exception(); }
	glDetachShader(id, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(id, fragmentShaderId);
	glDeleteShader(fragmentShaderId);

}

shaderProgram::shaderProgram(SHADERTYPE type)
{
	programType = type;
	
	if (type == SHADER_BASIC)
	{
		const GLchar* vertCode = readShader("Shaders/basicVertexShader.vert");
		GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderId, 1, &vertCode, NULL);
		glCompileShader(vertexShaderId);
		GLint success = 0;
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
		if (!success) { throw std::exception(); }
		std::cout << "compiled vertex shader" << std::endl;

		const GLchar* fragCode = readShader("Shaders/basicFragmentShader.frag");
		GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderId, 1, &fragCode, NULL);
		glCompileShader(fragmentShaderId);
		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
		if (!success) { throw std::exception(); }
		std::cout << "compiled fragment shader" << std::endl;

		id = glCreateProgram();
		glAttachShader(id, vertexShaderId);
		glAttachShader(id, fragmentShaderId);
		glBindAttribLocation(id, 0, "in_Position");
		glBindAttribLocation(id, 1, "a_texCoords");
		glLinkProgram(id);
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success) { throw std::exception(); }
		glDetachShader(id, vertexShaderId);
		glDeleteShader(vertexShaderId);
		glDetachShader(id, fragmentShaderId);
		glDeleteShader(fragmentShaderId);
		
		modelRef = glGetUniformLocation(id, "u_model");
		viewRef = glGetUniformLocation(id, "u_view");
		projRef = glGetUniformLocation(id, "u_projection");
		lightColourRef = NULL;
		ambientStrengthRef = NULL;
		lightPosRef = NULL;
		cameraPosRef = NULL;
	}
	else if (type == SHADER_LIGHT)
	{
		const GLchar* vertCode = readShader("Shaders/lightVertexShader.vert");
		GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderId, 1, &vertCode, NULL);
		glCompileShader(vertexShaderId);
		GLint success = 0;
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
		if (!success) 
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(vertexShaderId, maxLength, &maxLength, &errorLog.at(0));
			std::cout << &errorLog.at(0) << std::endl;
			throw std::exception();
		}
		std::cout << "compiled vertex shader" << std::endl;

		const GLchar* fragCode = readShader("Shaders/lightFragmentShader.frag");
		GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderId, 1, &fragCode, NULL);
		glCompileShader(fragmentShaderId);
		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLint maxLength = 0;
			glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(fragmentShaderId, maxLength, &maxLength, &errorLog.at(0));
			std::cout << &errorLog.at(0) << std::endl;
			throw std::exception(); 
		}
		std::cout << "compiled fragment shader" << std::endl;

		id = glCreateProgram();
		glAttachShader(id, vertexShaderId);
		glAttachShader(id, fragmentShaderId);
		glBindAttribLocation(id, 0, "in_Position");
		glBindAttribLocation(id, 1, "a_texCoords");
		glBindAttribLocation(id, 2, "a_normal");
		glLinkProgram(id);
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success) { throw std::exception(); }
		glDetachShader(id, vertexShaderId);
		glDeleteShader(vertexShaderId);
		glDetachShader(id, fragmentShaderId);
		glDeleteShader(fragmentShaderId);

		modelRef = glGetUniformLocation(id, "u_model");
		viewRef = glGetUniformLocation(id, "u_view");
		projRef = glGetUniformLocation(id, "u_projection");
		lightColourRef = glGetUniformLocation(id, "u_lightColour");
		ambientStrengthRef = glGetUniformLocation(id, "u_ambientStrength");
		lightPosRef = glGetUniformLocation(id, "u_lightPos");
		cameraPosRef = glGetUniformLocation(id, "u_cameraPos");

		lightColour = glm::vec3(1, 1, 1);
		lightPos = glm::vec3(1, 1000, 1);
		ambientStrength = 0.1f;

	}
	else if (type == SHADER_SUPER_BASIC)
	{
		const GLchar* vertCode = readShader("Shaders/superSimpleVertexShader.vert");
		GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderId, 1, &vertCode, NULL);
		glCompileShader(vertexShaderId);
		GLint success = 0;
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
		if (!success) { throw std::exception(); }
		std::cout << "compiled vertex shader" << std::endl;

		const GLchar* fragCode = readShader("Shaders/superSimpleFragmentShader.frag");
		GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderId, 1, &fragCode, NULL);
		glCompileShader(fragmentShaderId);
		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
		if (!success) { throw std::exception(); }
		std::cout << "compiled fragment shader" << std::endl;

		id = glCreateProgram();
		glAttachShader(id, vertexShaderId);
		glAttachShader(id, fragmentShaderId);
		glBindAttribLocation(id, 0, "in_Position");
		glBindAttribLocation(id, 1, "a_texCoords");
		glLinkProgram(id);
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success) { throw std::exception(); }
		glDetachShader(id, vertexShaderId);
		glDeleteShader(vertexShaderId);
		glDetachShader(id, fragmentShaderId);
		glDeleteShader(fragmentShaderId);
	
		modelRef = glGetUniformLocation(id, "u_model");;
		viewRef = glGetUniformLocation(id, "u_view");
		projRef = glGetUniformLocation(id, "u_projection");
		lightColourRef = NULL;
		ambientStrengthRef = NULL;
		lightPosRef = NULL;
		cameraPosRef = NULL;

	}
	else if (type == SHADER_ORTHO)
	{
		const GLchar* vertCode = readShader("Shaders/orthoVertexShader.vert");
		GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderId, 1, &vertCode, NULL);
		glCompileShader(vertexShaderId);
		GLint success = 0;
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
		if (!success) { throw std::exception(); }
		std::cout << "compiled vertex shader" << std::endl;

		const GLchar* fragCode = readShader("Shaders/orthoFragmentShader.frag");
		GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderId, 1, &fragCode, NULL);
		glCompileShader(fragmentShaderId);
		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
		if (!success) { throw std::exception(); }
		std::cout << "compiled fragment shader" << std::endl;

		id = glCreateProgram();
		glAttachShader(id, vertexShaderId);
		glAttachShader(id, fragmentShaderId);
		glBindAttribLocation(id, 0, "in_Position");
		glBindAttribLocation(id, 1, "a_texCoords");
		glLinkProgram(id);
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success) { throw std::exception(); }
		glDetachShader(id, vertexShaderId);
		glDeleteShader(vertexShaderId);
		glDetachShader(id, fragmentShaderId);
		glDeleteShader(fragmentShaderId);

		modelRef = glGetUniformLocation(id, "u_model");
		viewRef = glGetUniformLocation(id, "u_view");
		projRef = glGetUniformLocation(id, "u_projection");
		lightColourRef = NULL;
		ambientStrengthRef = NULL;
		lightPosRef = NULL;
		cameraPosRef = NULL;

	}
	else
	{
		throw std::exception();
	}
}

void shaderProgram::update(glm::mat4 _proj, glm::mat4 _view, glm::mat4 _model, vertexArray &vaoID, GLuint texID)
{
	glUseProgram(id);
	glBindVertexArray(vaoID.getId());
	glBindTexture(GL_TEXTURE_2D, texID);

	if (programType == SHADER_BASIC)
	{
		glUniformMatrix4fv(modelRef, 1, GL_FALSE, glm::value_ptr(_model));
		glUniformMatrix4fv(projRef, 1, GL_FALSE, glm::value_ptr(_proj));
		glUniformMatrix4fv(viewRef, 1, GL_FALSE, glm::value_ptr(glm::inverse(_view)));
		glUniform1i(texID, 1);
	}
	else if (programType == SHADER_LIGHT)
	{
		cameraPos = glm::vec3(_view * glm::vec4(0,0,0,1));
		glUniformMatrix4fv(modelRef, 1, GL_FALSE, glm::value_ptr(_model));
		glUniformMatrix4fv(projRef, 1, GL_FALSE, glm::value_ptr(_proj));
		glUniformMatrix4fv(viewRef, 1, GL_FALSE, glm::value_ptr(glm::inverse(_view)));
		glUniform1i(texID, 1);

		glUniform3fv(lightColourRef, 1, glm::value_ptr(lightColour));
		glUniform3fv(lightPosRef, 1, glm::value_ptr(lightPos));
		glUniform3fv(cameraPosRef, 1, glm::value_ptr(cameraPos));
		glUniform1f(ambientStrengthRef, ambientStrength);

	}
	else if (programType == SHADER_SUPER_BASIC)
	{
		glUniformMatrix4fv(modelRef, 1, GL_FALSE, glm::value_ptr(_model));
		glUniformMatrix4fv(projRef, 1, GL_FALSE, glm::value_ptr(_proj));
		glUniformMatrix4fv(viewRef, 1, GL_FALSE, glm::value_ptr(glm::inverse(_view)));
	}
	else if (programType == SHADER_ORTHO)
	{
		glUniformMatrix4fv(modelRef, 1, GL_FALSE, glm::value_ptr(_model));
		glUniformMatrix4fv(projRef, 1, GL_FALSE, glm::value_ptr(_proj));
		glUniformMatrix4fv(viewRef, 1, GL_FALSE, glm::value_ptr(glm::inverse(_view)));
		glUniform1i(texID, 1);
	}

	glEnable(GL_CULL_FACE);
	glDrawArrays(GL_TRIANGLES, 0, vaoID.getVertCount());
	glDisable(GL_CULL_FACE);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void shaderProgram::update(glm::mat4 _proj, glm::mat4 _view, glm::mat4 _model, std::shared_ptr<vertexArray> vaoID, GLuint texID)
{
	glUseProgram(id);
	glBindVertexArray(vaoID->getId());
	glBindTexture(GL_TEXTURE_2D, texID);

	if (programType == SHADER_BASIC)
	{
		glUniformMatrix4fv(modelRef, 1, GL_FALSE, glm::value_ptr(_model));
		glUniformMatrix4fv(projRef, 1, GL_FALSE, glm::value_ptr(_proj));
		glUniformMatrix4fv(viewRef, 1, GL_FALSE, glm::value_ptr(glm::inverse(_view)));
		glUniform1i(texID, 1);
	}
	else if (programType == SHADER_LIGHT)
	{
		cameraPos = glm::vec3(_view * glm::vec4(0, 0, 0, 1));
		glUniformMatrix4fv(modelRef, 1, GL_FALSE, glm::value_ptr(_model));
		glUniformMatrix4fv(projRef, 1, GL_FALSE, glm::value_ptr(_proj));
		glUniformMatrix4fv(viewRef, 1, GL_FALSE, glm::value_ptr(glm::inverse(_view)));
		glUniform1i(texID, 1);

		glUniform3fv(lightColourRef, 1, glm::value_ptr(lightColour));
		glUniform3fv(lightPosRef, 1, glm::value_ptr(lightPos));
		glUniform3fv(cameraPosRef, 1, glm::value_ptr(cameraPos));
		glUniform1f(ambientStrengthRef, ambientStrength);

	}
	else if (programType == SHADER_SUPER_BASIC)
	{
		glUniformMatrix4fv(modelRef, 1, GL_FALSE, glm::value_ptr(_model));
		glUniformMatrix4fv(projRef, 1, GL_FALSE, glm::value_ptr(_proj));
		glUniformMatrix4fv(viewRef, 1, GL_FALSE, glm::value_ptr(glm::inverse(_view)));
	}
	else if (programType == SHADER_ORTHO)
	{
		glUniformMatrix4fv(modelRef, 1, GL_FALSE, glm::value_ptr(_model));
		glUniformMatrix4fv(projRef, 1, GL_FALSE, glm::value_ptr(_proj));
		glUniformMatrix4fv(viewRef, 1, GL_FALSE, glm::value_ptr(glm::inverse(_view)));
		glUniform1i(texID, 1);
	}

	glEnable(GL_CULL_FACE);
	glDrawArrays(GL_TRIANGLES, 0, vaoID->getVertCount());
	glDisable(GL_CULL_FACE);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}


void shaderProgram::update(glm::mat4 _proj, std::shared_ptr<camera> _camera, glm::mat4 _model, vertexArray& vaoID, GLuint texID)
{
	glUseProgram(id);
	glBindVertexArray(vaoID.getId());
	glBindTexture(GL_TEXTURE_2D, texID);

	if (programType == SHADER_BASIC)
	{
		glUniformMatrix4fv(modelRef, 1, GL_FALSE, glm::value_ptr(_model));
		glUniformMatrix4fv(projRef, 1, GL_FALSE, glm::value_ptr(_proj));
		glUniformMatrix4fv(viewRef, 1, GL_FALSE, glm::value_ptr(glm::inverse(_camera->getMatrix())));
		glUniform1i(texID, 1);
	}
	else if (programType == SHADER_LIGHT)
	{
		cameraPos = glm::vec3(_camera->getMatrix() * glm::vec4(0, 0, 0, 1));
		glUniformMatrix4fv(modelRef, 1, GL_FALSE, glm::value_ptr(_model));
		glUniformMatrix4fv(projRef, 1, GL_FALSE, glm::value_ptr(_proj));
		glUniformMatrix4fv(viewRef, 1, GL_FALSE, glm::value_ptr(glm::inverse(_camera->getMatrix())));
		glUniform1i(texID, 1);

		glUniform3fv(lightColourRef, 1, glm::value_ptr(lightColour));
		glUniform3fv(lightPosRef, 1, glm::value_ptr(lightPos));
		glUniform3fv(cameraPosRef, 1, glm::value_ptr(cameraPos));
		glUniform1f(ambientStrengthRef, ambientStrength);

	}
	else if (programType = SHADER_ORTHO)
	{
		glUniformMatrix4fv(modelRef, 1, GL_FALSE, glm::value_ptr(_model));
		glUniformMatrix4fv(projRef, 1, GL_FALSE, glm::value_ptr(_proj));
		glUniformMatrix4fv(viewRef, 1, GL_FALSE, glm::value_ptr(glm::inverse(_camera->getMatrix())));
		glUniform1i(texID, 1);
	}

	glEnable(GL_CULL_FACE);
	glDrawArrays(GL_TRIANGLES, 0, vaoID.getVertCount());
	glDisable(GL_CULL_FACE);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void shaderProgram::update(glm::mat4 _proj, glm::mat4 _view, glm::mat4 _model, std::shared_ptr<vertexArray> vaoID, GLuint texID, std::shared_ptr<orbitLight> light)
{
	lightPos = light->getPos();
	cameraPos = glm::vec3(_view * glm::vec4(0, 0, 0, 1));
	glUniformMatrix4fv(modelRef, 1, GL_FALSE, glm::value_ptr(_model));
	glUniformMatrix4fv(projRef, 1, GL_FALSE, glm::value_ptr(_proj));
	glUniformMatrix4fv(viewRef, 1, GL_FALSE, glm::value_ptr(glm::inverse(_view)));
	glUniform1i(texID, 1);

	glUniform3fv(lightColourRef, 1, glm::value_ptr(lightColour));
	glUniform3fv(lightPosRef, 1, glm::value_ptr(lightPos));
	glUniform3fv(cameraPosRef, 1, glm::value_ptr(cameraPos));
	glUniform1f(ambientStrengthRef, ambientStrength);
}


void shaderProgram::update(glm::mat4 _proj, std::shared_ptr<vertexArray> vaoId, GLuint texId)
{
	glUseProgram(id);
	glBindVertexArray(vaoId->getId());
	glBindTexture(GL_TEXTURE_2D, texId);
}


const GLchar* shaderProgram::readShader(std::string _path)
{
	inputBuffer = "";
	std::string line = "";
	std::ifstream vis(_path);
	for (int i = 0; std::getline(vis, line); i++)
	{
		inputBuffer += line;
	}
	return inputBuffer.c_str();
}

GLuint shaderProgram::getId()
{
	return id;
}