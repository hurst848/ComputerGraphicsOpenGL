#include "vertexArray.h"

#include <bugl/bugl.h>
#include "vertexBuffer.h"


vertexArray::vertexArray()
{
	glGenVertexArrays(1, &id);
	if (!id) { throw std::exception(); }
	dirty = true;
	buffers.resize(20);
}

vertexArray::vertexArray(std::string _path)
{
	id = buLoadModel(_path, &vertCount);
	dirty = false;

}

size_t vertexArray::getVertCount()
{
	return vertCount;
}


vertexArray::~vertexArray()
{
	glDeleteVertexArrays(1, &id);
}

void vertexArray::setBuffer(GLuint _index, std::shared_ptr<vertexBuffer> _buffer)
{
	buffers.at(_index) = _buffer;
	dirty = true;
}

GLuint vertexArray::getId()
{
	if (dirty)
	{
		glBindVertexArray(id);
		for (size_t i = 0; i < buffers.size(); i++)
		{
			if (buffers.at(i) == NULL) { break; }
			glBindBuffer(GL_ARRAY_BUFFER, buffers.at(i)->getId());
			glVertexAttribPointer(i,buffers.at(i)->getComponents(), 
				GL_FLOAT,GL_FALSE,0,(void*)0);
			glEnableVertexAttribArray(i);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		glBindVertexArray(0);
		dirty = false;
	}
	return id;
}

void vertexArray::setVertCount(int _size)
{
	vertCount = _size;
}