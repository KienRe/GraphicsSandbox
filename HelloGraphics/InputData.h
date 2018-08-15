#pragma once

#include <SDL.h>
#include <functional>
#include <string>

struct InputData
{
	std::string eventName;
	std::function<void()> func;
	SDL_Keycode keyCode;
};