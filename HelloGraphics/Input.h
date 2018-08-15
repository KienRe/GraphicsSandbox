#pragma once

#include <vector>
#include "InputData.h"

class Input
{
private:
	static std::vector<InputData> inputData;
public:
	static void Register(std::string eventName, std::function<void()> func, SDL_Keycode keyCode);
	static void Update(SDL_Event event);
};