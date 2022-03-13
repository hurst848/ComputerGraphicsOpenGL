#include "vertexBuffer.h"

vertexBuffer::vertexBuffer()
{
	glGenBuffers(1, &id);
	if (!id) { throw std::exception(); }
	dirty = true;
	components = -1;
}

vertexBuffer::~vertexBuffer()
{
	glDeleteBuffers(1, &id);
}



void vertexBuffer::addData(glm::vec2 _value)
{
	if (components == -1) { components = 2; }
	else if (components != 2) { throw std::exception(); }

	data.push_back(_value.x);
	data.push_back(_value.y);
	dirty = true;
}

void vertexBuffer::addData(glm::vec3 _value)
{
	if (components == -1) { components = 3; }
	else if (components != 3) { throw std::exception(); }

	data.push_back(_value.x);
	data.push_back(_value.y);
	data.push_back(_value.z);
	dirty = true;
}

void vertexBuffer::addData(glm::vec4 _value)
{
	if (components == -1) { components = 4; }
	else if (components != 4) { throw std::exception(); }

	data.push_back(_value.x);
	data.push_back(_value.y);
	data.push_back(_value.z);
	data.push_back(_value.w);
	dirty = true;
}

int vertexBuffer::getComponents()
{
	return components;
}

GLuint vertexBuffer::getId()
{
	if (dirty)
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data.at(0)), &data.at(0), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		dirty = false;
	}
	return id;
}