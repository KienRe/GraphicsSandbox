#pragma once

#include <iostream>

#include <SDL.h>

#include <functional>

#include "Input.h"

class Window
{
private:
	void swap()
	{
		SDL_GL_SwapWindow(sdlWindow);
	}

public:
	SDL_Window* sdlWindow;

	Window(const char* title, int width, int height)
	{
		//Init SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			std::cout << ("Unable to initalize SDL: %s \n", SDL_GetError());
		}
		else
		{
			std::cout << "SDL initalized succesfully! \n";
		}

		//Create Window
		sdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	}

	~Window()
	{
		SDL_DestroyWindow(sdlWindow);
		SDL_Quit();
	}

	void Loop(std::function<void()> render)
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		while (event.type != SDL_QUIT)
		{
			Input::Update(event);

			render();

			SDL_PollEvent(&event);
			swap();
		}
	}
};