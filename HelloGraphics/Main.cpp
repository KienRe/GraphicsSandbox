#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <SDL.h>
#include <GL\glew.h>

#include <imgui.h>
#include "imgui_impl_sdl_gl3.h"

SDL_Window* window;
SDL_GLContext glContext;

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

bool drawWireframe = false;
bool allowWireframeSwitch = false;

float vertices[] =
{
	0.5f,  0.5f, 0.0f,		// top right
	0.5f, -0.5f, 0.0f,		// bottom right
	-0.5f, -0.5f, 0.0f,		// bottom left
	-0.5f,  0.5f, 0.0f		// top left 
};

unsigned int indices[] =
{
	0, 1, 3,				// first triangle
	1, 2, 3					// second triangle
};

const char* vertexShaderSource =
"														\
#version 330 core\n										\
layout(location = 0) in vec3 aPos;						\
														\
void main()												\
{														\
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	\
}														\
";

const char* fragementShaderSource =
"														\
#version 330 core\n										\
out vec4 FragColor;										\
														\
void main()												\
{														\
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);			\
} 														\
";

void ImguiFrame()
{
	ImGui_ImplSdlGL3_NewFrame(window);

	ImGui::BeginMainMenuBar();

	if (ImGui::BeginMenu("Rendering"))
	{
		ImGui::MenuItem("Wireframe Mode", "F1", &drawWireframe, true);
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

int main(int argc, char* args[])
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
	window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
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

	//Event Handling
	SDL_Event event;
	SDL_PollEvent(&event);

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
	glGenBuffers(0, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Vertex Attributes Setup
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Shader Setup
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR:SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragementShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR:SHADER::FRAGEMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR:SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


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
				if (event.key.repeat == 0)
					drawWireframe = !drawWireframe;
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

		//Rendering
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		ImGui::Render();
		SDL_GL_SwapWindow(window);
		SDL_PollEvent(&event);
	}

	SDL_Quit();
	SDL_DestroyWindow(window);

	return 0;
}