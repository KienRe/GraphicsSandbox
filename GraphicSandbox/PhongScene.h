#pragma once

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SDL.h>

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "DirectionalLight.h"
#include "PointLight.h"


float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,  -5.f,  -35.0f),
	glm::vec3(0.0f, -5.f, -5.0f),
	glm::vec3(0.0f,  5.f, -5.0f),
	glm::vec3(0.0f,  5.f, -35.0f)
};

VertexArray vao;

Shader shader;

Texture diffuseTex;
Texture specularTex;

DirectionalLight dirLight;
std::vector<PointLight> pointLights;

class PhongScene
{
public:
	PhongScene()
	{
		//Vertex Array Object / Vertex Buffer Object / Vertex Buffer Layout Setup
		VertexArray vertexArray;
		VertexBuffer vertexBuffer(vertices, sizeof(vertices));
		VertexBufferLayout vertexBufferLayout;

		vertexBufferLayout.Push<float>(3);
		vertexBufferLayout.Push<float>(3);
		vertexBufferLayout.Push<float>(2);

		vertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);

		//Texture Setup
		diffuseTex = Texture("res/textures/container_diffuse.png", GL_RGBA, 0);
		specularTex = Texture("res/textures/container_specular.png", GL_RGBA, 1);

		//Shader Setup
		Shader ourShader("res/shaders/shader.vs", "res/shaders/shader.fs");
		ourShader.use();
		ourShader.setInt("material.diffuse", 0);
		ourShader.setInt("material.specular", 1);

		//Assign members
		vao = vertexArray;
		shader = ourShader;

		//Light Setup
		glm::vec3 lightPos(0.0f, 0.0f, 8.f);
		glm::vec3 lightColor = glm::vec3(1.f, 1.f, 0.94f);

		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

		dirLight = DirectionalLight(lightPos, glm::vec3(0.f, 0.f, -1.f), ambientColor, diffuseColor, glm::vec3(1.0f, 1.0f, 1.0f));

		lightColor = glm::vec3(0.f, 0.f, 0.94f);

		diffuseColor = lightColor * glm::vec3(0.5f);
		ambientColor = diffuseColor * glm::vec3(0.2f);

		for (size_t i = 0; i < 4; i++)
		{
			pointLights.push_back(PointLight(i, pointLightPositions[i], ambientColor, diffuseColor, glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.005f, 0.032f));
		}
	}

	void DrawBoxes(float modleScale, Shader usedShader)
	{
		bool rotateObjects = false;

		//Bind Vertey Array Object
		vao.Bind();

		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4();
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f * i));

			model = glm::scale(model, glm::vec3(modleScale, modleScale, modleScale));
			if (rotateObjects)
			{
				float angle = 20.0f * i * (SDL_GetTicks() / 1000.0f);
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.7f));
			}
			usedShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	void Render(Camera& camera)
	{
		bool dynamicLight = true;

		//Create Transformation Matrixes
		glm::mat4 projection = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);

		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 20.f);
		view = camera.GetViewMatrix();

		//Clear Screen
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//Draw Directional Lights Model
		glm::vec3 lightColor = glm::vec3(1.f, 1.f, 0.94f);
		if (dynamicLight)
		{
			lightColor.x = sin((SDL_GetTicks() / 1000.0f) * 2.0f);
			lightColor.y = sin((SDL_GetTicks() / 1000.0f) * 0.7f);
			lightColor.z = sin((SDL_GetTicks() / 1000.0f) * 1.3f);
		}
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

		dirLight.UpdateLightColor(ambientColor, diffuseColor);
		dirLight.Draw(projection, view, lightColor);

		//Draw PointLights Model
		for each (auto pointLight in pointLights)
		{
			pointLight.UpdateLightColor(ambientColor, diffuseColor);
			pointLight.Draw(projection, view, lightColor);
		}

		//Setup Main Shader
		shader.use();
		//Material Uniforms
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
		shader.setVec3("viewPos", camera.Position);
		shader.setFloat("material.shininess", 32.0f);
		//Light Uniforms
		dirLight.SetUniforms(shader);
		for each (auto pointLight in pointLights)
		{
			pointLight.SetUniforms(shader);
		}
		//Texture Uniforms
		specularTex.Bind();
		diffuseTex.Bind();

		DrawBoxes(1.f, shader);

		glCheckError();
	}
};