#pragma once

#include <vector>
#include <map>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

#include "Cube.h"
#include "Quad.h"

Shader vegShader;
VertexArray vegVAO;
Texture grassTexture;
Texture windowTexture;
Cube cube1;

std::vector<glm::vec3> vegetation;

std::map<float, glm::vec3> sorted;

class VegetationScene
{
public:
	VegetationScene()
	{
		VertexBuffer vegVBO(transparentVertices, sizeof(transparentVertices));
		VertexBufferLayout vegLayout;
		vegLayout.Push<float>(3);
		vegLayout.Push<float>(2);
		vegVAO.AddBuffer(vegVBO, vegLayout);

		vegShader = Shader("res\\shaders\\vegShader.vs", "res\\shaders\\vegShader.fs");
		grassTexture = Texture("res\\textures\\grass.png", GL_RGBA, 0, false);
		windowTexture = Texture("res\\textures\\blendWindow.png", GL_RGBA, 0, false);

		vegetation.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
		vegetation.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
		vegetation.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
		vegetation.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
		vegetation.push_back(glm::vec3(0.5f, 0.0f, -0.6f));

		cube1 = Cube(glm::vec3(0.0f, 0.0f, -5.0f), 1);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Render(Camera& camera)
	{
		//Sort Transparent Objects
		for (size_t i = 0; i < vegetation.size(); i++)
		{
			float distance = glm::length(camera.Position - vegetation[i]);
			sorted[distance] = vegetation[i];
		}


		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 20.0f);

		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cube1.Draw(view, proj);

		vegShader.use();
		windowTexture.Bind();
		vegVAO.Bind();

		vegShader.setMat4("view", view);
		vegShader.setMat4("projection", proj);

		for (std::map<float,glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
		{
			glm::mat4 model = glm::mat4();
			model = glm::translate(model, it->second);
			vegShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}
};