#pragma once

#include <vector>
#include "InputData.h"
#include "MouseData.h"

class Input
{
private:
	static std::vector<InputData> inputData;

	static void UpdateKeys(SDL_Event event);
	static void UpdateMouse(SDL_Event event);
public:
	static MouseData mouseData;

	static void Register(std::string eventName, std::function<void()> func, SDL_Keycode keyCode);
	static void Update(SDL_Event event);
};