#pragma once

#include <glm/glm.hpp>

#include "Shader.h"
#include "VertexArray.h"
#include "LightModels.h"

class PointLight
{
private:
	glm::vec3 position;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadtratic;

	Shader shader;

	VertexArray vertexArray;
	VertexBufferLayout vertexBufferLayout;

	int index;


public:
	PointLight(int index,glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadtratic)
		: index(index),position(position), ambient(ambient), diffuse(diffuse), specular(specular), constant(constant), linear(linear), quadtratic(quadtratic)
	{
		VertexBuffer vertexBuffer = VertexBuffer(LigthModel::cubeVertices, sizeof(LigthModel::cubeVertices));
		vertexBufferLayout.Push<float>(3);

		vertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);

		shader = Shader("res/shaders/light.vs", "res/shaders/light.fs");
	}

	PointLight() {}

	void Draw(glm::mat4 projection, glm::mat4 view, glm::vec3 lightModelColor)
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
		objectShader.setVec3("pointLights["+std::to_string(index)+"].position", position);
		objectShader.setVec3("pointLights[" + std::to_string(index) + "].ambient", ambient);
		objectShader.setVec3("pointLights[" + std::to_string(index) + "].diffuse", diffuse);
		objectShader.setVec3("pointLights[" + std::to_string(index) + "].specular", specular);
		objectShader.setFloat("pointLights[" + std::to_string(index) + "].constant", constant);
		objectShader.setFloat("pointLights[" + std::to_string(index) + "].linear", linear);
		objectShader.setFloat("pointLights[" + std::to_string(index) + "].quadtratic", quadtratic);
	}

	void UpdateLightColor(glm::vec3 ambientColor, glm::vec3 diffuseColor)
	{
		ambient = ambientColor;
		diffuse = diffuseColor;
	}
};