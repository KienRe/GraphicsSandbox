#pragma once

#include <iostream>
#include <GL/glew.h>

#include "stb_image.h"
#include "Debug.h"

class Texture
{
private:
	unsigned int ID;
	int height;
	int width;
	int nrChannels;
	int slot;

public:
	Texture()
	{

	}

	Texture(const char* texturePath, GLenum format, int slot, bool flip)
	{
		this->slot = slot;

		stbi_set_flip_vertically_on_load(flip);
		unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load Texture" << std::endl;
		}

		glCheckError();
	}

	void Bind() const
	{
		switch (this->slot)
		{
		case 0:
			glActiveTexture(GL_TEXTURE0);
			break;
		case 1:
			glActiveTexture(GL_TEXTURE1);
			break;
		case 2:
			glActiveTexture(GL_TEXTURE2);
			break;
		case 3:
			glActiveTexture(GL_TEXTURE3);
			break;
		case 4:
			glActiveTexture(GL_TEXTURE4);
			break;
		case 5:
			glActiveTexture(GL_TEXTURE5);
			break;
		case 6:
			glActiveTexture(GL_TEXTURE6);
			break;
		case 7:
			glActiveTexture(GL_TEXTURE7);
			break;
		case 8:
			glActiveTexture(GL_TEXTURE0);
			break;
		}

		glBindTexture(GL_TEXTURE_2D, ID);

		glCheckError();
	}

	void Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);

		glCheckError();
	}
};
