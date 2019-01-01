#pragma once

#include <glm/glm.hpp>
#include "Camera.h"

#include "Cube.h"
#include "Quad.h"

#include <iostream>

Cube singleCube;
Quad quad;

unsigned int framebuffer;
unsigned int texColorBuffer;

class FrameBufferScene
{
public:
	FrameBufferScene()
	{
		singleCube = Cube(glm::vec3(0.0f, 0.0f, 5.0f),1.0f);
		quad = Quad(glm::vec3(0.0f, 0.0f, -10.0f),5.0f,"res\\shaders\\vegShader.vs","res\\shaders\\sharpPostFX.fs");

		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		//Texture Color Buffer Attachement
		glGenTextures(1, &texColorBuffer);
		glBindTexture(GL_TEXTURE_2D, texColorBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		//Attach
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

		//Stencil Depth Renderbuffer Attachement
		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		//Attach
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

		if(glCheckFramebufferStatus(framebuffer) == GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "ERROR::FRAMEBUFFER::NOT_COMPLETE" << std::endl;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Render(Camera& camera)
	{
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 20.0f);

		//First Pass
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		glClearColor(0.4f, 0.8f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);

		singleCube.Draw(view, proj);

		//Second Pass
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glClearColor(0.2f, 0.2f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_STENCIL_TEST);

		glBindTexture(GL_TEXTURE_2D,texColorBuffer);
		quad.Draw(view, proj);
	}
};