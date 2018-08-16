#include "Input.h"

std::vector<InputData> Input::inputData;
MouseData Input::mouseData;

void Input::Register(std::string eventName, std::function<void()> func, SDL_Keycode keyCode)
{
	InputData data;
	data.eventName = eventName;
	data.func = func;
	data.keyCode = keyCode;

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
	for each (auto data in inputData)
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == data.keyCode)
			{
				data.func();

				return;
			}
		}
	}
}