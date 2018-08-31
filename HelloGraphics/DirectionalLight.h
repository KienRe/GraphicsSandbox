#pragma once

#include <SDL.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "VertexArray.h"

#include "LightModels.h"

class DirectionalLight
{
private:
	glm::vec3 position;
	glm::vec3 dir;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	Shader shader;

	VertexArray vertexArray;
	VertexBufferLayout vertexBufferLayout;

public:
	DirectionalLight(glm::vec3 position,glm::vec3 dir, glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular)
		: position(position),dir(dir), ambient(ambient), diffuse(diffuse), specular(specular)
	{
		VertexBuffer vertexBuffer = VertexBuffer(LigthModel::cubeVertices, sizeof(LigthModel::cubeVertices));
		vertexBufferLayout.Push<float>(3);

		vertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);

		shader = Shader("res/shaders/light.vs", "res/shaders/light.fs");
	}

	DirectionalLight(){}

	void Draw(glm::mat4 projection,glm::mat4 view, glm::vec3 lightModelColor)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f));
		model = glm::translate(model, position);

		//Shader
		shader.use();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
		shader.setMat4("model", model);
		shader.setVec3("LightColor", ambient);

		vertexArray.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glCheckError();
	}

	void SetUniforms(Shader& objectShader)
	{
		objectShader.setVec3("dirLight.direction", dir);
		objectShader.setVec3("dirLight.ambient", ambient);
		objectShader.setVec3("dirLight.diffuse", diffuse);
		objectShader.setVec3("dirLight.specular", specular);
	}

	void UpdateLightColor(glm::vec3 ambientColor, glm::vec3 diffuseColor)
	{
		ambient = ambientColor;
		diffuse = diffuseColor;
	}
};