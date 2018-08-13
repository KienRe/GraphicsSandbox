#pragma once

#include <iostream>
#include <GL/glew.h>

#include "stb_image.h"

class Texture
{
private:
	unsigned int ID;
	int height;
	int width;
	int nrChannels;

public:
	Texture(const char* texturePath, GLenum format)
	{
		stbi_set_flip_vertically_on_load(true);
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
	}

	void Bind()
	{
		glBindBuffer(GL_TEXTURE_2D, ID);
	}

	void Unbind()
	{
		glBindBuffer(GL_TEXTURE_2D, 0);
	}
};
