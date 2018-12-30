#pragma once

#include <GL/glew.h>
#include "Debug.h"

class VertexBuffer
{

private:
	unsigned int ID;
public:
	VertexBuffer(const void* data, unsigned int size)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

		glCheckError();
	}

	~VertexBuffer()
	{
		//glDeleteBuffers(1, &ID);

		glCheckError();
	}

	void Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);

		glCheckError();
	}

	void Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glCheckError();
	}
};