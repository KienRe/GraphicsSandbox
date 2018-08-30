#pragma once

#include <iostream>

#include <SDL.h>
#include <GL/glew.h>

//#include <imgui.h>
//#include "imgui_impl_sdl_gl3.h"

#include "Camera.h"
#include "Scene.h"

class Renderer
{
private:
	SDL_GLContext glContext;
	SDL_Window* window;

public:
	bool drawWireframe = false;

public:
	Renderer(SDL_Window* window)
	{
		this->window = window;

		//OPENGL INIT
		glContext = SDL_GL_CreateContext(window);

		//GLEW INIT
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Glew Init failed!";
		}
		else
		{
			std::cout << "Glew initalized succesfully! \nVideo Driver Version: " << glGetString(GL_VERSION) << "\n";
		}

		//OPENGL CONFIGURATION
		glEnable(GL_DEPTH_TEST);
		glGetError();	//OpenGL starts with an error in the queue, we need to discard that else we cause confusion!

		//IMGUI INIT
		ImGui_ImplSdlGL3_Init(window);
		ImGui::StyleColorsClassic();
	}

	~Renderer()
	{
		SDL_GL_DeleteContext(glContext);
	}

	void ImguiFrame()
	{
		ImGui_ImplSdlGL3_NewFrame(window);

		ImGui::BeginMainMenuBar();

		if (ImGui::BeginMenu("Rendering"))
		{
			ImGui::MenuItem("Wireframe Mode", "", &drawWireframe, true);
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();


		// 1. Show a simple window.
		// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
		{
			//static float f = 0.0f;
			//ImGui::SliderFloat3("V1", v1, -1, 1, "%.1f");
			//ImGui::SliderFloat3("V2", v2, -1, 1, "%.1f");
			//ImGui::SliderFloat3("V3", v3, -1, 1, "%.1f");
			//ImGui::Text("Hello, world!");                           // Some text (you can use a format string too)
			//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float as a slider from 0.0f to 1.0f
			//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats as a color
			//if (ImGui::Button("Demo Window"))                       // Use buttons to toggle our bools. We could use Checkbox() as well.
			//	show_demo_window ^= 1;
			//if (ImGui::Button("Another Window"))
			//	show_another_window ^= 1;
			//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}

		//// 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name the window.
		//if (show_another_window)
		//{
		//	ImGui::Begin("Another Window", &show_another_window);
		//	ImGui::Text("Hello from another window!");
		//	ImGui::End();
		//}

		//// 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow().
		//if (show_demo_window)
		//{
		//	ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
		//	ImGui::ShowDemoWindow(&show_demo_window);
		//}
	}

	void RenderScene(Scene& scene)
	{
		scene.Render();

		//Imgui Frame
		{
			ImguiFrame();
		}

		//Debug Rendering Options
		if (drawWireframe)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		ImGui::Render();
	}

	//void Renderer::render_scene(const Camera &camera,
	//	const Scene &scene,
	//	const glm::ivec2 &resolution) {
	//	glViewport(0, 0, resolution.x, resolution.y);
	//	glUseProgram(standard_program_.program);
	//	glUniform1i(standard_program_.brdf_lut, 0);
	//	glUniform1i(standard_program_.shadow_maps[0], 1);
	//	glUniform1i(standard_program_.shadow_maps[1], 2);
	//	glUniform1i(standard_program_.environment_maps[0].map, 3);
	//	glUniform1i(standard_program_.environment_maps[1].map, 4);

	//	glUniform1i(standard_program_.material_albedo_map, 5);
	//	glUniform1i(standard_program_.material_emission_map, 6);
	//	glUniform1i(standard_program_.material_normal_map, 7);
	//	glUniform1i(standard_program_.material_metallic_map, 8);
	//	glUniform1i(standard_program_.material_roughness_map, 9);
	//	glUniform1i(standard_program_.material_ambient_occlusion_map, 10);

	//	glActiveTexture(GL_TEXTURE0);
	//	glBindTexture(GL_TEXTURE_2D, brdf_lut_texture_.texture);

	//	glActiveTexture(GL_TEXTURE1);
	//	glBindTexture(GL_TEXTURE_2D, shadow_maps_[0].texture);

	//	glActiveTexture(GL_TEXTURE2);
	//	glBindTexture(GL_TEXTURE_2D, shadow_maps_[1].texture);

	//	glActiveTexture(GL_TEXTURE3);
	//	glBindTexture(GL_TEXTURE_CUBE_MAP, propagate_target_.texture);

	//	glActiveTexture(GL_TEXTURE4);
	//	glBindTexture(GL_TEXTURE_CUBE_MAP, environment_maps_targets[1].texture);

	//	for (size_t i = 0; i < scene.environment_lights.size(); i++) {
	//		glUniform3fv(standard_program_.environment_maps[i].position, 1,
	//			glm::value_ptr(scene.environment_lights[i].position()));
	//		glUniform3fv(standard_program_.environment_maps[i].extent, 1,
	//			glm::value_ptr(scene.environment_lights[i].extent()));
	//		glUniform1fv(standard_program_.environment_maps[i].strength, 1,
	//			&scene.environment_lights[i].strength);
	//	}

	//	// Camera in world space
	//	auto position = camera.position();
	//	glUniform3fv(standard_program_.camera_position, 1, glm::value_ptr(position));

	//	for (size_t i = 0; i < scene.lights.size(); i++) {
	//		glUniform3fv(standard_program_.lights[i].position, 1,
	//			glm::value_ptr(glm::vec3(glm::vec4(scene.lights[i].position(), 1.0f))));

	//		glUniform3fv(standard_program_.lights[i].color, 1, glm::value_ptr(scene.lights[i].color));
	//		glUniform1fv(standard_program_.lights[i].strength, 1, &scene.lights[i].strength);

	//		glUniformMatrix4fv(standard_program_.lights[i].view, 1, GL_FALSE,
	//			&scene.lights[i].camera.view[0][0]);
	//		glUniformMatrix4fv(standard_program_.lights[i].projection, 1, GL_FALSE,
	//			&scene.lights[i].camera.projection[0][0]);

	//		auto light_angle = scene.lights[i].angle();
	//		glUniform1fv(standard_program_.lights[i].angle, 1, &light_angle);
	//		glUniform3fv(standard_program_.lights[i].direction, 1, glm::value_ptr(scene.lights[i].direction()));
	//	}

	//	glUniform2iv(standard_program_.camera_resolution, 1, glm::value_ptr(resolution));

	//	glUniform3fv(standard_program_.fog_color_near, 1, glm::value_ptr(scene.fog.color_near));
	//	glUniform3fv(standard_program_.fog_color_far, 1, glm::value_ptr(scene.fog.color_far));
	//	glUniform1fv(standard_program_.fog_attenuation_factor, 1,
	//		&scene.fog.attenuation_factor);

	//	for (auto &model : scene.models) {
	//		render_model(model, glm::mat4(1.0f), camera,
	//			scene.lights,
	//			scene.environment_lights,
	//			scene.fog,
	//			resolution, standard_program_);
	//	}
	//	render_boxes(scene.boxes, camera);
	//	render_particles(scene.particle_clouds, camera, resolution);
	//}
};