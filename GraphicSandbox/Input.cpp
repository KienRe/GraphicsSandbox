#include "Input.h"

std::vector<InputData> Input::inputData;
MouseData Input::mouseData;

void Input::Register(std::string eventName, std::function<void()> func, SDL_Scancode scanCode)
{
	InputData data;
	data.eventName = eventName;
	data.func = func;
	data.scanCode = scanCode;

	inputData.push_back(std::move(data));
}

void Input::Update(SDL_Event event)
{
	UpdateMouse(event);
	UpdateKeys(event);
}

void Input::UpdateMouse(SDL_Event event)
{
	mouseData.relX = 0;
	mouseData.relY = 0;

	if (event.button.button == SDL_BUTTON_LEFT)
	{
		if (event.button.state == SDL_PRESSED)
			mouseData.mouse1 = true;

		if (event.button.state == SDL_RELEASED)
			mouseData.mouse1 = false;
	}

	if (event.type == SDL_MOUSEMOTION && event.motion.state & SDL_BUTTON_LMASK)
	{
		mouseData.relX = event.motion.xrel;
		mouseData.relY = event.motion.yrel;
	}
}

void Input::UpdateKeys(SDL_Event event)
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	for each (auto data in inputData)
	{
		if (state[data.scanCode])
		{
			data.func();
		}
	}
}