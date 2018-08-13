#pragma once

#include <iostream>

#include <SDL.h>
#include <GL/glew.h>

#include <imgui.h>
#include "imgui_impl_sdl_gl3.h"

#include <functional>

class Window
{
private:
	bool drawWireframe = false;

	void swap()
	{
		SDL_GL_SwapWindow(window);
	}

public:
	SDL_Window * window;
	SDL_GLContext glContext;

	Window(const char* title, int width, int height)
	{
		//SDL INIT
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			std::cout << ("Unable to initalize SDL: %s \n", SDL_GetError());
		}
		else
		{
			std::cout << "SDL initalized succesfully! \n";
		}

		//WINDOW / OPENGL INIT
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
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

		//Imgui INIT
		ImGui_ImplSdlGL3_Init(window);
		ImGui::StyleColorsClassic();
	}

	~Window()
	{
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(window);
		SDL_Quit();
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

	void Loop(std::function<void()> render)
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		while (event.type != SDL_QUIT)
		{
			//Imgui Events
			ImGui_ImplSdlGL3_ProcessEvent(&event);

			//Input Events
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_F1:
					break;
				}
			}

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

			render();
			ImGui::Render();

			SDL_PollEvent(&event);

			swap();
		}
	}
};