#pragma once

#include <glm/glm.hpp>
#include "Camera.h"
#include "Cube.h"

Cube cube;

class CullScene
{
public:
	CullScene()
	{
		cube = Cube(glm::vec3(0.0f, 0.0f, -5.0f), 1);
	}


	void Render(Camera& camera)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);

		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 20.0f);

		cube.Draw(view, proj);
	}
};