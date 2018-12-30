#include <iostream>

#include <SDL.h>
#include <GL/glew.h>

#include "PhongScene.h"
#include "VegtationScene.h"

#include "Camera.h"

static bool s_Running = true;

SDL_Window* window;

void Init()
{
	//SDL Init
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << ("Unable to initalize SDL: %s \n", SDL_GetError());
	}
	else
	{
		std::cout << "SDL initalized succesfully! \n";
	}

	window = SDL_CreateWindow("Graphics Sandbox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

	//OpenGL Init
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	//Glew Init
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Glew Init failed!";
	}
	else
	{
		std::cout << "Glew initalized succesfully! \nVideo Driver Version: " << glGetString(GL_VERSION) << "\n";
	}

	//Setup
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glGetError();	//OpenGL starts with an error in the queue, we need to discard that else we cause confusion!
}

int main(int argc, char* args[])
{
	Init();

	//PhongScene phongScene;
	VegetationScene vegScene;
	Camera camera;

	while (s_Running)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		
		if (event.type == SDL_QUIT)
			s_Running = false;

		Input::Update(event);
		camera.Update();

		vegScene.Render(camera);

		SDL_PollEvent(&event);
		SDL_GL_SwapWindow(window);
	}

	return 0;
}