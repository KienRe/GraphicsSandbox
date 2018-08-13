#pragma once

#include <GL/glew.h>
#include "Shader.h"
#include "Texture.h"

float vertices[] = {
	// positions          // colors           // texture coords
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,	// top right
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,	// bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

float texCoords[] = {
	0.0f,0.0f,
	1.0f,0.0f,
	0.5f,1.0f
};

unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

unsigned int model;
Shader shader;

class Scene
{
public:
	Scene()
	{
		//Vertex Array Object Setup
		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		//Vertex Buffer Object Setup
		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//Element Buffer Object Setup
		unsigned int EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//Vertex Attributes Setup
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		//Texture Setup
		glActiveTexture(GL_TEXTURE0);
		Texture tex1("res/textures/test1.png", GL_RGB);

		glActiveTexture(GL_TEXTURE1);
		Texture tex2("res/textures/test2.png", GL_RGBA);

		//Shader Setup
		Shader ourShader("res/shaders/shader.vs", "res/shaders/shader.fs");
		ourShader.use();
		ourShader.setInt("texture1", 0);
		ourShader.setInt("texture2", 1);

		model = VBO;
		shader = ourShader;
	}

	void Render()
	{
		//Rendering
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();

		glBindVertexArray(model);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
};