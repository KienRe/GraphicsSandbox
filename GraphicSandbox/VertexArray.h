#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <GL/glew.h>
#include "Debug.h"

class VertexArray
{
private:
	unsigned int ID;

public:
	VertexArray()
		: ID(0)
	{
		//glGenVertexArrays(1, &ID);
	}

	~VertexArray()
	{
		//glDeleteVertexArrays(1, &ID);
		//glCheckError();
	}

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{	
		if(ID == 0)
			glGenVertexArrays(1, &ID);

		Bind();
		vb.Bind();

		const auto& elements = layout.GetElements();
		unsigned int offset = 0;

		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];

			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);

			offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
		}

		glCheckError();
	}

	void Bind() const
	{
		glBindVertexArray(ID);

		glCheckError();
	}

	void Unbind() const
	{
		glBindVertexArray(0);

		glCheckError();
	}
};