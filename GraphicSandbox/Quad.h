#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

float transparentVertices[] = {
	// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
	0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
	1.0f,  0.5f,  0.0f,  1.0f,  0.0f
};

class Quad
{
public:
	Quad()
	{

	}

	Quad(glm::vec3 pos,float scale, const GLchar* vsPath, const GLchar* fsPath)
	{
		VertexBuffer vbo(transparentVertices, sizeof(transparentVertices));
		VertexBufferLayout layout;

		layout.Push<float>(3);
		layout.Push<float>(2);

		vao.AddBuffer(vbo, layout);

		shader = Shader(vsPath, fsPath);

		model = glm::mat4();
		model = glm::translate(model, pos);
		model = glm::scale(model, glm::vec3(scale, scale, scale));
	}

	void Draw(glm::mat4 view, glm::mat4 proj)
	{
		vao.Bind();
		shader.use();
		shader.setMat4("view", view);
		shader.setMat4("projection", proj);
		shader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

private:
	Shader shader;
	VertexArray vao;
	glm::mat4 model;
};